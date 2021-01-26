#include "mathc/float.h"
#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "hud_camera.h"
#include "c_camera.h"
#include "background.h"
#include "canvas.h"
#include "brush.h"
#include "palette.h"
#include "palette_presave.h"
#include "input.h"


static void main_loop(float delta_time);


int main() {
    SDL_Log("Pixelc");

    // init e (environment)
    e_window_init("Pixelc");
    e_input_init();
    e_gui_init();

    // init r (render)
    r_render_init(e_window);
    r_text_default_font = TTF_OpenFont("res/fnf.ttf", 64);


    // init systems
    hud_camera_init();
    c_camera_init();
    background_init();
    canvas_init();
    brush_init();
    palette_init();
    input_init();

//    palette_presave_grayscale();
//    palette_presave_grayscale_alpha();
    palette_presave_pixilmatt();

    e_window_main_loop(main_loop);

    e_gui_kill();
    
    return 0;
}


static void main_loop(float delta_time) {
    // e updates
    e_window_update();
    e_input_update();
    

    // simulate
    hud_camera_update();
    c_camera_update();
    background_update(delta_time);
    canvas_update(delta_time);
    palette_update(delta_time);

    // render
    r_render_begin_frame(e_window_size[0], e_window_size[1]);

    background_render();
    canvas_render();
    palette_render();

    e_gui_render();

    // swap buffers
    r_render_end_frame();

    // check for opengl errors:
    r_render_error_check();
}


