#ifndef PIXELC_SELECTIONCTRL_H
#define PIXELC_SELECTIONCTRL_H

#include "e/input.h"
#include "r/ro_types.h"
#include "canvas.h"
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


typedef struct {
    Canvas *canvas_ref;
    
    Selection *selection;
    
    enum selectionctrl_mode mode;
    
    struct {
        bool show_copy_cut;
        bool show_ok;
    } out;
    
    struct {
        RoBatch border;
        
        bool moving;
        ivec2 pos;
        ivec2 move_start_selection_lt;
        ivec2 move_start_position;
    } L;
} SelectionCtrl;

SelectionCtrl *selectionctrl_new(Canvas *canvas);

void selectionctrl_kill(SelectionCtrl **self_ptr);

void selectionctrl_update(SelectionCtrl *self, float dtime);

void selectionctrl_render(const SelectionCtrl *self, const mat4 *cam_mat);

bool selectionctrl_pointer_event(SelectionCtrl *self, ePointer_s pointer);

void selectionctrl_stop(SelectionCtrl *self);

void selectionctrl_acquire(SelectionCtrl *self);

void selectionctrl_paste_image(SelectionCtrl *self, uImage img);


#endif //PIXELC_SELECTIONCTRL_H
