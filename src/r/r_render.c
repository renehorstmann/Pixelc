#include "rhc/error.h"
#include "rhc/log.h"
#include "mathc/utils/camera.h"
#include "r/texture.h"
#include "r/texture2d.h"
#include "r/ro_text.h"
#include "r/ro_particlerefract.h"
#include "r/render.h"


//
// private
//

typedef struct {
    RoText author_text;
    RoParticleRefract test;
    float remaining_time;
} StartUp;

struct rRender {
    vec4 clear_color;               // used by begin_frame
    SDL_Window *window;             // window, set by init

    // 3D (2D_ARRAY) not working in WebGL2
    rTexture2D framebuffer_tex;         // copy of the framebuffer, after blit_framebuffer
    GLuint framebuffer_tex_fbo;
    
    // if not null, startup screen was created
    StartUp *start_up;
};

//
// singleton
//
static rRender singleton;
static bool singleton_created;
//
//
//

//
// protected
//
rRender *r_render_singleton_;

//
// public
//

rRender *r_render_new(SDL_Window *window) {
    log_info("r_render_new");

    assume(!singleton_created, "r_render_new should be called only onve");
    singleton_created = true;

    r_render_error_check("r_render_newBEGIN");

    singleton.window = window;
    singleton.clear_color = (vec4) {{0, 0, 0, 1}};

    log_info("r_render_new: OpenGL version: %s", glGetString(GL_VERSION));

    int max_vertex_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);
    if (max_vertex_attributes < 16) {
        log_warn("r_render_new: OpenGL failed: only has %d/16 vertex attributes", max_vertex_attributes);
        r_exit_failure();
    }

    int max_texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
    if (max_texture_units < 3) {
        log_warn("r_render_new: OpenGL failed: only has %d/3 framebuffer texture units", max_texture_units);
        r_exit_failure();
    }

    // startup "empty" texture
    singleton.framebuffer_tex = r_texture2d_new_white_pixel();
    glGenFramebuffers(1, &singleton.framebuffer_tex_fbo);

    r_render_error_check("r_render_new");

    r_render_singleton_ = &singleton;
    return &singleton;
}

void r_render_kill(rRender **self_ptr) {
    // safe to free NULL
    if(!self_ptr)
        return;

    assume(*self_ptr == &singleton, "singleton?");
    memset(&singleton, 0, sizeof(singleton));
    *self_ptr = NULL;
}

vec4 *r_render_clear_color(rRender *self) {
    assume(self == &singleton, "singleton?");
    return &singleton.clear_color;
}

const rTexture2D *r_render_get_framebuffer_tex(const rRender *self) {
    assume(self == &singleton, "singleton?");
    return &singleton.framebuffer_tex;
}

void r_render_begin_frame(const rRender *self, ivec2 window_size) {
    assume(self == &singleton, "singleton?");
    r_render_error_check("r_render_begin_frameBEGIN");

    glViewport(0, 0, window_size.x, window_size.y);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(singleton.clear_color.r, singleton.clear_color.g, singleton.clear_color.b, singleton.clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);

    r_render_error_check("r_render_begin_frame");
}

void r_render_end_frame(const rRender *self) {
    assume(self == &singleton, "singleton?");
    r_render_error_check("r_render_end_frameBEGIN");

    SDL_GL_SwapWindow(singleton.window);

    r_render_error_check("r_render_end_frame");
}

void r_render_blit_framebuffer(const rRender *self, ivec2 window_size) {
    assume(self == &singleton, "singleton?");
    r_render_error_check("r_render_blit_framebufferBEGIN");

    GLint current_fbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);

    int cols = window_size.x;
    int rows = window_size.y;

    // renew texture, if size changed
    if (singleton.framebuffer_tex.size.x != cols || singleton.framebuffer_tex.size.y != rows) {
        r_texture2d_kill(&singleton.framebuffer_tex);
        singleton.framebuffer_tex = r_texture2d_new(cols, rows,  NULL);

        glBindFramebuffer(GL_FRAMEBUFFER, singleton.framebuffer_tex_fbo);

        // 3D not working in WebGL2
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, singleton.framebuffer_tex.tex, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // actual blit calls
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, singleton.framebuffer_tex_fbo);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, current_fbo);
    // src x0, y0, x1, y1; dst x0, y0, x1, y1   -> seems to be mirrored, so swapping dst y0 <> y1
    glBlitFramebuffer(0, 0, cols, rows, 0, rows, cols, 0, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // restore
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, current_fbo);

    r_render_error_check("r_render_blit_framebuffer");
}

bool r_render_error_check_impl_(const char *opt_tag) {
    static GLenum errs[32];
    int errs_size = 0;
    GLenum err;
    bool unexpected_error = false;
    while ((err = glGetError()) != GL_NO_ERROR) {
        for (int i = 0; i < errs_size; i++) {
            if (err == errs[i])
                continue;
        }

        const char *name;
        switch (err) {
            case 0x500:
                name = "GL_INVALID_ENUM";
                break;
            case 0x501:
                name = "GL_INVALID_VALUE";
                break;
            case 0x502:
                name = "GL_INVALID_OPERATION";
                break;
            case 0x503:
                name = "GL_STACK_OVERFLOW";
                break;
            case 0x504:
                name = "GL_STACK_UNDERFLOW";
                break;
            case 0x505:
                name = "GL_OUT_OF_MEMORY";
                break;
            case 0x506:
                name = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case 0x507:
                name = "GL_CONTEXT_LOST";
                break;
            case 0x8031:
                name = "GL_TABLE_TOO_LARGE";
                break;
            default:
                name = "UNKNOWN_ERROR?";
                break;
        }

        if (opt_tag) {
            log_error("%s: OpenGl error: 0x%04x %s", opt_tag, err, name);
        } else {
            log_error("OpenGl error: 0x%04x %s", err, name);
        }

        if (errs_size < 32)
            errs[errs_size++] = err;

        unexpected_error = true;
    }

    return unexpected_error;
}


//
// r_render_show_startup
//

#define CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

#define AUTHOR_SIZE 2.0

// copy from u/pose.h
static mat4 u_pose_new(float x, float y, float w, float h) {
    // mat4 has column major order
    return (mat4) {{
                           w, 0, 0, 0,
                           0, h, 0, 0,
                           0, 0, 1, 0,
                           x, y, 0, 1
                   }};
}


static mat4 camera(int wnd_width, int wnd_height) {
    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    float real_pixel_per_pixel = floorf(smaller_size / CAMERA_SIZE);

    float width_2 = wnd_width / (2 *  real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    float left = -floorf(width_2);
    float top = floorf(height_2);
    float right = width_2 + (width_2 - floorf(width_2));
    float bottom = -height_2 - (height_2 - floorf(height_2));
    return mat4_camera_ortho(left, right, bottom, top, -1, 1);
}

void r_render_show_startup(rRender *self, float block_time, const char *author) {
    log_info("r_render_show_startup");
    
    self->start_up = rhc_calloc(sizeof *self->start_up);
    
    self->start_up->remaining_time = block_time;
    
    self->start_up->author_text = ro_text_new_font85(32);
    vec2 text_size = ro_text_set_text(&self->start_up->author_text, author);
    self->start_up->author_text.pose = u_pose_new(-text_size.x * AUTHOR_SIZE / 2, 0, AUTHOR_SIZE, AUTHOR_SIZE);
    ro_text_set_color(&self->start_up->author_text, R_COLOR_WHITE);
    
    self->start_up->test = ro_particlerefract_new(1,
            r_texture_new_white_pixel(),
            r_texture_new_white_pixel());
    self->start_up->test.rects[0].color.a=0;
    ro_particlerefract_update(&self->start_up->test);
}

bool r_render_startup_update(rRender *self, ivec2 window_size, float delta_time) {
    if(!self->start_up)
        return true;
    
    // render
    r_render_begin_frame(self, window_size);
    mat4 cam = camera(window_size.x, window_size.y);
    ro_text_render(&self->start_up->author_text, &cam);
    r_render_blit_framebuffer(self, window_size);
    ro_particlerefract_render(&self->start_up->test, 0, &cam, 1, NULL, NULL, false);
    r_render_end_frame(self);
    
    // check error and abort
     if(r_render_error_check_impl_("e_r_startup")) {
        log_error("Unexpected OpenGL errors occured while checking in startup");
        r_exit_failure();
    }
    
    self->start_up->remaining_time -= delta_time;
    if(self->start_up->remaining_time <= 0) {
        // clean up
        ro_text_kill(&self->start_up->author_text);
        ro_particlerefract_kill(&self->start_up->test);
        rhc_free(self->start_up);
        self->start_up = NULL;
        return true;
    }
    return false;
}

