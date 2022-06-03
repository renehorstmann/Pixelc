// INFO: this module uses not only e/ but also parts of r/ !

#include "e/simple.h"
#include "rhc/rhc_full.h"
#include "mathc/sca/float.h"

#define OUT_SMOOTH_ALPHA 0.025

struct eSimple_Globals e_simple;

static struct {
    e_simple_init_fn init_fn;
    float seconds_per_update;
    float update_time;
    bool started;
} L;


static void init_loop(void *user_data);

static void main_loop(void *user_data);

// float out. fps, load*
static float smooth_out_value(float old_value, float new_value) {
    if (isnan(new_value) || isinf(new_value))
        return old_value;
    return sca_mix(old_value, new_value, OUT_SMOOTH_ALPHA);
}

void e_simple_start(const char *title, const char *author, float startup_block_time, float updates_per_seconds,
                    e_simple_init_fn init_fn,
                    e_simple_update_fn update_fn,
                    e_simple_render_fn render_fn) {
#ifdef NDEBUG
    rhc_log_set_min_level(RHC_LOG_WARN);
#else
    rhc_log_set_min_level(RHC_LOG_TRACE);
#endif

    log_info("starting: %s", title);

    assume(!L.started, "should be started just once in the main function");
    L.started = true;

    if (updates_per_seconds > 0)
        L.seconds_per_update = 1.0f / updates_per_seconds;

    L.init_fn = init_fn;
    e_simple.update_fn = update_fn;
    e_simple.render_fn = render_fn;

    // init e (environment)
    e_window_init(title);
    e_input_init();
    e_gui_init();

    // init r (render)
    r_render_init(e_window.sdl_window);

    // the startup screen acts as loading screen and also checks for render errors
    r_render_show_startup(startup_block_time,
                          author);

    // start the main loop, blocking call
    e_window_main_loop(init_loop, NULL);


    // clean up
    r_render_kill();
    e_gui_kill();
    e_input_kill();
    e_window_kill();
}

static void init_loop(void *user_data) {
    if (r_render_startup_update(e_window.size, e_window.dtime)) {
        log_info("init");
        e_window_set_vsync(true);
        e_window_reset_main_loop(main_loop, NULL);
        L.init_fn();
    }
}

static void main_loop(void *user_data) {
    RhcTimer_s timer = rhc_timer_new();

    e_simple.fps = smooth_out_value(e_simple.fps, 1 / e_window.dtime);

    // e updates
    e_input_update();

    // if updates_per_second is disabled, use delta time
    if (L.seconds_per_update <= 0) {
        e_simple.update_fn(e_window.dtime);
    } else {
        L.update_time += e_window.dtime;
        while (L.update_time >= L.seconds_per_update) {
            L.update_time -= L.seconds_per_update;
            e_simple.update_fn(L.seconds_per_update);
        }
    }

    double load_time = rhc_timer_reset(timer);

    // render
    r_render_begin_frame(e_window.size);

    e_simple.render_fn(e_window.dtime);

    // renders the debug gui windows
    e_gui_render();

    // swap buffers
    r_render_end_frame();

    double render_time = rhc_timer_elapsed(timer);
    double full_time = load_time + render_time;

    e_simple.load_update = sca_min(1, smooth_out_value(e_simple.load_update, load_time / e_window.dtime));
    e_simple.load_render = sca_min(1, smooth_out_value(e_simple.load_render, render_time / e_window.dtime));
    e_simple.load = sca_min(1, smooth_out_value(e_simple.load, full_time / e_window.dtime));
}
