#ifndef E_WINDOW_H
#define E_WINDOW_H

//
// creates an manages an sdl window
//

#include "core.h"
#include "m/types/int.h"

enum e_window_screen_modes {
    E_WINDOW_MODE_WINDOW,
    E_WINDOW_MODE_MAXIMIZED,
    E_WINDOW_MODE_FULLSCREEN,
    E_WINDOW_NUM_MODES
};

#define E_WINDOW_MAX_PAUSE_EVENTS 32
#define E_WINDOW_MAX_RUN_ONCE_EVENTS 32


typedef struct {
    // only for desktop platforms (and web if embedded and not fullscreen)
    // defaults to: 360x640
    int window_width, window_height;

    // defaults fo: E_WINDOW_MODE_WINDOW
    enum e_window_screen_modes screen_mode;
} eWindowStartUpOptions_s;

// callback, that will be called every frame
typedef void (*e_window_main_loop_fn)(void *user_data);

// callback, that will be called on pause and resume of the window
// e. g. Android home button, browser tab unfocused
typedef void (*e_window_pause_callback_fn)(bool resume, void *user_data);



struct eWindow_Globals {
    bool init;
    SDL_Window *sdl_window;
    SDL_GLContext gl_context;

    // set this to false, if the main loop should also run on lost focus
    // default is true
    bool allow_pause;

    // will read from sdl at the start of each frame:
    ivec2 size;
    
    // time between frames
    su32 frame_time_ms;
    int frame_deltatime_ms;
    float frame_deltatime;
    // time between updates
    // if e_simple update_dtime_ms are used, this time is a multitude that time
    su32 time_ms;
    int deltatime_ms;
    float deltatime;
};
extern struct eWindow_Globals e_window;

// creates the window and inits SDL and its components
void e_window_init(const char *title, eWindowStartUpOptions_s *opt_options);

void e_window_kill();

// starts the main loop (emscripten needs a main loop function)
void e_window_main_loop(e_window_main_loop_fn main_loop, void *user_data);

// resets the main loop functions
// call this function, if the main loop has been set
void e_window_reset_main_loop(e_window_main_loop_fn main_loop, void *user_data);

// if activate is false, vsync is disabled
// if activate is true, adaptive-vsync is tried and if not available, normal vsync is applied
// call this function, if the main loop has been set
void e_window_set_vsync(bool activate);

// to set fullscreen, etc.
void e_window_set_screen_mode(enum e_window_screen_modes mode);

// sets a pause / resume callback
// e. g. Android home button, browser tab unfocused
void e_window_register_pause_callback(e_window_pause_callback_fn event, void *user_data);

// unregisters a pause / resume callback
void e_window_unregister_pause_callback(e_window_pause_callback_fn event_to_unregister);

// runs a functions on the next main loop (frame)
// thread safe
void e_window_run_once_on_main_looper(e_window_main_loop_fn runnable, void *user_data);

#endif //E_WINDOW_H
