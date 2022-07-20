#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include "m/types/int.h"
#include "m/types/float.h"
#include "u/sprite.h"
#include "r/ro_single.h"

#define CANVAS_MAX_SIZE 1024
#define CANVAS_MAX_LAYERS 96
#define CANVAS_MAX_FRAMES 96
#define CANVAS_MAX_SAVES 128
#define CANVAS_MAX_TABS 9


enum canvas_blend_mode {
    CANVAS_BLEND_NONE,
    CANVAS_BLEND_FRAMES_ONION,
    CANVAS_BLEND_FRAMES_FULL,
    CANVAS_BLEND_LAYER_ONION,
    CANVAS_BLEND_LAYER_FULL,
    CANVAS_BLEND_NUM_MODES
};


struct Canvas_Globals {
    vec4 ro_color;

    bool show_grid;
    float alpha;
    enum canvas_blend_mode blend_mode;
    
    float frame_times[CANVAS_MAX_FRAMES];

    // read only
    struct {
        mat4 pose; // = u_pose_new_aa(0, 0, cols, rows)
        
        uSprite sprite;
        rTexture tex;
        
        int frames;
        int layers;
        
        int current_frame;
        int current_layer;
        
        bool frames_enabled;
        bool layers_enabled;
        
        // just to directly read the image from the sprite
        // deprecated
        uImage image;
        int current_image_layer;
        
        int pattern_cols;
        int pattern_rows;
        
        int tab_id;
    } RO;
};
extern struct Canvas_Globals canvas;


void canvas_init();

void canvas_update(float dtime);

void canvas_render(const mat4 *canvascam_mat);


void canvas_set_frame(int sprite_col);

void canvas_set_layer(int sprite_row);

// turns on or off sprite.cols
void canvas_enable_frames(bool enable);

// turns on or off sprite.rows
void canvas_enable_layers(bool enable);

// sets a new image for the canvas
// canvas will take the ownership of image_sink
void canvas_set_sprite(uSprite image_sink, bool save);

void canvas_set_pattern_size(int cols, int rows);

// saves an image (for reload, undo and redo)
// only saves if the image changed
void canvas_save();

// reloads the last saved image (for aborting a draw operation)
// uses the uSprite L.prev_image in memory
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

// sets to a new tab and loads that image
void canvas_set_tab_id(int id);

// returns a new image of the tab id
uSprite canvas_get_tab(int id);

// saves the config to the savestate config.json 
// uses object "canvas"
void canvas_save_config();

// loads the config from the savestate config.json
// uses object "canvas"
void canvas_load_config();

#endif //PIXELC_CANVAS_H
