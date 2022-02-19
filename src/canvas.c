#include <assert.h>
#include <float.h>
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/json.h"
#include "e/io.h"
#include "mathc/sca/int.h"
#include "mathc/mat/float.h"

#include "canvas.h"


//
// private
//


_Static_assert(CANVAS_MAX_SAVES<=999, "see save / load image");

static void save_image(const Canvas *self) {
    char file[128];
    snprintf(file, sizeof file, "image_%03i.png", self->L.save_idx);
    u_image_save_file(self->RO.image,
            e_io_savestate_file_path(file).s);
    e_io_savestate_save();
}

static void load_image(Canvas *self) {
    char file[128];
    snprintf(file, sizeof file, "image_%03i.png", self->L.save_idx);
    canvas_set_image(self, u_image_new_file(self->RO.image.layers, 
            e_io_savestate_file_path(file).s),
            false);
}

// updates the ro tex and sizes
static void update_render_objects(Canvas *self) {
    for (int i = 0; i < self->RO.image.layers; i++) {
        rTexture tex = r_texture_new(self->RO.image.cols, self->RO.image.rows, 1, 1, u_image_layer(self->RO.image, i));
        ro_single_set_texture(&self->L.render_objects[i], tex);
    }
    
    u_pose_set_size(&self->L.grid.rect.uv, self->RO.image.cols, self->RO.image.rows);
    {
        float w = (float) self->RO.image.cols / (2 * self->RO.pattern_cols);
        float h = (float) self->RO.image.rows / (2 * self->RO.pattern_rows);
        u_pose_set_size(&self->L.bg.rect.uv, w, h);
    }
}




//
// public
//


Canvas *canvas_new() {
    Canvas *self = rhc_calloc(sizeof *self);

    self->ro_color = R_COLOR_WHITE;
    
    self->alpha = 1.0;
    self->import_file = "import.png";
    self->auto_save_config = true;
    
    self->RO.pose = mat4_eye();
    
    self->RO.pattern_cols = 8;
    self->RO.pattern_rows = 8;
    
    for (int i = 0; i < CANVAS_MAX_LAYERS; i++) {
        self->L.render_objects[i] = ro_single_new(r_texture_new_invalid());
    }    

    rTexture grid_tex = r_texture_new_file(1, 1, "res/canvas_grid.png");
    r_texture_wrap_repeat(grid_tex);
    self->L.grid = ro_single_new(grid_tex);
    
    uColor_s buf[4];
    buf[0] = buf[3] = u_color_from_hex("#999999");
    buf[1] = buf[2] = u_color_from_hex("#777777");
    rTexture bg_tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(bg_tex);
    self->L.bg = ro_single_new(bg_tex);
    
    uImage img = u_image_new_zeros(32, 32, 1);
    canvas_set_image(self, img, false);
    
    return self;
}

void canvas_update(Canvas *self, float dtime) {
    
    self->RO.pose = u_pose_new_aa(0, 0, self->RO.image.cols, self->RO.image.rows);

    for (int i = 0; i < self->RO.image.layers; i++) {
        r_texture_set(self->L.render_objects[i].tex, u_image_layer(self->RO.image, i));

        // set pose
        self->L.render_objects[i].rect.pose = self->RO.pose;
        
        self->L.render_objects[i].rect.color = self->ro_color;
    }

    self->L.grid.rect.pose = self->RO.pose;
    self->L.bg.rect.pose = self->RO.pose;
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

}

void canvas_set_image(Canvas *self, uImage image_sink, bool save) {
    if(!u_image_valid(image_sink)) {
        log_warn("canvas: set_image failed, invalid img");
        return;
    }
    if(image_sink.layers>CANVAS_MAX_LAYERS) {
        log_warn("canvas: set_image failed, to much layers!");
        return;
    }
    log_info("canvas: set_image");
    
    u_image_kill(&self->RO.image);
    self->RO.image = image_sink;

    u_image_kill(&self->L.prev_image);
    self->L.prev_image = u_image_new_clone(image_sink);

    if(save)
        canvas_save(self);

    update_render_objects(self);
}

void canvas_set_pattern_size(Canvas *self, int cols, int rows) {
    cols = isca_clamp(cols, 1, self->RO.image.cols);
    rows = isca_clamp(rows, 1, self->RO.image.rows);
    self->RO.pattern_cols = cols;
    self->RO.pattern_rows = rows;
    update_render_objects(self);
    if(self->auto_save_config)
        canvas_save_config(self);
}

void canvas_save(Canvas *self) {
    log_info("canvas: save");
    if (u_image_equals(self->RO.image, self->L.prev_image)) {
        log_info("canvas: save failed, not changed");
        return;
    }
    
    u_image_copy(self->L.prev_image, self->RO.image);
    self->L.save_idx++;
    self->L.save_idx%=CANVAS_MAX_SAVES;
    self->L.save_idx_max = self->L.save_idx;
    if(self->L.save_idx == self->L.save_idx_min) {
        self->L.save_idx_min++;
        self->L.save_idx_min%=CANVAS_MAX_SAVES;
    }    
    
    save_image(self);
    
    if(self->auto_save_config)
        canvas_save_config(self);
}

void canvas_reload(Canvas *self) {
    u_image_copy(self->RO.image, self->L.prev_image);
}

void canvas_undo(Canvas *self) {
    log_info("canvas: undo");    
    if(self->L.save_idx == self->L.save_idx_min) {
        log_info("canvas: undo failed, on min idx");
        return;
    }
    
    self->L.save_idx--;
    if(self->L.save_idx < 0)
        self->L.save_idx = CANVAS_MAX_SAVES - 1;
        
    load_image(self);
    
    if(self->auto_save_config)
        canvas_save_config(self);
}

void canvas_redo(Canvas *self) {
    log_info("canvas: redo");
    if(self->L.save_idx == self->L.save_idx_max) {
        log_info("canvas: redo failed, on max idx");
        return;
    }
    
    self->L.save_idx++;
    self->L.save_idx %= CANVAS_MAX_SAVES;
    
    load_image(self);
    
    if(self->auto_save_config)
        canvas_save_config(self);
}

void canvas_save_config(const Canvas *self) {
    log_info("canvas: save_config");
    
    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json").s);
    
    uJson *canvas = u_json_append_object(config, "canvas");
    
    u_json_append_int(canvas, "pattern_cols", self->RO.pattern_cols);
    u_json_append_int(canvas, "pattern_rows", self->RO.pattern_rows);
    u_json_append_int(canvas, "save_idx", self->L.save_idx);
    u_json_append_int(canvas, "save_idx_min", self->L.save_idx_min);
    u_json_append_int(canvas, "save_idx_max", self->L.save_idx_max);
    
    u_json_save_file(config,
                       e_io_savestate_file_path("config.json").s);
    e_io_savestate_save();
    
    u_json_kill(&config);
}

void canvas_load_config(Canvas *self) {
    log_info("canvas: load_config");
    
    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json").s);
    
    uJson *canvas = u_json_get_object(config, "canvas");
    
    int pattern_cols, pattern_rows;
    if(u_json_get_object_int(canvas, "pattern_cols", &pattern_cols)
            && u_json_get_object_int(canvas, "pattern_rows", &pattern_rows)) {
        self->RO.pattern_cols = pattern_cols;
        self->RO.pattern_rows = pattern_rows;
    }
    
    int save_idx, save_idx_min, save_idx_max;
    if(u_json_get_object_int(canvas, "save_idx", &save_idx)
            && u_json_get_object_int(canvas, "save_idx_min", &save_idx_min)
            && u_json_get_object_int(canvas, "save_idx_max", &save_idx_max)) {
        self->L.save_idx = save_idx;
        self->L.save_idx_min = save_idx_min;
        self->L.save_idx_max = save_idx_max;
        
        load_image(self);
    } else {
        log_info("canvas: load_config failed, saving the empty image as index 0");
        save_image(self);
    }
    
    update_render_objects(self);
    
    u_json_kill(&config);
}
