#ifndef R_RENDER_H
#define R_RENDER_H

//
// base module of r
//

#include "texture2d.h"
#include "framebuffer.h"

struct rRender_Globals {
    bool init;
    vec4 clear_color;               // used by begin_frame
    SDL_Window *window;             // window, set by init
    ivec2 current_window_size;      // window size of the current frame

    // 3D (2D_ARRAY) not working in WebGL2
    rTexture2D framebuffer_tex;         // copy of the framebuffer, after blit_framebuffer
    
    // defaults to false
    bool init_textures_as_filtered_linear;

    // set the current scale in your camera, default is 128 (extra high, which may result in wrong / unprecise rendering)
    // the scale is the ratio between real pixels and internal pixel units.
    // For example the "some" default camera uses a minimal viewport of 180x180 units.
    // So for a screen of 540x540 real pixels, the scale would be calculated in the camera as 3.0
    // the render objects receive the scale and will floor the center position of the pose with it.
    // in fact they will floor it with a precision of 1/2 units, so at the position of a 5x5 sprite can be set exactly
    // between 2 pixels
    float camera_scale;

    struct {
        int max_texture_size;
        int max_texture_layers;
    } limits; // read only, set by r_render_init
};
extern struct rRender_Globals r_render;


// creates the opengl context and does some error checks
void r_render_init(SDL_Window *window);

void r_render_kill();

// creates a startup screen
// also checks if the rendering got any errors and will exit the app, if so
// if block_time > 0, it will sleep so many seconds
void r_render_show_startup(float block_time, const char *author);

// updates and renders the startup screen, if created.
// calls begin and end frame itself
// returns true if the startup finished
bool r_render_startup_update(ivec2 window_size, float delta_time);

// starts a new frame
// cols and rows of the current screen, see e_window
void r_render_begin_frame(ivec2 window_size);

// swaps the framebuffer
void r_render_end_frame();

// clears the bound framebuffer with the given clear color
void r_render_clear(vec4 clear_color);

// copies the current framebuffer into r_render.framebuffer_tex
// cols and rows of the current screen, see e_window
void r_render_blit_framebuffer();

// sets a framebuffer for rendering
void r_render_set_framebuffer(rFramebuffer fbo);

// restores the framebuffer to the default window buffer
void r_render_restore_framebuffer();

// checks for opengl errors and displays them, returns true on unexpected error
bool r_render_error_check_impl_(const char *opt_tag);


//
// public function, uses glGetError
//

// checks for opengl errors and displays them
static void r_render_error_check(const char *opt_tag) {
#ifdef NDEBUG
    return;
#endif
#ifdef OPTION_GL_ERROR
    r_render_error_check_impl_(opt_tag);
#endif
}

#endif //R_RENDER_H
