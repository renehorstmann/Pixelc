#ifndef E_WINDOW_H
#define E_WINDOW_H

//
// creates an manages an sdl window
//

#include <stdbool.h>
#include "mathc/types/int.h"
#include "core.h"

enum e_window_screen_modes {
    E_WINDOW_MODE_WINDOW,
    E_WINDOW_MODE_MAXIMIZED,
    E_WINDOW_MODE_FULLSCREEN,
    E_WINDOW_NUM_MODES
};

#define E_WINDOW_MAX_PAUSE_EVENTS 32

// callback, that will be called every frame
typedef void (*e_window_main_loop_fn)(float delta_time);

// callback, that will be called on pause and resume of the window
// e. g. Android home button, browser tab unfocused
typedef void (*e_window_pause_callback_fn)(bool resume, void *user_data);


typedef struct eWindow eWindow;


// creates the (singleton) window and inits SDL and its components
eWindow *e_window_new(const char *title);

void e_window_kill(eWindow **self_ptr);

SDL_Window *e_window_get_sdl_window(const eWindow *self);

SDL_GLContext e_window_get_sdl_gl_context(const eWindow *self);

// starts the main loop (emscripten needs a main loop function)
void e_window_main_loop(eWindow *self, e_window_main_loop_fn main_loop);

// resets the main loop functions
// call this function, if the main loop has been set
void e_window_reset_main_loop(eWindow *self, e_window_main_loop_fn main_loop);

// returns the windows canvas pixel size
ivec2 e_window_get_size(const eWindow *self);

// if activate is false, vsync is disables
// if activate is true, adaptive-vsync is tried and if not available, normal vsync is applied
// call this function, if the main loop has been set
void e_window_set_vsync(const eWindow *self, bool activate);

// to set fullscreen, etc.
void e_window_set_screen_mode(const eWindow *self, enum e_window_screen_modes mode);

// sets a pause / resume callback
// e. g. Android home button, browser tab unfocused
void e_window_register_pause_callback(eWindow *self, e_window_pause_callback_fn event, void *user_data);

// unregisters a pause / resume callback
void e_window_unregister_pause_callback(eWindow *self, e_window_pause_callback_fn event_to_unregister);

#endif //E_WINDOW_H
