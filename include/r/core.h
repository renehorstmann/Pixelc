#ifndef R_CORE_H
#define R_CORE_H

//
// as e/core.h, this file includes headers of sdl and opengl and has some color constants
//

#include <stdbool.h>

#define GL_GLEXT_PROTOTYPES

#ifdef OPTION_GLEW
#include <GL/glew.h>
#endif

#include <SDL2/SDL.h>

#ifndef OPTION_GLEW
#include <SDL2/SDL_opengl.h>
#endif

#include "mathc/types/float.h"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
// #include <emscripten/html5.h>
#endif


// exit the app, on emscripten an error message will be shown
static void r_exit_failure() {
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    EM_ASM(
            set_exit_failure_error_msg();
            );
#endif
    exit(EXIT_FAILURE);
}

static const vec4 R_COLOR_TRANSPARENT = {{0, 0, 0, 0}};
static const vec4 R_COLOR_BLACK = {{0, 0, 0, 1}};
static const vec4 R_COLOR_WHITE = {{1, 1, 1, 1}};
static const vec4 R_COLOR_RED = {{1, 0, 0, 1}};
static const vec4 R_COLOR_GREEN = {{0, 1, 0, 1}};
static const vec4 R_COLOR_BLUE = {{0, 0, 1, 1}};
static const vec4 R_COLOR_YELLOW = {{1, 1, 0, 1}};
static const vec4 R_COLOR_CYAN = {{0, 1, 1, 1}};
static const vec4 R_COLOR_MAGENTA = {{1, 0, 1, 1}};

#endif //R_CORE_H
