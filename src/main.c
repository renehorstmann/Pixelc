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
#include "toolbar.h"
#include "inputctrl.h"
#include "multitouchcursor.h"

//
// options
//

// canvas size
//*
#define COLS 32
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
#define PLAY_SIZE 1.0
#define PLAY_FRAMES 2
#define PLAY_FPS 6.0


#define BG_COLOR_A "#aaaacc"
#define BG_COLOR_B "#9999dd"

#define TB_ACTIVE_BG_A "#9999bb"
#define TB_ACTIVE_BG_B "#888888"
#define TB_SECONDARY_BG_A "#bb9999"
#define TB_SECONDARY_BG_B "#888888"
#define TB_SELECTION_BG_A "#99bb99"
#define TB_SELECTION_BG_B "#888888"

#define GRID_COLS 8
#define GRID_ROWS 8

//
// end of options
//


static struct {
    Camera_s *camera;
    Background *background;
    Canvas *canvas;
    Animation *animation;
    SelectionCtrl *selectionctrl;
    Brush *brush;
    Palette *palette;
    CameraCtrl *camctrl;
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

    L.background = background_new(u_color_from_hex(BG_COLOR_A), u_color_from_hex(BG_COLOR_B));
    L.canvas = canvas_new();

    L.animation = animation_new(L.canvas, PLAY_COLS, PLAY_ROWS, PLAY_SIZE, PLAY_FRAMES, PLAY_FPS);
    L.selectionctrl = selectionctrl_new(L.canvas);
    L.brush = brush_new(L.canvas);
    L.palette = palette_new(L.camera, L.brush);

    L.camctrl = cameractrl_new(simple->input, L.camera, L.brush);
    cameractrl_set_home(L.camctrl, L.canvas->RO.image.cols, L.canvas->RO.image.rows);

    L.toolbar = toolbar_new(L.camera, 
                            L.camctrl,
                            L.canvas,
                            L.brush, 
                            L.palette,
                            L.selectionctrl,
                            L.animation,
                            u_color_from_hex(TB_ACTIVE_BG_A),
                            u_color_from_hex(TB_ACTIVE_BG_B),
                            u_color_from_hex(TB_SECONDARY_BG_A),
                            u_color_from_hex(TB_SECONDARY_BG_B),
                            u_color_from_hex(TB_SELECTION_BG_A),
                            u_color_from_hex(TB_SELECTION_BG_B)
    );

    L.mtc = multitouchcursor_new(L.camera, L.brush, L.palette);

    L.inputctrl = inputctrl_new(simple->input, L.camera, L.camera, L.palette, L.brush, L.selectionctrl,
                                L.toolbar, L.camctrl, L.mtc);


    brush_load_config(L.brush);
    palette_load_config(L.palette);
    canvas_load_config(L.canvas);

    uImage img = u_image_new_empty(COLS, ROWS, LAYERS);
    u_image_copy_top_left(img, L.canvas->RO.image);
    canvas_set_image(L.canvas, img, false);
}

// this functions is called either each frame or at a specific update/s time
static void update(eSimple *simple, ivec2 window_size, float dtime) {
    // simulate
    camera_update(L.camera, window_size);

    background_update(L.background, L.camera, dtime);


    canvas_update(L.canvas, dtime);
    palette_update(L.palette, dtime);
    animation_update(L.animation, L.camera, palette_get_hud_size(L.palette), dtime);

    selectionctrl_update(L.selectionctrl, dtime);
    L.brush->in.selection_ref = L.selectionctrl->selection;

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
    toolbar_render(L.toolbar, hud_cam);
    palette_render(L.palette, hud_cam);
}

int main(int argc, char **argv) {
    e_simple_start("Pixelc", "Horsimann",
                   0.0f,   // startup block time (the time in which "Horsimann" is displayed at startup)
                   0,      // updates/s, <=0 to turn off and use fps
                   init, update, render);

    return 0;
}
