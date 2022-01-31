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
    hud_pointer.pos = mat4_mul_vec(self->camera_ref->matrices.p_inv, pointer.pos);
    // canvas pointer.pos in canvas coords
    ePointer_s c_pointer = pointer;
    c_pointer.pos = mat4_mul_vec(self->canvascam_ref->matrices.v_p_inv, pointer.pos);


    // only UP in all cases
    bool go = true;
    bool set_go = pointer.action == E_POINTER_UP;

    if (multitouchcursor_pointer_event(self->mtc_ref, hud_pointer)) 
        go = set_go;

    if (toolbar_pointer_event(self->toolbar_ref, hud_pointer))
        go = set_go;

    if (go && palette_pointer_event(self->palette_ref, hud_pointer))
        go = set_go;

    if (go && cameractrl_pointer_event(self->canvascamctrl_ref, c_pointer))
        go = set_go;
        
    if (go && selectionctrl_pointer_event(self->selectionctrl_ref, c_pointer))
        go = set_go;

    if (go)
        brush_pointer_event(self->brush_ref, c_pointer);
}


//
// public
//

InputCtrl *inputctrl_new(eInput *input, const Camera_s *camera, const Camera_s *canvascam,
                         Palette *palette, Brush *brush, 
                         SelectionCtrl *selectionctrl, Toolbar *toolbar, CameraCtrl *canvascamctrl,
                         MultiTouchCursor *mtc) {
    InputCtrl *self = rhc_calloc(sizeof *self);

    self->camera_ref = camera;
    self->canvascam_ref = canvascam;
    self->palette_ref = palette;
    self->brush_ref = brush;
    self->selectionctrl_ref = selectionctrl;
    self->toolbar_ref = toolbar;
    self->canvascamctrl_ref = canvascamctrl;
    self->mtc_ref = mtc;

    e_input_register_pointer_event(input, pointer_event, self);

    return self;
}
