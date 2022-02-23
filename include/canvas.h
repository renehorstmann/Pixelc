#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "u/image.h"
#include "r/ro_types.h"

#define CANVAS_MAX_SIZE 256
#define CANVAS_MAX_LAYERS 16
#define CANVAS_MAX_SAVES 128

typedef struct Canvas {
    vec4 ro_color;
    
    int current_layer;
    bool show_grid;
    float alpha;
    bool blend_layers;
    const char *import_file;
    
    bool auto_save_config;
    
    // read only
    struct {
        mat4 pose; // = u_pose_new_aa(0, 0, cols, rows)
        uImage image;
        
        int pattern_cols;
        int pattern_rows;
    } RO;

    // private
    struct {
        uImage prev_image;
        RoSingle render_objects[CANVAS_MAX_LAYERS];

        RoSingle bg;
        RoSingle grid;
        
        int save_idx;
        int save_idx_max;
        int save_idx_min;

        int save_layers[CANVAS_MAX_SAVES];
    } L;
} Canvas;

Canvas *canvas_new();

void canvas_update(Canvas *self, float dtime);

void canvas_render(Canvas *self, const mat4 *canvascam_mat);


// sets a new image for the canvas
// canvas will take the ownership of image_sink
void canvas_set_image(Canvas *self, uImage image_sink, bool save);

void canvas_set_pattern_size(Canvas *self, int cols, int rows);

// saves an image (for reload, undo and redo)
// only saves if the image changed
void canvas_save(Canvas *self);

// reloads the last saved image (for aborting a draw operation)
// uses the uImage L.prev_image in memory
void canvas_reload(Canvas *self);

// reloads the last saved image
void canvas_undo(Canvas *self);

// redos the undo (loads the next saved image, if available)
void canvas_redo(Canvas *self);

// sets the render object color for vertex color effects
// default = R_COLOR_WHITE
void canvas_set_ro_color(Canvas *self, vec4 color);

// saves the config to the savestate config.json 
// uses object "canvas"
void canvas_save_config(const Canvas *self);

// loads the config from the savestate config.json
// uses object "canvas"
void canvas_load_config(Canvas *self);


static bool canvas_undo_available(const Canvas *self) {
    return self->L.save_idx != self->L.save_idx_min;
}

static bool canvas_redo_available(const Canvas *self) {
    return self->L.save_idx != self->L.save_idx_max;
}

#endif //PIXELC_CANVAS_H
