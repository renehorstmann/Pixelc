#ifndef E_CORE_H
#define E_CORE_H

//
// this file just includes SDL and OpenGL headers
//

#define GL_GLEXT_PROTOTYPES

#ifdef OPTION_GLEW

#include <GL/glew.h>

#endif

#include <SDL.h>

#ifndef OPTION_GLEW
#include <SDL_opengl.h>
#endif

#endif //E_CORE_H
