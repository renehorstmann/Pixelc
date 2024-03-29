#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

//
// The actual image canvas, loads saves and renders the image
//

#include "m/types/int.h"
#include "m/types/float.h"
#include "u/sprite.h"
#include "r/ro_single.h"
#include "tile.h"

// 64 "MiB" = 16 "MiPixel"
#define CANVAS_MAX_MEMORY 67108864

#define CANVAS_MAX_SIZE 8192
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
    
    // show or hide the background grid (defaults to true)
    bool show_bg;

    // shows frames and layers grid and sets the alpha value of the canvas lower
    //      to blend in the background
    bool show_grid;

    // sets the render mode for the canvas
    enum canvas_blend_mode blend_mode;

    // will be saved and used in the animation
    float frame_times[CANVAS_MAX_FRAMES];

    // read only
    struct {
        mat4 pose; // = u_pose_new_aa(0, 0, cols, rows)

        // actual canvas size
        int cols, rows;
        int frames, layers;

        // the sprite to draw in
        // the internal sizes may differ from the canvas size above
        // if frames or layers are not enabled, the sprite image contains the full canvas
        uSprite sprite;

        // The texture used to draw the canvas
        // will normally be generated from sprite (but can be reset for mods, e. g. Tilec)
        // is always reset to the default in canvas_update
        rTexture tex;

        // current sprite position to draw
        int current_frame;
        int current_layer;

        bool frames_enabled;
        bool layers_enabled;

        // just a ref to sprite.img to directly read the image from the sprite
        uImage image;
        // = current_layer*sprite.cols + current_frame
        int current_image_layer;

        // one of the nine image tabs
        int current_tab_id;

        ivec2 pattern_size;
    } RO;
};
extern struct Canvas_Globals canvas;

// returns true if the given size is valid
// may be invalid if image size would exceed CANVAS_MAX_MEMORY
//      or r_render.limits.
//      or all sizes to be<=0
bool canvas_size_valid(int cols, int rows, int frames, int layers);

void canvas_init();

void canvas_update(float dtime);

void canvas_render(const mat4 *canvascam_mat);

// returns the size of the canvas
static ivec2 canvas_get_size() {
    if(tile.active && tile.canvas_active)
        return tile_canvas_get_size();
    return (ivec2) {{canvas.RO.image.cols, canvas.RO.image.rows}};
}

// returns the size of a pixel unit
// normally 1, but tiles renders multiple pixels in a tile unit (8, 16, 32)
static vec2 canvas_get_unit_scale() {
    ivec2 cs = canvas_get_size();
    return (vec2) {{(float) cs.x / canvas.RO.image.cols, (float) cs.y / canvas.RO.image.rows}};
}

// returns col and row for the canvas image from a touch on the canvas
static ivec2 canvas_get_cr(vec2 pointer_pos) {
    if(tile.active && tile.canvas_active)
        return tile_canvas_get_cr(pointer_pos);

    return (ivec2) {{(int) pointer_pos.x, (int) -pointer_pos.y}};
}

// returns a new image with a single layer
// calls canvas_reload first
uImage canvas_get_full_image();

// returns a new image, with the layers merged
// calls canvas_reload first
uImage canvas_get_merged_image();

// returns a new sprite
// calls canvas_reload first
uSprite canvas_get_sprite();

// may be called by a mod
static void canvas_reset_tex(rTexture tex) {
    canvas.RO.tex = tex;
}

void canvas_set_frame(int sprite_col);

void canvas_set_layer(int sprite_row);

// turns on or off sprite.cols
// will call canvas_save_config
void canvas_enable_frames(bool enable);

// turns on or off sprite.rows
// will call canvas_save_config
void canvas_enable_layers(bool enable);

// sets a new image for the canvas
// canvas will take the ownership of image_sink
void canvas_set_sprite(uSprite image_sink, bool save);

// resets the chessboard pattern background size (size of a bright or dark set of pixels)
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

bool canvas_undo_available();

bool canvas_redo_available();

// sets to a new tab and loads that image
void canvas_set_tab_id(int id);

// returns a new image of the tab id
uSprite canvas_get_tab(int id);

// clears the '0'er save idx of all tabs
void canvas_clear_all_base_tabs();

// saves the config to the savestate config.json 
// uses object "canvas"
// also saves the current image as savestate
void canvas_save_config();

// loads the config from the savestate config.json
// uses object "canvas"
void canvas_load_config();

#endif //PIXELC_CANVAS_H
