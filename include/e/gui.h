#ifndef E_GUI_H
#define E_GUI_H

//
// debug gui, nuklear based
// is a singleton / module
// window functions dont need the eGui handle
//

#include "mathc/types/float.h"

struct nk_context;
struct eWindow;
typedef struct eGui eGui;

// creates the singleton
eGui *e_gui_new(const struct eWindow *window);

void e_gui_kill(eGui **self_ptr);

// renders every window, created between the calls
// safe to pass NULL
void e_gui_render(const eGui *self);

// returns the nuklear context for self made windows
// if gui is not created, NULL is returned
struct nk_context *e_gui_get_nk_context();

// creates a nuklear window to set the float attribute
// safe to call if gui is not created
void e_gui_float(const char *title, float *attribute, float min, float max);


// creates a nuklear window to set the vec2 attribute
// safe to call if gui is not created
void e_gui_vec2(const char *title, vec2 *attribute, vec2 min, vec2 max);

// creates a nuklear window to set the vec3 attribute
// safe to call if gui is not created
void e_gui_vec3(const char *title, vec3 *attribute, vec3 min, vec3 max);

// creates a nuklear window to set the vec4 attribute
// safe to call if gui is not created
void e_gui_vec4(const char *title, vec4 *attribute, vec4 min, vec4 max);

// creates a nuklear window to set a color attribute
// safe to call if gui is not created
void e_gui_rgb(const char *title, vec3 *attribute);

// creates a nuklear window to set a color (with alpha) attribute
// safe to call if gui is not created
void e_gui_rgba(const char *title, vec4 *attribute);

// nuklear test window
// safe to call if gui is not created
void e_gui_test();


#endif //E_GUI_H
