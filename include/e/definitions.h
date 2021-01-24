#ifndef E_DEFINITIONS_H
#define E_DEFINITIONS_H

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


#ifdef __EMSCRIPTEN__
const Uint32 E_SDL_INIT_FLAGS = SDL_INIT_VIDEO;
#else
const Uint32 E_SDL_INIT_FLAGS = SDL_INIT_EVERYTHING;
#endif


#if defined GLES || __EMSCRIPTEN__
static const int E_GL_MAJOR_VERSION = 3;
static const int E_GL_MINOR_VERSION = 0;
static const int E_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_ES;
#else
static const int E_GL_MAJOR_VERSION = 3;
static const int E_GL_MINOR_VERSION = 3;
static const int E_GL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;
#endif


#endif //E_DEFINITIONS_H
