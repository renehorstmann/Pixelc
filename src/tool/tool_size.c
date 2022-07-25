#include "u/button.h"
#include "dialog.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (!u_button_toggled(&self->ro.rect, pointer))
        return;

    // only passed if button state toggled
    bool pressed = u_button_is_pressed(&self->ro.rect);
    if (pressed) {
        s_log("tool size start");
        dialog_create_size();
    } else {
        s_log("tool size stop");
        dialog_hide();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    bool active = strcmp(dialog.id, "set size") == 0;
    u_button_set_pressed(&self->ro.rect, active);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_size() {
    return tool_button_new("size",
                           "Change the\n"
                           "canvas size,\n"
                           "frames size\n"
                           "and layer size",
                           "res/button_size.png",
                           pointer_event,
                           is_active);
}

