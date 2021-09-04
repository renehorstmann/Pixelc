#ifndef E_GUI_H
#define E_GUI_H

//
// debug gui, nuklear based
//

struct nk_context;
struct eWindow;
typedef struct eGui eGui;

eGui *e_gui_new(const struct eWindow *window);

void e_gui_kill(eGui **self_ptr);

void e_gui_render(const eGui *self);

struct nk_context *e_gui_get_nk_context(const eGui *self);

// creates a nuklear window to set the float attribute with a slider
void e_gui_wnd_float_attribute(const eGui *self, const char *title, float *attribute, float min, float max, float step);

// nuklear test window
void e_gui_test(const eGui *self);


#endif //E_GUI_H
