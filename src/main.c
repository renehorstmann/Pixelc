#include "mathc/float.h"
#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "brush.h"
#include "c_camera.h"
#include "canvas.h"
#include "input.h"
#include "hud_camera.h"
#include "palette.h"
#include "palette_presave.h"


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
    brush_init();
    c_camera_init();
    canvas_init();
    input_init();
    hud_camera_init();
    palette_init();
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
    c_camera_update();
    canvas_update(delta_time);
    hud_camera_update();
    palette_update(delta_time);

    // render
    r_render_begin_frame(e_window_size[0], e_window_size[1]);

    canvas_render();
    palette_render();

    e_gui_render();

    // swap buffers
    r_render_end_frame();

    // check for opengl errors:
    r_render_error_check();
}


