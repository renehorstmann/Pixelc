#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "u/image.h"
#include "r/ro_single.h"

#define CANVAS_MAX_SIZE 1024
#define CANVAS_MAX_LAYERS 128
#define CANVAS_MAX_SAVES 128


struct Canvas_Globals {
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
};
extern struct Canvas_Globals canvas;


void canvas_init();

void canvas_update(float dtime);

void canvas_render(const mat4 *canvascam_mat);


// sets a new image for the canvas
// canvas will take the ownership of image_sink
void canvas_set_image(uImage image_sink, bool save);

void canvas_set_pattern_size(int cols, int rows);

// saves an image (for reload, undo and redo)
// only saves if the image changed
void canvas_save();

// reloads the last saved image (for aborting a draw operation)
// uses the uImage L.prev_image in memory
void canvas_reload();

// reloads the last saved image
void canvas_undo();

// redos the undo (loads the next saved image, if available)
void canvas_redo();

// sets the render object color for vertex color effects
// default = R_COLOR_WHITE
void canvas_set_ro_color(vec4 color);

bool canvas_undo_available();

bool canvas_redo_available();

// saves the config to the savestate config.json 
// uses object "canvas"
void canvas_save_config();

// loads the config from the savestate config.json
// uses object "canvas"
void canvas_load_config();

#endif //PIXELC_CANVAS_H
