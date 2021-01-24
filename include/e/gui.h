#ifndef E_GUI_H
#define E_GUI_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear/nuklear.h"
#ifdef GLES
#include "nuklear/nuklear_sdl_gles2.h"
#else
#include "nuklear/nuklear_sdl_gl3.h"
#endif
#include "SDL.h"

extern struct nk_context *e_gui_ctx;

void e_gui_init();

void e_gui_kill();

void e_gui_wnd_float_attribute(const char *title, float *attribute, float min, float max, float step);

void e_gui_test();

void e_gui_render();


#endif //E_GUI_H
