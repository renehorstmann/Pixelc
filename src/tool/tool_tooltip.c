#include "u/button.h"
#include "tooltip.h"
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
    s_log("tool tooltip: %i", pressed);
    tooltip.show = pressed;
    tooltip_save_config();
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, tooltip.show);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_tooltip() {
    return tool_button_new("tooltip",
                           "Click or hover\n"
                           "on a tool\n"
                           "to get its tip",
                           "res/button_tooltip.png",
                           pointer_event,
                           is_active);
}
