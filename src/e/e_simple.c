// INFO: this module uses not only e/ but also parts of r/ !

#include "e/simple.h"
#include "s/s_full.h"
#include "m/sca/float.h"

#define OUT_SMOOTH_ALPHA 0.025

struct eSimple_Globals e_simple;

static struct {
    e_simple_init_fn init_fn;
    int update_deltatime_ms;
    su32 time_ms;
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

void e_simple_start(const char *title, 
                    const char *author, 
                    float startup_block_time, 
                    int update_deltatime_ms,
                    e_simple_init_fn init_fn,
                    e_simple_update_fn update_fn,
                    e_simple_render_fn render_fn) {
#ifdef NDEBUG
    s_log_set_min_level(S_LOG_WARN);
#else
    s_log_set_min_level(S_LOG_TRACE);
#endif

    s_log("starting: %s", title);

    s_assume(!L.started, "should be started just once in the main function");
    L.started = true;

    L.update_deltatime_ms = update_deltatime_ms;

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
    if (r_render_startup_update(e_window.size, e_window.deltatime)) {
        s_log("init");
        e_window_set_vsync(true);
        e_window_reset_main_loop(main_loop, NULL);
        L.init_fn();
    }
}

static void main_loop(void *user_data) {
    sTimer_s timer = s_timer_new();

    e_simple.fps = smooth_out_value(e_simple.fps, 1 / e_window.frame_deltatime);

    // e updates
    e_input_update();

    // if updates_per_second is disabled, use delta time
    if (L.update_deltatime_ms <= 0) {
        e_simple.update_fn(e_window.deltatime);
    } else {
        while (L.time_ms <= e_window.frame_time_ms) {
            L.time_ms += L.update_deltatime_ms;
            
            // reset e_window time to a miltitude of update_dtime
            e_window.time_ms = L.time_ms;
            e_window.deltatime_ms = L.update_deltatime_ms;
            e_window.deltatime = e_window.deltatime_ms/1000.0f;
            e_simple.update_fn(e_window.deltatime);
        }
    }

    double load_time = s_timer_reset(timer);

    // render
    r_render_begin_frame(e_window.size);

    e_simple.render_fn(e_window.frame_deltatime);

    // renders the debug gui windows
    e_gui_render();

    // swap buffers
    r_render_end_frame();

    double render_time = s_timer_elapsed(timer);
    double full_time = load_time + render_time;

    e_simple.load_update = sca_min(1, smooth_out_value(e_simple.load_update, load_time / e_window.frame_deltatime));
    e_simple.load_render = sca_min(1, smooth_out_value(e_simple.load_render, render_time / e_window.frame_deltatime));
    e_simple.load = sca_min(1, smooth_out_value(e_simple.load, full_time / e_window.frame_deltatime));
}
