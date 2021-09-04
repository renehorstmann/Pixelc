#ifndef R_RENDER_H
#define R_RENDER_H

//
// base module of r
//

#include "types.h"

//struct rRenderGolabals_s {
//    vec4 clear_color;               // used by begin_frame
//    SDL_Window *window;             // window, set by init
//
//    // 3D (2D_ARRAY) not working in WebGL2
//    rTexture2D framebuffer_tex;         // copy of the framebuffer, after blit_framebuffer
//};
//extern struct rRenderGolabals_s r_render;


typedef struct rRender rRender;


rRender *r_render_new(SDL_Window *window);

void r_render_kill(rRender **self_ptr);

vec4 *r_render_clear_color(rRender *self);

const rTexture2D *r_render_get_framebuffer_tex(const rRender *self);

// starts a new frame
// cols and rows of the current screen, see e_window
void r_render_begin_frame(const rRender *self, int cols, int rows);

// swaps the framebuffer
void r_render_end_frame(const rRender *self);

// copies the current framebuffer into r_render.framebuffer_tex
// cols and rows of the current screen, see e_window
void r_render_blit_framebuffer(const rRender *self, int cols, int rows);

// checks for opengl errors and displays them
void r_render_error_check_impl_(const char *opt_tag);


//
// public function, uses glGetError
//

// checks for opengl errors and displays them
static void r_render_error_check(const char *opt_tag) {
#ifdef OPTION_GL_ERROR
    r_render_error_check_impl_(const char *opt_tag);
#endif
}

#endif //R_RENDER_H
