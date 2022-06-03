#include "button.h"
#include "brush.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (!button_toggled(&self->ro.rect, pointer))
        return;

    // only passed if button state toggled
    bool pressed = button_is_pressed(&self->ro.rect);
    log_info("tool shading: %i", pressed);
    brush.shading_active = pressed;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, brush.shading_active);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_shading() {
    return tool_button_new("shading",
                           "only paint above\nthe secondary color",
                           "res/button_shade.png",
                           pointer_event,
                           is_active);
}
