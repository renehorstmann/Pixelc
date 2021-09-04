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


typedef void (*e_window_main_loop_fn)(float delta_time);

typedef void (*e_window_pause_callback_fn)(bool resume, void *user_data);


typedef struct eWindow eWindow;


eWindow *e_window_new(const char *name);

void e_window_kill(eWindow **self_ptr);

SDL_Window *e_window_get_sdl_window(const eWindow *self);

SDL_GLContext e_window_get_sdl_gl_context(const eWindow *self);

ivec2 e_window_get_size(const eWindow *self);

// starts the main loop (emscripten needs a main loop function)
void e_window_main_loop(eWindow *self, e_window_main_loop_fn main_loop);

// to set fullscreen, etc.
void e_window_set_screen_mode(const eWindow *self, enum e_window_screen_modes mode);

void e_window_register_pause_callback(eWindow *self, e_window_pause_callback_fn event, void *user_data);

void e_window_unregister_pause_callback(eWindow *self, e_window_pause_callback_fn event_to_unregister);

#endif //E_WINDOW_H
