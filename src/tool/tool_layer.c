#include "button.h"
#include "toolbar.h"
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
    if (pressed) {
        log_info("tool layer: start");
        toolbar_show_layer();
    } else {
        log_info("tool layer: stop");
        toolbar_hide_layer();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, toolbar_container_valid(&toolbar.layer));
    // always active
    return true;
}

//
// public
//

Tool *tool_new_layer() {
    return tool_button_new("layer",
                           "open / close\nthe layer toolbar",
                           "res/button_layer.png",
                           pointer_event,
                           is_active);
}
