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
#include "feedback.h"
#include "tile.h"
#include "tooltip.h"

//
// options
//


#ifdef PIXELC_PREMIUM
#define BG_COLOR_A "#F3DF76"
#define BG_COLOR_B "#e2ce67"
#else
#define BG_COLOR_A "#aaaacc"
#define BG_COLOR_B "#9999dd"
#endif


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

    animation_init();
    selectionctrl_init();

    brush_init();
    brush_load_config();

    palette_init();
    palette_load_config();

    cameractrl_init();
    dialog_init();
    toolbar_init();
    multitouchcursor_init();
    inputctrl_init();   
    feedback_init();

    tile_init();
    tile_load_config();
    
    tooltip_init();
    tooltip_load_config();

    cameractrl_set_home();
    dialog_create_startup();

    // startup color and hide palette info on startup
    palette_set_color(s_min(1, palette.RO.palette_size-1));
    palette_set_info(NULL);
}

// this functions is called either each frame or at a specific update/s time
static void update(float dtime) {
    // simulate
    camera_update();
    cameractrl_update(dtime);
    background_update(dtime);
    canvas_update(dtime);
    palette_update(dtime);
    animation_update(dtime);

    selectionctrl_update(dtime);
    brush.selection_ref = selectionctrl.selection;

    toolbar_update(dtime);
    dialog_update(dtime);
    if (modal_active()) {
        multitouchcursor.active = false;
    }
    multitouchcursor_update(dtime);
    modal_update(dtime);
    feedback_update(dtime);

    tile_update(dtime);

    tooltip_update(dtime);
    
}

// this function is calles each frame to render stuff, dtime is the time between frames
static void render(float dtime) {
    const mat4 *hud_cam = &camera.matrices.p;
    const mat4 *canvas_cam = &camera.matrices.vp;

    background_render(hud_cam);
    animation_render(hud_cam);
    canvas_render(canvas_cam);
    selectionctrl_render(hud_cam, canvas_cam);
    toolbar_render(hud_cam);
    tooltip_render(hud_cam);
    palette_render(hud_cam);
    dialog_render(hud_cam);
    if (!modal_active()) {
        multitouchcursor_render(hud_cam);
    }
    modal_render();
    feedback_render(hud_cam);
}

int main(int argc, char **argv) {
    e_simple_start("Pixelc", "Horsimann",
                   1.0f,   // startup block time (the time in which "Horsimann" is displayed at startup)
                   0,      // update deltatime_ms, <=0 to turn off and use fps (5=200hz)
                   init, update, render);

    return 0;
}
