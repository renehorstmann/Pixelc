#include "u/button.h"
#include "brush.h"
#include "tool.h"

//
// private
//


static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        log_info("tool clear");
        brush_clear();
    }
}

//
// public
//

Tool *tool_new_clear() {
    return tool_button_new("clear",
                           "resets the canvas\nor selection\nto transparent",
                           "res/button_clear.png",
                           pointer_event,
                           NULL);
}
