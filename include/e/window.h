#ifndef E_WINDOW_H
#define E_WINDOW_H

#include "mathc/types/int.h"
#include "core.h"

struct eWindowGlobals_s {
	SDL_Window *window;
    ivec2 size;
};
extern struct eWindowGlobals_s e_window; 


typedef void (*eWindowMainLoopFn)(float delta_time);



void e_window_init(const char *name);

void e_window_kill();

void e_window_update();

void e_window_main_loop(eWindowMainLoopFn main_loop);

#endif //E_WINDOW
