#ifndef E_GUI_H
#define E_GUI_H


// setup nuklear
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include "nuklear/nuklear.h"

#ifdef USING_GLES
#include "nuklear/nuklear_sdl_gles2.h"
#else

#include "nuklear/nuklear_sdl_gl3.h"

#endif

#include "SDL.h"

struct eGuiGlobals_s {
    struct nk_context *ctx;
};
extern struct eGuiGlobals_s e_gui;

void e_gui_init();

void e_gui_kill();

void e_gui_render();

// creates a nuklear window to set the float attribute with a slider
void e_gui_wnd_float_attribute(const char *title, float *attribute, float min, float max, float step);

// nuklear test window
void e_gui_test();


#endif //E_GUI_H
