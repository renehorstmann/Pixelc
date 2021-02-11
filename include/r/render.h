#ifndef R_RENDER_H
#define R_RENDER_H

#include "core.h"

struct rRenderGolabals_s {
    SDL_Window *window;
};
extern struct rRenderGolabals_s r_render;


void r_render_init(SDL_Window *window);

void r_render_begin_frame(int cols, int rows);

void r_render_end_frame();

void r_render_error_check();

#endif //R_RENDER_H
