#ifndef R_CORE_H
#define R_CORE_H

//
// as e/core.h, this file includes headers of sdl and opengl and has some color constants
//

#define GL_GLEXT_PROTOTYPES

#ifdef USING_GLEW

#include <GL/glew.h>

#endif

#include <SDL.h>

#ifndef USING_GLEW
#include <SDL_opengl.h>
#endif

#include "mathc/types/float.h"


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
