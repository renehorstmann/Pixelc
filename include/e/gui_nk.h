#ifndef SOME_GUI_NK_H
#define SOME_GUI_NK_H

// includes nuklear for costum windows

// setup nuklear
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include "nuklear/nuklear.h"

#ifdef OPTION_GLES
#include "nuklear/nuklear_sdl_gles2.h"
#else

#include "nuklear/nuklear_sdl_gl3.h"

#endif

#include <SDL2/SDL.h>

#endif //SOME_GUI_NK_H
