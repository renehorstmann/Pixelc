#include "rhc/error.h"
#include "rhc/log.h"
#include "r/texture2d.h"
#include "r/render.h"


//
// private
//

struct rRender {
    vec4 clear_color;               // used by begin_frame
    SDL_Window *window;             // window, set by init

    // 3D (2D_ARRAY) not working in WebGL2
    rTexture2D framebuffer_tex;         // copy of the framebuffer, after blit_framebuffer
    GLuint framebuffer_tex_fbo;
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
        //exit(EXIT_FAILURE);
    }

    int max_texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
    if (max_texture_units < 3) {
        log_warn("r_render_new: OpenGL failed: only has %d/3 framebuffer texture units", max_texture_units);
        //exit(EXIT_FAILURE);
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

void r_render_begin_frame(const rRender *self, int cols, int rows) {
    assume(self == &singleton, "singleton?");
    r_render_error_check("r_render_begin_frameBEGIN");

    glViewport(0, 0, cols, rows);
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

void r_render_blit_framebuffer(const rRender *self, int cols, int rows) {
    assume(self == &singleton, "singleton?");
    r_render_error_check("r_render_blit_framebufferBEGIN");

    GLint current_fbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);

    // renew texture, if size changed
    if (singleton.framebuffer_tex.size.x != cols || singleton.framebuffer_tex.size.y != rows) {
        r_texture2d_kill(&singleton.framebuffer_tex);
        singleton.framebuffer_tex = r_texture2d_new_empty(cols, rows);

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

void r_render_error_check_impl_(const char *opt_tag) {
#ifdef NDEBUG
    return
#endif

    static GLenum errs[32];
    int errs_size = 0;
    GLenum err;
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
    }
}
