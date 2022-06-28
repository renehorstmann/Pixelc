#include "u/button.h"
#include "canvas.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool undo");
        canvas_undo();
    }
}

static bool is_active(struct Tool *super, float dtime) {
    return canvas_undo_available();
}

//
// public
//

Tool *tool_new_undo() {
    return tool_button_new("undo",
                           "undos the last\ncanvas changes",
                           "res/button_undo.png",
                           pointer_event,
                           is_active);
}
