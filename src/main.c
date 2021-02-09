#include "mathc/float.h"
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


static void main_loop(float delta_time);


int main(int argc, char **argv) {
    SDL_Log("Pixelc");

    // init e (environment)
    e_window_init("Pixelc");
    e_input_init();
    e_gui_init();

    // init r (render)
    r_render_init(e_window);


    // init systems
    camera_init();
    canvas_camera_init();
    background_init();
    canvas_init(16, 16);
    animation_init(2, 2);
    brush_init();
    canvas_camera_control_init();
    palette_init();
    toolbar_init();
    input_init();
    savestate_init();

//    palette_presave_grayscale();
//    palette_presave_grayscale_alpha();
    palette_presave_pixilmatt();
//    palette_presave_slso8();
//    palette_presave_gameboy();
//    palette_presave_endesga32();
//    palette_presave_endesga64();
//    palette_presave_nes();
//    palette_presave_aap64();

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
    r_render_begin_frame(e_window_size.x, e_window_size.y);

    background_render();
    canvas_render();
    animation_render();
    palette_render();
    toolbar_render();

    e_gui_render();

    // swap buffers
    r_render_end_frame();

    // check for opengl errors:
    r_render_error_check();
}


