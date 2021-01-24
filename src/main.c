#include "mathc/float.h"
#include "e/e.h"
#include "r/r.h"
#include "u/u.h"

#include "c_camera.h"
#include "c_input.h"
#include "canvas.h"


static void main_loop(float delta_time);


int main() {
    puts("Pixelc");
    
    e_window_init("Pixelc");
    e_input_init();
    e_gui_init();

    r_render_init(e_window);

    // init
    r_text_default_font = TTF_OpenFont("res/fnf.ttf", 64);
    c_camera_init();
    c_camera_set_pos(10, 20);
    c_camera_set_angle(M_PI * 0.1);
    canvas_init();
    c_input_init();


    e_window_main_loop(main_loop);

    e_gui_kill();
    
    return 0;
}


static void main_loop(float delta_time) {
    
    e_window_update();
    e_input_update();
    

    // simulate
    c_camera_update();
    canvas_update(delta_time);

    // render
    r_render_begin_frame(e_window_size[0], e_window_size[1]);

    canvas_render();

    e_gui_render();

    // swap buffers
    r_render_end_frame();
    

    // check for opengl errors:
    r_render_error_check();
}


