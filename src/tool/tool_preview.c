#include "u/button.h"
#include "animation.h"
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
    s_log("tool preview: %i", pressed);
    animation.show = pressed;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, animation.show);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_preview() {
    return tool_button_new("preview",
                           "shows the\nanimated preview",
                           "res/button_play.png",
                           pointer_event,
                           is_active);
}
