#ifndef E_WINDOW_H
#define E_WINDOW_H

#include "mathc/types/int.h"
#include "core.h"

typedef void (*eWindowMainLoopFn)(float delta_time);


extern SDL_Window *e_window;
extern ivec2 e_window_size;


void e_window_init(const char *name);

void e_window_kill();

void e_window_update();

void e_window_main_loop(eWindowMainLoopFn main_loop);

#endif //E_WINDOW
