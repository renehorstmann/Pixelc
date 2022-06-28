#include "u/button.h"
#include "toolbar.h"
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
        s_log("tool layer: start");
        toolbar_show_layer();
    } else {
        s_log("tool layer: stop");
        toolbar_hide_layer();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, toolbar_container_valid(&toolbar.layer));
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
