#ifndef E_DEFINITIONS_H
#define E_DEFINITIONS_H

#include "core.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


#ifdef __EMSCRIPTEN__
const Uint32 E_SDL_INIT_FLAGS = SDL_INIT_VIDEO;
#else
const Uint32 E_SDL_INIT_FLAGS = SDL_INIT_EVERYTHING;
#endif


// GLES and WebGL use GLES3.0
#if defined GLES || __EMSCRIPTEN__
static const int E_GL_MAJOR_VERSION = 3;
static const int E_GL_MINOR_VERSION = 0;
static const int E_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_ES;

// GL uses GL3.3
#else
static const int E_GL_MAJOR_VERSION = 3;
static const int E_GL_MINOR_VERSION = 3;
static const int E_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;
#endif


#endif //E_DEFINITIONS_H
