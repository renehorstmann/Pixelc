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
#include "dialog.h"
#include "inputctrl.h"
#include "multitouchcursor.h"

//
// options
//


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
    Dialog *dialog;
    InputCtrl *inputctrl;
    MultiTouchCursor *mtc;

} L;

// this function will be called at the start of the app
static void init(eSimple *simple, ivec2 window_size) {

    // init systems
    L.camera = rhc_calloc(sizeof *L.camera);
    *L.camera = camera_new();
    camera_load_config(L.camera);
    camera_update(L.camera, window_size);

    L.background = background_new(u_color_from_hex(BG_COLOR_A), u_color_from_hex(BG_COLOR_B));
    
    L.canvas = canvas_new();
    canvas_load_config(L.canvas);

    L.animation = animation_new(L.canvas, PLAY_COLS, PLAY_ROWS, PLAY_SIZE, PLAY_FRAMES, PLAY_FPS);
    L.selectionctrl = selectionctrl_new(L.canvas);
    
    L.brush = brush_new(L.canvas);
    brush_load_config(L.brush);
    
    L.palette = palette_new(L.camera, L.brush);
    palette_load_config(L.palette);  

    L.camctrl = cameractrl_new(simple->input, L.camera, L.brush);
    cameractrl_set_home(L.camctrl, L.canvas->RO.image.cols, L.canvas->RO.image.rows);
    
    L.dialog = dialog_new();

    L.toolbar = toolbar_new(simple->window,
                            simple->input,
                            L.camera,
                            L.camctrl,
                            L.canvas,
                            L.brush, 
                            L.palette,
                            L.selectionctrl,
                            L.dialog,
                            L.animation,
                            u_color_from_hex(TB_ACTIVE_BG_A),
                            u_color_from_hex(TB_ACTIVE_BG_B),
                            u_color_from_hex(TB_SECONDARY_BG_A),
                            u_color_from_hex(TB_SECONDARY_BG_B),
                            u_color_from_hex(TB_SELECTION_BG_A),
                            u_color_from_hex(TB_SELECTION_BG_B)
    );
    
    L.mtc = multitouchcursor_new(L.camera, L.palette);

    L.inputctrl = inputctrl_new(simple->input, 
            L.camera,
            L.palette, 
            L.brush, 
            L.selectionctrl,
            L.toolbar, 
            L.dialog,
            L.camctrl, 
            L.mtc);

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
    dialog_update(L.dialog, dtime);
    if(L.dialog->out.textinput_active) {
        L.mtc->active = false;
    }
    multitouchcursor_update(L.mtc, dtime);
}

// this function is calles each frame to render stuff, dtime is the time between frames
static void render(eSimple *simple, ivec2 window_size, float dtime) {
    const mat4 *hud_cam = &L.camera->matrices.p;
    const mat4 *canvas_cam = &L.camera->matrices.vp;

    background_render(L.background, hud_cam);
    canvas_render(L.canvas, canvas_cam);
    selectionctrl_render(L.selectionctrl, canvas_cam);
    toolbar_render(L.toolbar, hud_cam);
    if(L.dialog->out.textinput_active) {
        palette_render(L.palette, hud_cam);
        dialog_render(L.dialog, hud_cam);
    } else {
        dialog_render(L.dialog, hud_cam);
        multitouchcursor_render(L.mtc, hud_cam);
        palette_render(L.palette, hud_cam);
    }
    animation_render(L.animation, hud_cam);
}

int main(int argc, char **argv) {
    e_simple_start("Pixelc", "Horsimann",
                   0.0f,   // startup block time (the time in which "Horsimann" is displayed at startup)
                   0,      // updates/s, <=0 to turn off and use fps
                   init, update, render);

    return 0;
}
