#include "mathc/mat/float.h"
#include "e/input.h"
#include "hud_camera.h"
#include "c_camera.h"

#include "brush.h"
#include "palette.h"
#include "toolbar.h"
#include "input.h"


static void pointer_event(ePointer_s pointer, void *user_data) {
    
    // hud pointer.pos in hud coords
    ePointer_s hud_pointer = pointer;
    hud_pointer.pos = mat4_mul_vec(hud_camera_matrices.p_inv, pointer.pos);
        
    
    if(palette_pointer_event(hud_pointer))
        return;
        
    if(toolbar_pointer_event(hud_pointer))
        return;
        
        
    // canvas pointer.pos in canvas coords
    ePointer_s c_pointer = pointer;
    c_pointer.pos = mat4_mul_vec(c_camera_matrices.v_p_inv, pointer.pos);

    brush_pointer_event(c_pointer);
    
}

void input_init() {
    e_input_register_pointer_event(pointer_event, NULL);
}
