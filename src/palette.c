#include <float.h>  // FLT_MAX
#include <assert.h>
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "rhc/allocator.h"
#include "brush.h"
#include "palette.h"

#define COLOR_DROP_SIZE 16.0f
#define MAX_ROWS 10


//
// private
//



static int palette_cols(const Palette *self) {
    assert(camera_width(self->camera_ref) > 0 && camera_height(self->camera_ref) > 0 && "startup bug?");
    if (camera_is_portrait_mode(self->camera_ref))
        return (int) floorf(camera_width(self->camera_ref) / COLOR_DROP_SIZE);
    return (int) floorf(camera_height(self->camera_ref) / COLOR_DROP_SIZE);
}

static bool pos_in_palette(const Palette *self, vec2 pos) {
    int cols = palette_cols(self);
    int rows = 1 + self->L.palette_size / cols;
    int size = rows * COLOR_DROP_SIZE;
    if (camera_is_portrait_mode(self->camera_ref)) {
        return pos.y <= self->camera_ref->RO.bottom + size;
    }
    return pos.x >= self->camera_ref->RO.right - size;
}


static mat4 setup_palette_color_pose(const Palette *self, int r, int c) {
    mat4 pose = mat4_eye();
    u_pose_set_size(&pose, COLOR_DROP_SIZE, COLOR_DROP_SIZE);
    if (camera_is_portrait_mode(self->camera_ref)) {
        u_pose_set_xy(&pose, self->camera_ref->RO.left + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE,
                      self->camera_ref->RO.bottom + COLOR_DROP_SIZE / 2 + r * COLOR_DROP_SIZE);
    } else {
        u_pose_set_xy(&pose, self->camera_ref->RO.right - COLOR_DROP_SIZE / 2 - r * COLOR_DROP_SIZE,
                      self->camera_ref->RO.bottom + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE);
        u_pose_set_angle(&pose, M_PI_2);
    }
    return pose;
}


//
// public
//

Palette *palette_new(const Camera_s *camera, Brush *brush) {
    Palette *self = rhc_calloc_raising(sizeof *self);

    self->camera_ref = camera;
    self->brush_ref = brush;

    self->L.palette_ro = ro_batch_new(PALETTE_MAX, r_texture_new_file(1, 1, "res/color_drop.png"));

    self->L.background_ro = ro_batch_new(PALETTE_MAX + MAX_ROWS,
                                         r_texture_new_file(2, 2, "res/palette_background.png"));

    self->L.select_ro = ro_single_new(r_texture_new_file(1, 1, "res/palette_select.png"));

    // default palette:
    {
        uColor_s palette[4] = {
                {0,   0,   0,   0},
                {0,   0,   0,   255},
                {128, 128, 128, 255},
                {255, 255, 255, 255}
        };
        palette_set_colors(self, palette, 4);
    }

    return self;
}


void palette_update(Palette *self, float dtime) {
    int cols = palette_cols(self);
    int last_row = (self->L.palette_size - 1) / cols;
    for (int i = 0; i < PALETTE_MAX; i++) {
        int r = i / cols;
        int c = i % cols;

        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(self, r, c);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        self->L.palette_ro.rects[i].pose = pose;
        self->L.background_ro.rects[i].pose = pose;

        // color
        vec4 col;
        if (i < self->L.palette_size)
            col = u_color_to_vec4(self->L.palette[i]);
        else
            col = R_COLOR_TRANSPARENT;

        self->L.palette_ro.rects[i].color = col;


        // background sprite
        {
            float u = i < self->L.palette_size ? 0 : 1;
            float v = r < last_row ? 1 : 0;
            self->L.background_ro.rects[i].sprite = (vec2) {{u, v}};
        }
    }

    // background continuation
    for (int r = 0; r < MAX_ROWS; r++) {
        int idx = self->L.background_ro.num - r - 1;
        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(self, r, cols);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        self->L.background_ro.rects[idx].pose = pose;

        // background uv
        {
            float u = 1;
            float v = r < last_row ? 1 : 0;
            self->L.background_ro.rects[idx].sprite = (vec2) {{u, v}};
        }
    }

    self->L.select_ro.rect.pose = self->L.palette_ro.rects[self->L.last_selected].pose;

    ro_batch_update(&self->L.palette_ro);
    ro_batch_update(&self->L.background_ro);
}

void palette_render(Palette *self, const mat4 *camera_mat) {
    ro_batch_render(&self->L.background_ro, camera_mat);
    ro_batch_render(&self->L.palette_ro, camera_mat);
    ro_single_render(&self->L.select_ro, camera_mat);
}


bool palette_pointer_event(Palette *self, ePointer_s pointer) {
    if (!pos_in_palette(self, pointer.pos.xy))
        return false;

    if (pointer.action != E_POINTER_DOWN)
        return true;

    for (int i = 0; i < self->L.palette_size; i++) {
        if (u_pose_contains(self->L.palette_ro.rects[i].pose, pointer.pos)) {
            palette_set_color(self, i);
            return true;
        }
    }

    return true;
}

float palette_get_hud_size(const Palette *self) {
    int cols = palette_cols(self);
    int rows = 1 + self->L.palette_size / cols;
    return rows * COLOR_DROP_SIZE;
}

void palette_set_colors(Palette *self, const uColor_s *palette, int size) {
    assert(size < PALETTE_MAX);
    memcpy(self->L.palette, palette, sizeof(uColor_s) * size);
    self->L.palette_size = size;
    palette_set_color(self, 0);
}


int palette_get_color(const Palette *self) {
    return self->L.last_selected;
}

void palette_set_color(Palette *self, int index) {
    self->brush_ref->current_color = self->L.palette[index];
    self->L.select_ro.rect.pose = self->L.palette_ro.rects[index].pose;
    self->L.last_selected = index;
}
