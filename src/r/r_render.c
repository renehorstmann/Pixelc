#include "r/render.h"

struct rRenderGolabals_s r_render;

void r_render_init(SDL_Window *window) {
    r_render.window = window;

    SDL_Log("OpenGL version: %s", glGetString(GL_VERSION));

    int max_vertex_attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);
    if (max_vertex_attributes < 16) {
        SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "OpenGL failed: only has %d/16 vertex attributes", max_vertex_attributes);
        //exit(EXIT_FAILURE);
    }
}

void r_render_begin_frame(int cols, int rows) {
    glViewport(0, 0, cols, rows);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void r_render_end_frame() {
    SDL_GL_SwapWindow(r_render.window);
}


void r_render_error_check() {
    static GLenum errs[32];
    int errs_size = 0;
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        for (int i = 0; i < errs_size; i++) {
            if (err == errs[i])
                continue;
        }
        SDL_Log("OpenGl error in a frame: 0x%04x", err);
        if (errs_size < 32)
            errs[errs_size++] = err;
    }
}
