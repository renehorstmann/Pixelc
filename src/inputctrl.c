#include "e/input.h"
#include "m/mat/float.h"

#include "multitouchcursor.h"
#include "dialog.h"
#include "camera.h"
#include "palette.h"
#include "cameractrl.h"
#include "brush.h"
#include "canvas.h"
#include "toolbar.h"
#include "tooltip.h"
#include "inputctrl.h"


//
// private
//

static void pointer_event(ePointer_s pointer, void *user_data) {
    // hud pointer.pos in hud coords
    ePointer_s hud_pointer = pointer;
    hud_pointer.pos = mat4_mul_vec(camera.matrices.p_inv, pointer.pos);

    // multitouchcursor may change hud_pointer, if active
    if (multitouchcursor_pointer_event(&hud_pointer)) {
        // always return here, multitouchcursor consumed the multi touch event
        return;
    }

    // canvas pointer.pos in canvas coords
    ePointer_s c_pointer = hud_pointer;
    c_pointer.pos = mat4_mul_vec(camera.matrices.v, hud_pointer.pos);

    if (dialog_pointer_event(hud_pointer)) {
        // always return here, so the tools are not toggled
        return;
    }


    // only UP in all cases
    bool go = true;
    bool set_go = pointer.action == E_POINTER_UP;

    bool selectionctrl_acquired = selectionctrl.mode == SELECTIONCTRL_ACQUIRE;
    bool toolbar_used = false;
    bool palette_used = false;

    if (go && toolbar_pointer_event(hud_pointer)) {
        toolbar_used = true;
        go = set_go;
    }

    if (go && !multitouchcursor.active && palette_pointer_event(hud_pointer)) {
        palette_used = true;
        go = set_go;
    }

    if (go && !multitouchcursor.active && cameractrl_pointer_event(c_pointer)) {
        go = set_go;
    }

    if (go && selectionctrl_pointer_event(c_pointer)) {
        go = set_go;
    }

    if (go) {
        brush_pointer_event(c_pointer);
    }

    if(pointer.action == E_POINTER_DOWN && (toolbar_used)) {

        // if selectionctrl is aquiring, we stop it if not pressed down in the canvas
        // dont test mode here, because it may be aquired during the pointer events...
        if(selectionctrl_acquired) {
            selectionctrl_stop();
        }
    }
}

static void key_event(const SDL_Event *event, void *user_data) {
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_AC_BACK) {
        s_log("key back");
        canvas_undo();
        tooltip_set("undo",
                    "Undos the last\n"
                    "canvas changes");
    }
}

//
// public
//

void inputctrl_init() {
    e_input_register_pointer_event_with_hovering(pointer_event, NULL);
    e_input_register_key_raw_event(key_event, NULL);
}
