#include <assert.h>
#include <float.h>
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/json.h"
#include "e/io.h"
#include "mathc/mat/float.h"

#include "palette.h"
#include "toolbar.h"
#include "canvas.h"


//
// private
//


static void save_image(const Canvas *self) {
    char file[128];
    snprintf(file, sizeof file, "save_file_%i.png", self->L.save_idx);
    u_image_save_file(self->RO.image, file);
}

static void load_image(Canvas *self) {
    char file[128];
    snprintf(file, sizeof file, "save_file_%i.png", self->L.save_idx);
    canvas_set_image(self, u_image_new_file(self->RO.image.layers, file));
}

// updates the ro tex and sizes
static void update_render_objects(Canvas *self) {
    for (int i = 0; i < self->RO.image.layers; i++) {
        rTexture tex = r_texture_new(self->RO.image.cols, self->RO.image.rows, 1, 1, u_image_layer(self->RO.image, i));
        ro_single_set_texture(&self->L.render_objects[i], tex);
    }
    
    u_pose_set_size(&self->L.grid.rect.uv, self->RO.image.cols, self->RO.image.rows);
    {
        float w = (float) self->RO.image.cols / (2 * self->L.grid_cols);
        float h = (float) self->RO.image.rows / (2 * self->L.grid_rows);
        u_pose_set_size(&self->L.bg.rect.uv, w, h);
    }
}




//
// public
//


Canvas *canvas_new(int cols, int rows, int layers, int grid_cols, int grid_rows) {
    Canvas *self = rhc_calloc(sizeof *self);

    self->ro_color = R_COLOR_WHITE;

    self->L.grid_cols = grid_cols;
    self->L.grid_rows = grid_rows;

    self->default_image_file = "image.png";
    self->default_import_file = "import.png";

    assume(layers <= CANVAS_MAX_LAYERS, "too many layers");
    self->alpha = 1.0;

    self->RO.pose = mat4_eye();

    self->current_layer = 0;

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
    

    uImage img = u_image_new_zeros(cols, rows, layers);
    {
        uImage load = u_image_new_file(layers, self->default_image_file);
        if (u_image_valid(load))
            u_image_copy_top_left(img, load);
        u_image_kill(&load);
        
    }

    self->L.prev_image = u_image_new_clone(img);
    
    canvas_set_image(self, img);
    
    save_image(self);
    
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

void canvas_set_image(Canvas *self, uImage image_sink) {
    if(!u_image_valid(image_sink))
        return;
    log_info("canvas: set_image");
    
    u_image_kill(&self->RO.image);
    u_image_kill(&self->L.prev_image);
    
    self->RO.image = image_sink;
    self->L.prev_image = u_image_new_clone(image_sink);
    
    update_render_objects(self);
}


void canvas_save(Canvas *self) {
    log_info("canvas: save");
    if (!u_image_equals(self->RO.image, self->L.prev_image)) {
        u_image_copy(self->L.prev_image, self->RO.image);
        u_image_save_file(self->RO.image, self->default_image_file);
        
        self->L.save_idx++;
        if(self->L.save_idx >= CANVAS_MAX_SAVES)
            self->L.save_idx = 0;
        if(self->L.save_idx == self->L.save_idx_min) {
            self->L.save_idx_min++;
            if(self->L.save_idx_min >= CANVAS_MAX_SAVES)
                self->L.save_idx_min = 0;
        }
        
        save_image(self);
    }
}

void canvas_reload(Canvas *self) {
    log_info("canvas: reload");
    u_image_copy(self->RO.image, self->L.prev_image);
}

void canvas_undo(Canvas *self) {
    log_info("canvas: undo %i %i", self->L.save_idx, self->L.save_idx_min);    
    if(self->L.save_idx == self->L.save_idx_min) {
        log_info("canvas: undo failed, on min idx");
        return;
    }
    
    self->L.save_idx--;
    if(self->L.save_idx < 0)
        self->L.save_idx = CANVAS_MAX_SAVES - 1;
        
    load_image(self);
}

void canvas_redo(Canvas *self) {
    log_info("canvas: redo");
    if(self->L.save_idx == self->L.save_idx_max) {
        log_info("canvas: redo failed, on max idx");
        return;
    }
    
    self->L.save_idx++;
    if(self->L.save_idx >= CANVAS_MAX_SAVES)
        self->L.save_idx = 0;
        
    load_image(self);
}

void canvas_save_config(const Canvas *self) {
    log_info("canvas: save_config");
    
    String config_string;
    uJson *config;
    
    config_string = e_io_savestate_read("config.json", true);
    config = u_json_new_str(config_string.str);
    string_kill(&config_string);
    
    uJson *canvas = u_json_append_object(config, "canvas");
    
    u_json_append_int(canvas, "cols", self->RO.image.cols);
    u_json_append_int(canvas, "rows", self->RO.image.rows);
    u_json_append_int(canvas, "layers", self->RO.image.layers);
    u_json_append_int(canvas, "grid_cols", self->L.grid_cols);
    u_json_append_int(canvas, "grid_rows", self->L.grid_rows);
    
    config_string = u_json_to_string(config);
    e_io_savestate_write("config.json", config_string.str, true);
    string_kill(&config_string);
    
    u_json_kill(&config);
}

void canvas_load_config(Canvas *self) {
    log_info("canvas: load_config");
    
    uJson *config;
    
    String config_string = e_io_savestate_read("config.json", true);
    config = u_json_new_str(config_string.str);
    string_kill(&config_string);
    
    uJson *canvas = u_json_get_object(config, "canvas");
    int cols, rows, layers;
    if(u_json_get_object_int(canvas, "cols", &cols)
        && u_json_get_object_int(canvas, "rows", &rows)
        && u_json_get_object_int(canvas, "layers", &layers)) {
        
        // todo
    }
    
    int grid_cols, grid_rows;
    if(u_json_get_object_int(canvas, "grid_cols", &grid_cols)
        && u_json_get_object_int(canvas, "grid_rows", &grid_rows)) {
        self->L.grid_cols = grid_cols;
        self->L.grid_rows = grid_rows;
    }
    
    update_render_objects(self);
    
    u_json_kill(&config);
}
