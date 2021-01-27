#ifndef E_WINDOW_H
#define E_WINDOW_H

#include "core.h"

typedef void (*eWindowMainLoopFn)(float delta_time);


extern SDL_Window *e_window;
extern int e_window_size[2];


void e_window_init(const char *name);

void e_window_kill();

void e_window_update();

void e_window_main_loop(eWindowMainLoopFn main_loop);


#endif //E_WINDOW
