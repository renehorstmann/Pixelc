#include "r/texture.h"
#include "r/render.h"
#include "rhc/log.h"

struct rRenderGolabals_s r_render;

static struct {
   GLuint framebuffer_tex_fbo;
} L;

void r_render_init(SDL_Window *window) {
    r_render_error_check("r_render_initBEGIN");

    r_render.window = window;
    r_render.clear_color = (vec4) {{0, 0, 0, 1}};

    log_info("r_render_init: OpenGL version: %s", glGetString(GL_VERSION));

    int max_vertex_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);
    if (max_vertex_attributes < 16) {
        log_warn("r_render_init: OpenGL failed: only has %d/16 vertex attributes", max_vertex_attributes);
        //exit(EXIT_FAILURE);
    }
    
    int max_texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
    if (max_texture_units < 3) {
        log_warn("r_render_init: OpenGL failed: only has %d/3 framebuffer texture units", max_texture_units);
        //exit(EXIT_FAILURE);
    }
    
    // startup "empty" texture
    r_render.framebuffer_tex = r_texture2d_new_white_pixel();
    glGenFramebuffers(1, &L.framebuffer_tex_fbo);
    
    r_render_error_check("r_render_init");
}

void r_render_begin_frame(int cols, int rows) {
    r_render_error_check("r_render_begin_frameBEGIN");
    
    glViewport(0, 0, cols, rows);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(r_render.clear_color.r, r_render.clear_color.g, r_render.clear_color.b, r_render.clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
    
    r_render_error_check("r_render_begin_frame");
}

void r_render_end_frame() {
    r_render_error_check("r_render_end_frameBEGIN");
    
    SDL_GL_SwapWindow(r_render.window);

    r_render_error_check("r_render_end_frame");
}

void r_render_blit_framebuffer(int cols, int rows) {
    r_render_error_check("r_render_blit_framebufferBEGIN");

    GLint current_fbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);

    // renew texture, if size changed
    if(r_render.framebuffer_tex.size.x != cols || r_render.framebuffer_tex.size.y != rows) {
        r_texture2d_kill(&r_render.framebuffer_tex);
        r_render.framebuffer_tex = r_texture2d_new_empty(cols, rows);

        glBindFramebuffer(GL_FRAMEBUFFER, L.framebuffer_tex_fbo);
        
        // 3D not working in WebGL2
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, r_render.framebuffer_tex.tex, 0);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // actual blit calls
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, L.framebuffer_tex_fbo);
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
        switch(err) {
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
        
        if(opt_tag) {
            log_error("%s: OpenGl error: 0x%04x %s", opt_tag, err, name);
        } else {
            log_error("OpenGl error: 0x%04x %s", err, name);
        }
        
        if (errs_size < 32)
            errs[errs_size++] = err;
    }
}
