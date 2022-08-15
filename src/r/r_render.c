#include "m/utils/camera.h"
#include "r/texture.h"
#include "r/texture2d.h"
#include "r/ro_text.h"
#include "r/ro_particlerefract.h"
#include "r/render.h"

struct rRender_Globals r_render;

//
// private
//

typedef struct {
    RoText author_text;
    RoParticleRefract test;
    float remaining_time;
} StartUp;

static struct {
    rFramebuffer framebuffer_window;

    GLuint framebuffer_tex_fbo;
    // if not null, startup screen was created
    StartUp *start_up;
} L;


//
// public
//

void r_render_init(SDL_Window *window) {
    s_assume(!r_render.init, "r_render_init should be called only once");
    r_render.init = true;
    s_log("init");

    r_render_error_check("r_render_initBEGIN");

    r_render.window = window;
    r_render.clear_color = (vec4) {{0, 0, 0, 1}};

    s_log("OpenGL version: %s", glGetString(GL_VERSION));

    int max_vertex_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);
    if (max_vertex_attributes < 16) {
        s_log_warn("OpenGL failed: only has %d/16 vertex attributes", max_vertex_attributes);
        r_exit_failure();
    }

    int max_texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
    if (max_texture_units < 3) {
        s_log_warn("OpenGL failed: only has %d/3 framebuffer texture units", max_texture_units);
        r_exit_failure();
    }

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &r_render.limits.max_texture_size);
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &r_render.limits.max_texture_layers);
    s_log("OpenGL texture limits: size=%i; layers=%i",
          r_render.limits.max_texture_size, r_render.limits.max_texture_layers);

    // startup "empty" texture
    r_render.framebuffer_tex = r_texture2d_new_white_pixel();
    glGenFramebuffers(1, &L.framebuffer_tex_fbo);

    // get the default window framebuffer
    GLint current_fbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
    L.framebuffer_window.fbo = current_fbo;


    r_render_error_check("r_render_init");
}

void r_render_kill() {
    if (!r_render.init)
        return;

    memset(&r_render, 0, sizeof r_render);
    memset(&L, 0, sizeof L);
}

void r_render_begin_frame(ivec2 window_size) {
    r_render_error_check("r_render_begin_frameBEGIN");

    // update window framebuffer reference
    L.framebuffer_window.tex.size = window_size;

    r_render.current_window_size = window_size;

    r_render_restore_framebuffer();

    r_render_clear(r_render.clear_color);

    r_render_error_check("r_render_begin_frame");
}

void r_render_end_frame() {
    r_render_error_check("r_render_end_frameBEGIN");

    SDL_GL_SwapWindow(r_render.window);

    r_render_error_check("r_render_end_frame");
}

void r_render_clear(vec4 clear_color) {
    r_render_error_check("r_render_clearBEGIN");
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
    r_render_error_check("r_render_clear");
}

void r_render_blit_framebuffer() {
    r_render_error_check("r_render_blit_framebufferBEGIN");

    GLint current_draw_fbo, current_read_fbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &current_draw_fbo);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &current_read_fbo);

    int cols = r_render.current_window_size.x;
    int rows = r_render.current_window_size.y;

    // renew texture, if size changed
    if (r_render.framebuffer_tex.size.x != cols || r_render.framebuffer_tex.size.y != rows) {
        r_texture2d_kill(&r_render.framebuffer_tex);
        r_render.framebuffer_tex = r_texture2d_new(cols, rows, NULL);

        glBindFramebuffer(GL_FRAMEBUFFER, L.framebuffer_tex_fbo);

        // 3D not working in WebGL2
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, r_render.framebuffer_tex.tex, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // actual blit calls
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, L.framebuffer_tex_fbo);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, current_draw_fbo);
    // src x0, y0, x1, y1; dst x0, y0, x1, y1   -> seems to be mirrored, so swapping dst y0 <> y1
    glBlitFramebuffer(0, 0, cols, rows, 0, rows, cols, 0, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // restore
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, current_draw_fbo);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, current_read_fbo);

    r_render_error_check("r_render_blit_framebuffer");
}

void r_render_set_framebuffer(rFramebuffer fbo) {
    r_render_error_check("r_render_set_framebufferBEGIN");
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.fbo);
    glViewport(0, 0, fbo.tex.size.x, fbo.tex.size.y);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    r_render_error_check("r_render_set_framebuffer");
}

void r_render_restore_framebuffer() {
    r_render_set_framebuffer(L.framebuffer_window);
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
            s_log_error("%s: OpenGl error: 0x%04x %s", opt_tag, err, name);
        } else {
            s_log_error("OpenGl error: 0x%04x %s", err, name);
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

    float width_2 = wnd_width / (2 * real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    float left = -floorf(width_2);
    float top = floorf(height_2);
    float right = width_2 + (width_2 - floorf(width_2));
    float bottom = -height_2 - (height_2 - floorf(height_2));
    return mat4_camera_ortho(left, right, bottom, top, -1, 1);
}

void r_render_show_startup(float block_time, const char *author) {
    s_log("startup");

    L.start_up = s_malloc0(sizeof *L.start_up);

    L.start_up->remaining_time = block_time;

    L.start_up->author_text = ro_text_new_font85(32);
    vec2 text_size = ro_text_set_text(&L.start_up->author_text, author);
    L.start_up->author_text.pose = u_pose_new(-text_size.x * AUTHOR_SIZE / 2, 0, AUTHOR_SIZE, AUTHOR_SIZE);
    ro_text_set_color(&L.start_up->author_text, R_COLOR_WHITE);

    rTexture a = r_texture_new_white_pixel();
    rTexture b = r_texture_new_white_pixel();
    L.start_up->test = ro_particlerefract_new(1, a, b);
    L.start_up->test.rects[0].color.a = 0;
}

bool r_render_startup_update(ivec2 window_size, float delta_time) {
    if (!L.start_up)
        return true;

    // render
    r_render_begin_frame(window_size);
    mat4 cam = camera(window_size.x, window_size.y);
    ro_text_render(&L.start_up->author_text, &cam);
    r_render_blit_framebuffer();
    ro_particlerefract_render(&L.start_up->test, 0, &cam, 1, NULL, NULL);
    r_render_end_frame();

    // check error and abort
    if (r_render_error_check_impl_("e_r_startup")) {
        s_log_error("Unexpected OpenGL errors occured while checking in startup");
        r_exit_failure();
    }

    L.start_up->remaining_time -= delta_time;
    if (L.start_up->remaining_time <= 0) {
        // clean up
        ro_text_kill(&L.start_up->author_text);
        ro_particlerefract_kill(&L.start_up->test);
        s_free(L.start_up);
        L.start_up = NULL;
        return true;
    }
    return false;
}

