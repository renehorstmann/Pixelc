#ifndef R_RENDER_H
#define R_RENDER_H

//
// base module of r
//

#include <stdbool.h>
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

// creates the opengl context and does some error checks
rRender *r_render_new(SDL_Window *window);

void r_render_kill(rRender **self_ptr);

// returns a pointer to the clear color, to read and write
vec4 *r_render_clear_color(rRender *self);

// creates a startup screen
// also checks if the rendering got any errors and will exit the app, if so
// if block_time > 0, it will sleep so many seconds
void r_render_show_startup(rRender *self, float block_time, const char *author);

// updates and renders the startup screen, if created.
// calls begin and end frame itself
// returns true if the startup finished
bool r_render_startup_update(rRender *self, ivec2 window_size, float delta_time);

// returns the last blitted framebuffer, see r_render_blit_framebuffer
// the default rTexture (3D texture) does not work on some devices
const rTexture2D *r_render_get_framebuffer_tex(const rRender *self);

// starts a new frame
// cols and rows of the current screen, see e_window
void r_render_begin_frame(const rRender *self, ivec2 window_size);

// swaps the framebuffer
void r_render_end_frame(const rRender *self);

// copies the current framebuffer into r_render.framebuffer_tex
// cols and rows of the current screen, see e_window
void r_render_blit_framebuffer(const rRender *self, ivec2 window_size);

// checks for opengl errors and displays them, returns true on unexpected error
bool r_render_error_check_impl_(const char *opt_tag);


//
// public function, uses glGetError
//

// checks for opengl errors and displays them
static void r_render_error_check(const char *opt_tag) {
#ifdef NDEBUG
    return
#endif
#ifdef OPTION_GL_ERROR
    r_render_error_check_impl_(const char *opt_tag);
#endif
}

#endif //R_RENDER_H
