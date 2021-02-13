#include "mathc/float.h"
#include "mathc/utils/float.h"
#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "camera.h"
#include "canvas_camera.h"
#include "background.h"
#include "canvas.h"
#include "animation.h"
#include "brush.h"
#include "canvas_camera_control.h"
#include "palette.h"
#include "palette_presave.h"
#include "toolbar.h"
#include "input.h"
#include "savestate.h"
#include "io.h"

//
// options
//

// canvas size
#define COLS 32
#define ROWS 32

// animation + tiles
// screen size is >=180 pixel
// 16 Pixel * 11 cols = 180...
#define PLAY_COLS 1
#define PLAY_ROWS 1
#define PLAY_FRAMES 1
#define PLAY_FPS 2.0
 
// uncomment the used palette:
// #define PALETTE grayscale
// #define PALETTE grayscale_alpha
// #define PALETTE grayscale
 #define PALETTE pixilmatt
// #define PALETTE slso8
// #define PALETTE gameboy
// #define PALETTE endesga32
// #define PALETTE endesga64
// #define PALETTE nes
// #define PALETTE aap64


#define BG_COLOR_A "#222222"
#define BG_COLOR_B "#333344"

#define GRID_COLS 8
#define GRID_ROWS 8


// uncomment to change the file locations:
// #define IMAGE_FILE "res/button_play.png"
// #define IMPORT_FILE "res/color_drop.png"

//
// end of options
//


// macro to call palette_presave_PALETTE()
#define Cat(a, b) a ## b
#define PalettePresave(pal) Cat(palette_presave_, pal)


static void main_loop(float delta_time);


int main(int argc, char **argv) {
    SDL_Log("Pixelc");
    
#ifdef IMAGE_FILE
    io.default_image_file = IMAGE_FILE;
#endif
#ifdef IMPORT_FILE
    io.default_import_file = IMPORT_FILE;
#endif

    // init e (environment)
    e_window_init("Pixelc");
    e_input_init();
    e_gui_init();

    // init r (render)
    r_render_init(e_window.window);

    // init systems
    camera_init();
    canvas_camera_init();
    background_init(color_from_hex(BG_COLOR_A), color_from_hex(BG_COLOR_B));
    canvas_init(COLS, ROWS, GRID_COLS, GRID_ROWS);
    animation_init(PLAY_COLS, PLAY_ROWS, PLAY_FRAMES, PLAY_FPS);
    brush_init();
    canvas_camera_control_init();
    palette_init();
    toolbar_init();
    input_init();
    savestate_init();

    // calls "palette_presave_PALETTE();"
    PalettePresave(PALETTE)();    

    // save start frame
    savestate_save();

    e_window_main_loop(main_loop);

    e_gui_kill();
    
    return 0;
}


static void main_loop(float delta_time) {
    // e updates
    e_window_update();
    e_input_update();
    

    // simulate
    camera_update();
    canvas_camera_update();
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

    // check for opengl errors:
    r_render_error_check();
}


