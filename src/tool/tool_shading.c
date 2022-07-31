#include "u/button.h"
#include "brush.h"
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
    s_log("tool shading: %i", pressed);
    brush.shading_active = pressed;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, brush.shading_active);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_shading() {
    return tool_button_new("shading",
                           "Only paint above\n"
                           "the secondary color\n\n"
                           "flashes the screen\n"
                           "while active",
                           "res/button_shade.png",
                           pointer_event,
                           is_active);
}
