#ifndef E_WINDOW_H
#define E_WINDOW_H

//
// creates an manages an sdl window
//

#include <stdbool.h>
#include "mathc/types/int.h"
#include "core.h"


#define E_WINDOW_MAX_PAUSE_EVENTS 32

struct eWindowGlobals_s {
    SDL_Window *window;
    SDL_GLContext gl_context;
    ivec2 size;
};
extern struct eWindowGlobals_s e_window;


typedef void (*e_window_main_loop_fn)(float delta_time);

typedef void (*e_window_pause_callback_fn)(bool resume, void *user_data);


void e_window_init(const char *name);

void e_window_kill();

// starts the main loop (emscripten needs a main loop function)
void e_window_main_loop(e_window_main_loop_fn main_loop);

void e_window_register_pause_callback(e_window_pause_callback_fn event, void *user_data);

void e_window_unregister_pause_callback(e_window_pause_callback_fn event_to_unregister);

#endif //E_WINDOW
