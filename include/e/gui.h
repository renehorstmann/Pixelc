#ifndef E_GUI_H
#define E_GUI_H

//
// debug gui, nuklear based
//

#include "core.h"
#include "m/types/float.h"

struct nk_context;


struct eGui_Globals {
    bool init;
    struct nk_context *ctx;

    // added to the nuklear render to scale the whole nuklear gui
    // reset this f. e. in the camera
    float scale;
};
extern struct eGui_Globals e_gui;


void e_gui_init();

void e_gui_kill();

// renders every window, created between the calls
void e_gui_render();

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
