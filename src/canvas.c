#include <assert.h>
#include <float.h>
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/image.h"
#include "mathc/mat/float.h"

#include "palette.h"
#include "toolbar.h"
#include "selection.h"
#include "canvas.h"

#define SELECTION_BORDER_FACTOR 4

//
// private
//


static void init_render_objects(Canvas *self) {
    for (int i = 0; i < self->RO.image.layers; i++) {
        rTexture tex = r_texture_new(self->RO.image.cols, self->RO.image.rows, 1, 1, u_image_layer(self->RO.image, i));
        self->L.render_objects[i] = ro_single_new(tex);
    }
}

static mat4 pixel_pose(const Canvas *self, int x, int y) {
    float w = u_pose_get_w(self->RO.pose);
    float size = w / self->RO.image.cols;


    float pos_x = u_pose_aa_get_left(self->RO.pose) + (x + 0.5) * size;
    float pos_y = u_pose_aa_get_top(self->RO.pose) - (y + 0.5) * size;

    mat4 pose = mat4_eye();
    u_pose_set(&pose, pos_x, pos_y, size, size, 0);
    return pose;
}

static void setup_selection(Canvas *self) {
    int x = 0, y = 0, w = 0, h = 0;
    if (self->brush_ref->selection) {
        x = self->brush_ref->selection->left;
        y = self->brush_ref->selection->top;
        w = self->brush_ref->selection->cols;
        h = self->brush_ref->selection->rows;
    }

    int max = self->L.selection_border.num;

    int idx = 0;
    for (int i = 0; i < h; i++) {
        self->L.selection_border.rects[idx].pose = pixel_pose(self, x - 1, y + i);
        self->L.selection_border.rects[idx].sprite = (vec2) {0, 0};
        idx++;
        if (idx >= max) goto UPDATE;

        self->L.selection_border.rects[idx].pose = pixel_pose(self, x + w, y + i);
        self->L.selection_border.rects[idx].sprite = (vec2) {0, 1};
        idx++;
        if (idx >= max) goto UPDATE;
    }
    for (int i = 0; i < w; i++) {
        self->L.selection_border.rects[idx].pose = pixel_pose(self, x + i, y - 1);
        self->L.selection_border.rects[idx].sprite = (vec2) {1, 0};
        idx++;
        if (idx >= max) goto UPDATE;

        self->L.selection_border.rects[idx].pose = pixel_pose(self, x + i, y + h);
        self->L.selection_border.rects[idx].sprite = (vec2) {1, 1};
        idx++;
        if (idx >= max) goto UPDATE;
    }

    for (; idx < self->L.selection_border.num; idx++) {
        u_pose_set(&self->L.selection_border.rects[idx].pose, FLT_MAX, FLT_MAX, 0, 0, 0);
    }

    UPDATE:
    ro_batch_update(&self->L.selection_border);
}

static void save_state(SaveState *savestate, void *user_data) {
    Canvas *self = user_data;
    log_info("canvas: save_state");

    // costum uImage with data concatenated
    size_t img_size = sizeof(uImage) + u_image_data_size(self->RO.image);
    char *data = rhc_malloc(img_size);
    uImage *img = (uImage *) data;
    img->data = (uColor_s *) (data + sizeof(uImage));
    img->cols = self->RO.image.cols;
    img->rows = self->RO.image.rows;
    img->layers = self->RO.image.layers;
    img->allocator = rhc_allocator_new_empty();

    u_image_copy(*img, self->RO.image);
    savestate_save_data(savestate, img, img_size);

    // costum uImage
    rhc_free(img);
}

static void load_state(SaveState *savestate, const void *data, size_t size, void *user_data) {
    Canvas *self = user_data;
    log_info("canvas: load_state");
    // todo: check new layers, rows, cols
    assume(sizeof(uImage) + u_image_data_size(self->RO.image) == size, "invalid data + size pair");

    u_image_kill(&self->RO.image);

    // costum uImage with data concatenated
    uImage *img = (uImage *) data;
    img->data = (uColor_s *) ((char *) data + sizeof(uImage));

    self->RO.image = u_image_new_clone(*img);
    u_image_save_file(self->RO.image, self->default_image_file);
    u_image_copy(self->L.prev_image, self->RO.image);
}


//
// public
//


Canvas *canvas_new(SaveState *savestate, int cols, int rows, int layers, int grid_cols, int grid_rows) {
    Canvas *self = rhc_calloc(sizeof *self);

    self->savestate_ref = savestate;

    self->default_image_file = "image.png";
    self->default_import_file = "import.png";

    assume(layers <= CANVAS_MAX_LAYERS, "too many layers");
    self->alpha = 1.0;

    self->L.save_id = savestate_register(savestate, save_state, load_state, self);

    self->RO.pose = mat4_eye();

    self->RO.image = u_image_new_zeros(cols, rows, layers);
    self->current_layer = 0;

    init_render_objects(self);

    self->L.grid = ro_single_new(r_texture_new_file(1, 1, "res/canvas_grid.png"));
    u_pose_set_size(&self->L.grid.rect.uv, cols, rows);


    self->L.selection_border = ro_batch_new(2 * (rows + cols) * SELECTION_BORDER_FACTOR,
                                            r_texture_new_file(2, 2, "res/selection_border.png"));
    for (int i = 0; i < self->L.selection_border.num; i++) {
        self->L.selection_border.rects[i].color = u_color_to_vec4(u_color_from_hex("#357985"));
    }


    uColor_s buf[4];
    buf[0] = buf[3] = u_color_from_hex("#999999");
    buf[1] = buf[2] = u_color_from_hex("#777777");
    rTexture bg_tex = r_texture_new(2, 2, 1, 1, buf);
    self->L.bg = ro_single_new(bg_tex);
    {
        float w = (float) cols / (2 * grid_cols);
        float h = (float) rows / (2 * grid_rows);
        u_pose_set_size(&self->L.bg.rect.uv, w, h);
    }

    uImage img = u_image_new_file(layers, self->default_image_file);
    if (u_image_valid(img)) {
        u_image_copy_top_left(self->RO.image, img);
        u_image_kill(&img);
    }

    self->L.prev_image = u_image_new_clone(self->RO.image);

    return self;
}

void canvas_update(Canvas *self, const Camera_s *camera, float dtime) {
    float w, h;
    if (self->RO.image.rows < self->RO.image.cols) {
        w = 160;
        h = 160.0f * self->RO.image.rows / self->RO.image.cols;
    } else {
        h = 160;
        w = 160.0f * self->RO.image.cols / self->RO.image.rows;
    }

    float x = 0, y = 0;
    if (camera_is_portrait_mode(camera)) {
        y = 30;
    }

    u_pose_set(&self->RO.pose, x, y, w, h, 0);

    for (int i = 0; i < self->RO.image.layers; i++) {
        r_texture_set(self->L.render_objects[i].tex, u_image_layer(self->RO.image, i));

        // set pose
        self->L.render_objects[i].rect.pose = self->RO.pose;
    }

    self->L.grid.rect.pose = self->RO.pose;
    self->L.bg.rect.pose = self->RO.pose;

    setup_selection(self);
}

void canvas_render(Canvas *self, const mat4 *canvascam_mat) {
    ro_single_render(&self->L.bg, canvascam_mat);

    for (int i = 0; i <= self->current_layer; i++) {
        float alpha = (i + 1.0) / (self->current_layer + 1.0);
        self->L.render_objects[i].rect.color.w = alpha * self->alpha;
        ro_single_render(&self->L.render_objects[i], canvascam_mat);
    }

    if (self->show_grid)
        ro_single_render(&self->L.grid, canvascam_mat);

    if (self->brush_ref->selection)
        ro_batch_render(&self->L.selection_border, canvascam_mat, false);
}

void canvas_resize(Canvas *self, int cols, int rows, int layers) {
    // todo
}

ivec2 canvas_get_cr(const Canvas *self, vec4 pointer_pos) {
    mat4 pose_inv = mat4_inv(self->RO.pose);
    vec4 pose_pos = mat4_mul_vec(pose_inv, pointer_pos);

    ivec2 cr;
    cr.x = (pose_pos.x + 0.5) * self->RO.image.cols;
    cr.y = (0.5 - pose_pos.y) * self->RO.image.rows;
    return cr;
}

void canvas_clear(Canvas *self) {
    log_info("canvas: clear");
    for (int r = 0; r < self->RO.image.rows; r++) {
        for (int c = 0; c < self->RO.image.cols; c++) {
            if (self->brush_ref->selection && !selection_contains(self->brush_ref->selection, c, r))
                continue;

            *u_image_pixel(self->RO.image, c, r, self->current_layer) = U_COLOR_TRANSPARENT;
        }
    }
    canvas_save(self);
}

void canvas_save(Canvas *self) {
    log_info("canvas: save");
    if (!u_image_equals(self->RO.image, self->L.prev_image)) {
        u_image_copy(self->L.prev_image, self->RO.image);
        savestate_save(self->savestate_ref);
        u_image_save_file(self->RO.image, self->default_image_file);
    }
}

void canvas_redo_image(Canvas *self) {
    log_info("canvas: redo_image");
    u_image_copy(self->RO.image, self->L.prev_image);
}

