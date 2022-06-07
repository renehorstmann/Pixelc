#include "u/button.h"
#include "cameractrl.h"
#include "canvas.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        log_info("tool camera");
        cameractrl_set_home();
    }
}

//
// public
//

Tool *tool_new_camera() {
    return tool_button_new("camera",
                           "resets the camera",
                           "res/button_camera.png",
                           pointer_event,
                           NULL);
}
