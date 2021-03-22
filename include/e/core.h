#ifndef E_CORE_H
#define E_CORE_H

#define GL_GLEXT_PROTOTYPES

#ifdef USING_GLEW

#include <GL/glew.h>

#endif

#include <SDL.h>

#ifndef USING_GLEW
#include <SDL_opengl.h>
#endif

#endif //E_CORE_H
