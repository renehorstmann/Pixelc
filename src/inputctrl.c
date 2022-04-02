#include "e/input.h"
#include "mathc/mat/float.h"

#include "inputctrl.h"


//
// private
//

static void pointer_event(ePointer_s pointer, void *user_data) {
    InputCtrl *self = user_data;

    // hud pointer.pos in hud coords
    ePointer_s hud_pointer = pointer;
    hud_pointer.pos = mat4_mul_vec(self->cam_ref->matrices.p_inv, pointer.pos);

    // multitouchcursor may change hud_pointer, if active
    if(multitouchcursor_pointer_event(self->mtc_ref, &hud_pointer)) {
        // always return here, multitouchcursor consumed the multi touch event
        return;
    }

    // canvas pointer.pos in canvas coords
    ePointer_s c_pointer = hud_pointer;
    c_pointer.pos=  mat4_mul_vec(self->cam_ref->matrices.v, hud_pointer.pos);

    if (dialog_pointer_event(self->dialog_ref, hud_pointer)) {
        // always return here, so the tools are not toggled
        return;
    }


    // only UP in all cases
    bool go = true;
    bool set_go = pointer.action == E_POINTER_UP;

    if (go && toolbar_pointer_event(self->toolbar_ref, hud_pointer))
        go = set_go;
    
    if (go && !self->mtc_ref->active && palette_pointer_event(self->palette_ref, hud_pointer))
        go = set_go;

    if (go && !self->mtc_ref->active && cameractrl_pointer_event(self->canvascamctrl_ref, c_pointer))
        go = set_go;
        
    if (go && selectionctrl_pointer_event(self->selectionctrl_ref, c_pointer))
        go = set_go;

    if (go)
        brush_pointer_event(self->brush_ref, c_pointer);
}


//
// public
//

InputCtrl *inputctrl_new(
        eInput *input, 
        const Camera_s *camera, 
        Palette *palette, 
        Brush *brush, 
        SelectionCtrl *selectionctrl, 
        Toolbar *toolbar,
        Dialog *dialog,
        CameraCtrl *canvascamctrl,
        MultiTouchCursor *mtc) {
    InputCtrl *self = rhc_calloc(sizeof *self);

    self->cam_ref = camera;
    self->palette_ref = palette;
    self->brush_ref = brush;
    self->selectionctrl_ref = selectionctrl;
    self->toolbar_ref = toolbar;
    self->dialog_ref = dialog;
    self->canvascamctrl_ref = canvascamctrl;
    self->mtc_ref = mtc;

    e_input_register_pointer_event(input, pointer_event, self);

    return self;
}
