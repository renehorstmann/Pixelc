#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "io.h"
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
#include "modal.h"

//
// options
//


// animation + tiles
// screen size is >=180 pixel
// 16 Pixel * 11 cols = 180...
#define PLAY_COLS 1
#define PLAY_ROWS 1
#define PLAY_SIZE 1.0
#define PLAY_FRAMES 4
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


// this function will be called at the start of the app
static void init() {

    // init systems
    io_init();
    
    camera_init();
    camera_load_config();
    camera_update();

    background_init(u_color_from_hex(BG_COLOR_A), u_color_from_hex(BG_COLOR_B));

    canvas_init();
    canvas_load_config();

    animation_init(PLAY_COLS, PLAY_ROWS, PLAY_SIZE, PLAY_FRAMES, PLAY_FPS);
    selectionctrl_init();

    brush_init();
    brush_load_config();

    palette_init();
    palette_load_config();

    cameractrl_init();
    
    dialog_init();

    toolbar_init(u_color_from_hex(TB_ACTIVE_BG_A),
                 u_color_from_hex(TB_ACTIVE_BG_B),
                 u_color_from_hex(TB_SECONDARY_BG_A),
                 u_color_from_hex(TB_SECONDARY_BG_B),
                 u_color_from_hex(TB_SELECTION_BG_A),
                 u_color_from_hex(TB_SELECTION_BG_B)
    );

    multitouchcursor_init();

    inputctrl_init();

    cameractrl_set_home();
    
}

// this functions is called either each frame or at a specific update/s time
static void update(float dtime) {
    // simulate
    camera_update();
    cameractrl_update(dtime);

    background_update(dtime);


    canvas_update(dtime);
    palette_update(dtime);
    animation_update(palette_get_hud_size(), dtime);

    selectionctrl_update(dtime);
    brush.selection_ref = selectionctrl.selection;

    toolbar_update(dtime);
    dialog_update(dtime);
    if (modal_active()) {
        multitouchcursor.active = false;
    }
    multitouchcursor_update(dtime);
    modal_update(dtime);
    
}

// this function is calles each frame to render stuff, dtime is the time between frames
static void render(float dtime) {
    const mat4 *hud_cam = &camera.matrices.p;
    const mat4 *canvas_cam = &camera.matrices.vp;

    background_render(hud_cam);
    canvas_render(canvas_cam);
    selectionctrl_render(canvas_cam);
    toolbar_render(hud_cam);
    palette_render(hud_cam);
    dialog_render(hud_cam);
    if (!modal_active()) {
        multitouchcursor_render(hud_cam);
    }
    modal_render();
    animation_render(hud_cam);
}

int main(int argc, char **argv) {
    e_simple_start("Pixelc", "Horsimann",
                   0.0f,   // startup block time (the time in which "Horsimann" is displayed at startup)
                   0,      // update deltatime_ms, <=0 to turn off and use fps (5=200hz)
                   init, update, render);

    return 0;
}
