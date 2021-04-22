#ifndef R_RENDER_H
#define R_RENDER_H

//
// base module of r
//

#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "core.h"
#include "texture2d.h"

struct rRenderGolabals_s {
    vec4 clear_color;               // used by begin_frame
    SDL_Window *window;             // window, set by init
    
    // 3D (2D_ARRAY) not working in WebGL2
    rTexture2D framebuffer_tex;         // copy of the framebuffer, after blit_framebuffer
};
extern struct rRenderGolabals_s r_render;


void r_render_init(SDL_Window *window);

// starts a new frame
// cols and rows of the current screen, see e_window
void r_render_begin_frame(int cols, int rows);

// swaps the framebuffer
void r_render_end_frame();

// copies the current framebuffer into r_render.framebuffer_tex
// cols and rows of the current screen, see e_window
void r_render_blit_framebuffer(int cols, int rows);

// checks for opengl errors and displays them
void r_render_error_check_impl_(const char *opt_tag);

// checks for opengl errors and displays them
static void r_render_error_check(const char *opt_tag) {
#ifdef OPTION_GL_ERROR
    r_render_error_check_impl_(const char *opt_tag);
#endif
}

#endif //R_RENDER_H
