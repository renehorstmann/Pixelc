#include "button.h"
#include "animation.h"
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
    log_info("tool preview: %i", pressed);
    animation.show = pressed;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, animation.show);
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
