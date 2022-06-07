#include "u/button.h"
#include "canvas.h"
#include "tool.h"

//
// private
//


static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        log_info("tool redo");
        canvas_redo();
    }
}

static bool is_active(struct Tool *super, float dtime) {
    return canvas_redo_available();
}

//
// public
//

Tool *tool_new_redo() {
    return tool_button_new("redo",
                           "redos the undone\ncanvas changes",
                           "res/button_redo.png",
                           pointer_event,
                           is_active);
}
