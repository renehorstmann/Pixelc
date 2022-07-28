#ifndef PIXELC_SELECTIONCTRL_H
#define PIXELC_SELECTIONCTRL_H

//
// handles selections on the canvas
//

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

// in acquiring mode, the selection creation is prepared
// the next pointer event on the canvas will create the selection box
void selectionctrl_acquire();

void selectionctrl_paste_image(uImage img);


#endif //PIXELC_SELECTIONCTRL_H
