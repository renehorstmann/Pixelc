#ifndef PIXELC_SELECTIONCTRL_H
#define PIXELC_SELECTIONCTRL_H

#include "e/input.h"
#include "selection.h"

enum selectionctrl_mode {
    SELECTIONCTRL_NONE,
    SELECTIONCTRL_ACQUIRE,
    SELECTIONCTRL_SET,
    SELECTIONCTRL_COPY,
    SELECTIONCTRL_CUT,
    SELECTIONCTRL_PASTE,
    SELECTIONCTRL_NUM_MODES
};


struct SelectionCtrl_Globals {
    Selection *selection;

    enum selectionctrl_mode mode;

    bool show_copy_cut;
    bool show_ok;
};
extern struct SelectionCtrl_Globals selectionctrl;


void selectionctrl_init();

void selectionctrl_update(float dtime);

void selectionctrl_render(const mat4 *cam_mat);

bool selectionctrl_pointer_event(ePointer_s pointer);

void selectionctrl_stop();

void selectionctrl_acquire();

void selectionctrl_paste_image(uImage img);


#endif //PIXELC_SELECTIONCTRL_H
