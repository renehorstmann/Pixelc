// INFO: this module uses not only e/ but also parts of r/ !

#include "rhc/log.h"
#include "rhc/error.h"
#include "rhc/alloc.h"

#include "e/simple.h"


static struct {
    eSimple super;
    e_simple_init_fn init_fn;
    float seconds_per_update;
    float update_time;
    bool started;
} L;


static void init_loop(float delta_time);

static void main_loop(float delta_time);


void e_simple_start(const char *title, const char *author, float startup_block_time, float updates_per_seconds,
                    e_simple_init_fn init_fn,
                    e_simple_update_fn update_fn,
                    e_simple_render_fn render_fn) {
    log_info(title);
    log_info("e_simple_start");

    assume(!L.started, "e_simple is a singleton and should be started just once in thr main function");
    L.started = true;

    if (updates_per_seconds > 0)
        L.seconds_per_update = 1.0f / updates_per_seconds;

    L.init_fn = init_fn;
    L.super.update_fn = update_fn;
    L.super.render_fn = render_fn;

    // init e (environment)
    L.super.window = e_window_new(title);
    L.super.input = e_input_new(L.super.window);
    L.super.gui = e_gui_new(L.super.window);

    ivec2 window_size = e_window_get_size(L.super.window);

    // init r (render)
    L.super.render = r_render_new(e_window_get_sdl_window(L.super.window));

    // the startup screen acts as loading screen and also checks for render errors
    r_render_show_startup(L.super.render,
                          startup_block_time,
                          author);

    // start the main loop, blocking call
    e_window_main_loop(L.super.window, init_loop);

    // clean up
    r_render_kill(&L.super.render);
    e_gui_kill(&L.super.gui);
    e_input_kill(&L.super.input);
    e_window_kill(&L.super.window);
}

static void init_loop(float delta_time) {
    ivec2 window_size = e_window_get_size(L.super.window);
    if (r_render_startup_update(L.super.render, window_size, delta_time)) {
        log_info("e_simple_init");
        e_window_set_vsync(L.super.window, true);
        e_window_reset_main_loop(L.super.window, main_loop);
        L.init_fn(&L.super, window_size);
    }
}

static void main_loop(float delta_time) {
    ivec2 window_size = e_window_get_size(L.super.window);


    // e updates
    e_input_update(L.super.input);

    // if updates_per_second is disabled, use delta time
    if (L.seconds_per_update <= 0) {
        L.super.update_fn(&L.super, window_size, delta_time);
    } else {
        L.update_time += delta_time;
        while (L.update_time >= L.seconds_per_update) {
            L.update_time -= L.seconds_per_update;
            L.super.update_fn(&L.super, window_size, L.seconds_per_update);
        }
    }

    // render
    r_render_begin_frame(L.super.render, window_size);

    L.super.render_fn(&L.super, window_size, delta_time);

    // renders the debug gui windows
    e_gui_render(L.super.gui);

    // swap buffers
    r_render_end_frame(L.super.render);
}
