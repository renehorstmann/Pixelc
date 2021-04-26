#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "camera.h"
#include "canvascam.h"
#include "background.h"
#include "canvas.h"
#include "animation.h"
#include "brush.h"
#include "canvascamctrl.h"
#include "palette.h"
#include "palettepresave.h"
#include "toolbar.h"
#include "input.h"
#include "savestate.h"

//
// options
//

// canvas size
//*
#define COLS 64
#define ROWS 32
#define LAYERS 1
//*/

// Tilec
/*
#define COLS 16*8
#define ROWS 16*8
#define LAYERS 2
//*/

// JumpHare
/*
#define COLS 32*8
#define ROWS 32*6
#define LAYERS 1
//*/


// animation + tiles
// screen size is >=180 pixel
// 16 Pixel * 11 cols = 180...
#define PLAY_COLS 1
#define PLAY_ROWS 1
#define PLAY_SIZE 1
#define PLAY_FRAMES 2
#define PLAY_FPS 2.0

// uncomment the used palette:
// #define PALETTE grayscale
// #define PALETTE grayscale_alpha
// #define PALETTE pixilmatt
// #define PALETTE slso8
// #define PALETTE gameboy
// #define PALETTE endesga32
// #define PALETTE endesga64
// #define PALETTE nes
 #define PALETTE aap64
 
//#define PALETTE refrection_values


#define BG_COLOR_A "#aaaacc"
#define BG_COLOR_B "#9999dd"

#define GRID_COLS 8
#define GRID_ROWS 8


// uncomment to change the file locations:
// #define IMAGE_FILE "../JumpHare/res/ice_block.png"
// #define IMPORT_FILE "res/color_drop.png"

//
// end of options
//


// macro to call palettepresave_PALETTE()
#define Cat(a, b) a ## b
#define PalettePresave(pal) Cat(palettepresave_, pal)


static void main_loop(float delta_time);


int main(int argc, char **argv) {
    log_info("Pixelc");

#ifdef IMAGE_FILE
    canvas.default_image_file = IMAGE_FILE;
#endif
#ifdef IMPORT_FILE
    canvas.default_import_file = IMPORT_FILE;
#endif

    // init e (environment)
    e_window_init("Pixelc");
    e_input_init();
    e_gui_init();

    // init r (render)
    r_render_init(e_window.window);

    // init systems
    camera_init();
    canvascam_init();
    background_init(u_color_from_hex(BG_COLOR_A), u_color_from_hex(BG_COLOR_B));
    canvas_init(COLS, ROWS, LAYERS, GRID_COLS, GRID_ROWS);
    animation_init(PLAY_COLS, PLAY_ROWS, PLAY_SIZE, PLAY_FRAMES, PLAY_FPS);
    brush_init();
    canvascamctrl_init();
    palette_init();
    toolbar_init();
    input_init();
    savestate_init();

    // calls "palettepresave_PALETTE();"
    PalettePresave(PALETTE)();

    // save start frame
    savestate_save();

    e_window_main_loop(main_loop);

    e_gui_kill();

    return 0;
}


static void main_loop(float delta_time) {
    // e updates
    e_input_update();


    // simulate
    camera_update();
    canvascam_update();
    background_update(delta_time);
    canvas_update(delta_time);
    animation_update(delta_time);
    palette_update(delta_time);
    toolbar_update(delta_time);

    // render
    r_render_begin_frame(e_window.size.x, e_window.size.y);

    background_render();
    animation_render();
    canvas_render();
    palette_render();
    toolbar_render();

    e_gui_render();

    // swap buffers
    r_render_end_frame();
}


