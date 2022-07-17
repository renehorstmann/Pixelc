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
        s_log("tool frames: start");
        toolbar_show_frames();
    } else {
        s_log("tool frames: stop");
        toolbar_hide_frames();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, toolbar_container_valid(&toolbar.frames));
    // always active
    return true;
}

//
// public
//

Tool *tool_new_frames() {
    return tool_button_new("frames",
                           "open / close\nthe frames toolbar",
                           "res/button_play.png",
                           pointer_event,
                           is_active);
}
