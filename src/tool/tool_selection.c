#include "u/button.h"
#include "selectionctrl.h"
#include "canvas.h"
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
        s_log("tool selection: start");
        selectionctrl_acquire();
    } else {
        s_log("tool selection: stop");
        selectionctrl_stop();
        canvas_reload();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, selectionctrl.mode != SELECTIONCTRL_NONE);
    // always active
    return true;
}

//
// public
//


Tool *tool_new_selection() {
    return tool_button_new("selection",
                           "toggle a\ncanvas selection",
                           "res/button_selection.png",
                           pointer_event,
                           is_active);
}
