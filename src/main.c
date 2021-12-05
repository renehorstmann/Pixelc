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
#include "inputctrl.h"
#include "savestate.h"

#include "textinput.h"

//
// options
//

// canvas size
//*
#define COLS 128*2
#define ROWS 16
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
// #define IMAGE_FILE "../JumpHare/res/tiles/tile_02.png"
// #define IMPORT_FILE "res/button_dot.png"

//
// end of options
//


// macro to call palettepresave_PALETTE()
#define Cat(a, b) a ## b
#define PalettePresave(pal) Cat(palettepresave_, pal)


static struct {
    Camera_s *camera;
    CanvasCam_s *canvascam;
    SaveState *savestate;
    Background *background;
    Canvas *canvas;
    Animation *animation;
    Brush *brush;
    Palette *palette;
    CanvasCamCtrl *canvascamctrl;
    Toolbar *toolbar;
    InputCtrl *inputctrl;
    
    TextInput *textinput;
} L;

// this function will be called at the start of the app
static void init(eSimple *simple, ivec2 window_size) {

    // init systems
    L.camera = camera_new();
    L.canvascam = canvascam_new();
    L.savestate = savestate_new();
    L.background = background_new(u_color_from_hex(BG_COLOR_A), u_color_from_hex(BG_COLOR_B));
    L.canvas = canvas_new(L.savestate, COLS, ROWS, LAYERS, GRID_COLS, GRID_ROWS);
#ifdef IMAGE_FILE
    L.canvas->default_image_file = IMAGE_FILE;
#endif
#ifdef IMPORT_FILE
    L.canvas->default_import_file = IMPORT_FILE;
#endif

    L.animation = animation_new(L.canvas, PLAY_COLS, PLAY_ROWS, PLAY_SIZE, PLAY_FRAMES, PLAY_FPS);
    L.brush = brush_new(L.canvas);
    L.palette = palette_new(L.camera, L.brush);
    L.canvascamctrl = canvascamctrl_new(simple->input, L.canvascam, L.brush);
    L.toolbar = toolbar_new(L.camera, L.savestate, L.canvas, L.brush, L.canvascamctrl, L.animation);
    L.inputctrl = inputctrl_new(simple->input, L.camera, L.canvascam, L.palette, L.brush, L.toolbar, L.canvascamctrl);

    L.textinput = textinput_new(simple->input, L.camera, "Your name:");

    // calls "palettepresave_PALETTE(L.palette);"
    PalettePresave(PALETTE)(L.palette);

    // save start frame
    savestate_save(L.savestate);
}

// this functions is called either each frame or at a specific update/s time
static void update(eSimple *simple, ivec2 window_size, float delta_time) {
    // simulate
    camera_update(L.camera, window_size.x, window_size.y);
    canvascam_update(L.canvascam, window_size.x, window_size.y);

    background_update(L.background, L.camera, delta_time);

    //*
    canvas_update(L.canvas, L.canvascam, delta_time);
    palette_update(L.palette, delta_time);
    animation_update(L.animation, L.camera, palette_get_hud_size(L.palette), delta_time);
    toolbar_update(L.toolbar, delta_time);
    //*/

    //textinput_update(L.textinput, delta_time);
}

// this function is calles each frame to render stuff
static void render(eSimple *simple, ivec2 window_size) {
    const mat4 *camera_mat = &L.camera->matrices.p;
    const mat4 *canvascam_mat = &L.canvascam->matrices.vp;

    background_render(L.background, camera_mat);

    //*
    animation_render(L.animation, camera_mat);
    canvas_render(L.canvas, canvascam_mat);
    palette_render(L.palette, camera_mat);
    toolbar_render(L.toolbar, camera_mat);
    //*/

    //textinput_render(L.textinput, camera_mat);
}

int main(int argc, char **argv) {
    e_simple_start("Pixelc", "Horsimann",
                   0, // updates/s, <=0 to turn off and use fps
                   init, update, render);
    return 0;
}

