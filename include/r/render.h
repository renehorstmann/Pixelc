#ifndef R_RENDER_H
#define R_RENDER_H

#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "core.h"

struct rRenderGolabals_s {
    vec4 clear_color;
    SDL_Window *window;
    GLuint framebuffer_tex;
    ivec2 framebuffer_tex_size;
};
extern struct rRenderGolabals_s r_render;


void r_render_init(SDL_Window *window);

// cols and rows of the current screen, see e_window
void r_render_begin_frame(int cols, int rows);

void r_render_end_frame();

// cols and rows of the current screen, see e_window
void r_render_blit_framebuffer(int cols, int rows);

void r_render_error_check();

#endif //R_RENDER_H
