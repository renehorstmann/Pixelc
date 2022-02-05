#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "camera.h"
#include "background.h"
#include "canvas.h"
#include "animation.h"
#include "brush.h"
#include "selectionctrl.h"
#include "cameractrl.h"
#include "palette.h"
#include "palettepresave.h"
#include "toolbar_old.h"
#include "toolbar.h"
#include "inputctrl.h"
#include "multitouchcursor.h"

//
// options
//

// canvas size
//*
#define COLS 128
#define ROWS 8
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
#define PLAY_SIZE 1.0
#define PLAY_FRAMES 1
#define PLAY_FPS 6.0

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
    Background *background;
    Canvas *canvas;
    Animation *animation;
    SelectionCtrl *selectionctrl;
    Brush *brush;
    Palette *palette;
    CameraCtrl *camctrl;
    ToolbarOld *toolbar_old;
    Toolbar *toolbar;
    InputCtrl *inputctrl;
    MultiTouchCursor *mtc;
    
} L;

// this function will be called at the start of the app
static void init(eSimple *simple, ivec2 window_size) {

    // init systems
    L.camera = rhc_calloc(sizeof *L.camera);
    *L.camera = camera_new();
    camera_update(L.camera, window_size);
    printf("%i %i %i %i\n", L.camera->RO.left, L.camera->RO.right, L.camera->RO.top, L.camera->RO.bottom);

    L.background = background_new(u_color_from_hex(BG_COLOR_A), u_color_from_hex(BG_COLOR_B));
    L.canvas = canvas_new();
#ifdef IMAGE_FILE
    L.canvas->default_image_file = IMAGE_FILE;
#endif
#ifdef IMPORT_FILE
    L.canvas->default_import_file = IMPORT_FILE;
#endif

    L.animation = animation_new(L.canvas, PLAY_COLS, PLAY_ROWS, PLAY_SIZE, PLAY_FRAMES, PLAY_FPS);
    L.selectionctrl = selectionctrl_new(L.canvas);
    L.brush = brush_new(L.canvas);
    L.palette = palette_new(L.camera, L.brush);
    
    L.camctrl = cameractrl_new(simple->input, L.camera, L.brush);
    printf("canvassize: %i %i\n", L.canvas->RO.image.cols, L.canvas->RO.image.rows);
    cameractrl_set_home(L.camctrl, L.canvas->RO.image.cols, L.canvas->RO.image.rows);
    
    L.toolbar_old = toolbar_old_new(L.camera, L.canvas, L.brush, L.selectionctrl, L.camctrl, L.animation);
    L.toolbar = toolbar_new(L.camera, L.canvas, L.brush, L.palette);
     
    L.mtc = multitouchcursor_new(L.camera, L.brush, L.palette);

    L.inputctrl = inputctrl_new(simple->input, L.camera, L.camera, L.palette, L.brush, L.selectionctrl, L.toolbar_old, L.toolbar, L.camctrl, L.mtc);

    // calls "palettepresave_PALETTE(L.palette);"
    PalettePresave(PALETTE)(L.palette);
    
    
    brush_load_config(L.brush);
    palette_load_config(L.palette);
    canvas_load_config(L.canvas);
    
    uImage img = u_image_new_empty(32, 16, 1);
    u_image_copy_top_left(img, L.canvas->RO.image);
    canvas_set_image(L.canvas, img);
}

// this functions is called either each frame or at a specific update/s time
static void update(eSimple *simple, ivec2 window_size, float dtime) {
    // simulate
    camera_update(L.camera, window_size);
    
    background_update(L.background, L.camera, dtime);

    //*
    canvas_update(L.canvas, dtime);
    palette_update(L.palette, dtime);
    animation_update(L.animation, L.camera, palette_get_hud_size(L.palette), dtime);
    
    selectionctrl_update(L.selectionctrl, dtime);
    L.brush->in.selection_ref = L.selectionctrl->selection;
    
    if(L.selectionctrl->out.show_copy_cut) {
        L.selectionctrl->out.show_copy_cut = false;
        L.toolbar_old->show_selection_copy_cut = true;
    }
    if(L.selectionctrl->out.show_ok) {
        L.selectionctrl->out.show_ok = false;
        L.toolbar_old->show_selection_ok = true;
        L.toolbar_old->show_selection_copy_cut = false;
    }
    
    //toolbar_old_update(L.toolbar_old, dtime);
    toolbar_update(L.toolbar, dtime);
    
    multitouchcursor_update(L.mtc, dtime);
    
}

// this function is calles each frame to render stuff, dtime is the time between frames
static void render(eSimple *simple, ivec2 window_size, float dtime) {
    const mat4 *hud_cam = &L.camera->matrices.p;
    const mat4 *canvas_cam = &L.camera->matrices.vp;

    background_render(L.background, hud_cam);

    
    animation_render(L.animation, hud_cam);
    canvas_render(L.canvas, canvas_cam);
    selectionctrl_render(L.selectionctrl, canvas_cam);
    multitouchcursor_render(L.mtc, hud_cam);
    palette_render(L.palette, hud_cam);
    //toolbar_old_render(L.toolbar_old, hud_cam);
    toolbar_render(L.toolbar, hud_cam);
}

int main(int argc, char **argv) {
    e_simple_start("Pixelc", "Horsimann",
                   0.0f,   // startup block time (the time in which "Horsimann" is displayed at startup)
                   0,      // updates/s, <=0 to turn off and use fps
                   init, update, render);
    return 0;
}
