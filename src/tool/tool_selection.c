#include "u/button.h"
#include "u/pose.h"
#include "selectionctrl.h"
#include "canvas.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;

    // special button, becaus inputctrl stops selectionctrl on a press down in the toolbar, if it was active
    // after handling this stuff here...

    if(pointer.action != E_POINTER_DOWN) {
        return;
    }
    if (!u_pose_aa_contains(self->ro.rect.pose, pointer.pos.xy)) {
        return;
    }

    if(selectionctrl.mode == SELECTIONCTRL_NONE) {
        s_log("tool selection: start");
        selectionctrl_acquire();
    } else {
        s_log("tool selection: stop");
        selectionctrl_stop();
        canvas_reload();
    }
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, selectionctrl.mode != SELECTIONCTRL_NONE || !selectionctrl.allowed);
    // always active
    return true;
}

//
// public
//


Tool *tool_new_selection() {
    return tool_button_new("selection",
                           "Toggle a\ncanvas selection",
                           "res/button_selection.png",
                           pointer_event,
                           is_active);
}
