#include "button.h"
#include "selectionctrl.h"
#include "canvas.h"
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
        log_info("tool selection: start");
        selectionctrl_acquire();
    } else {
        log_info("tool selection: stop");
        selectionctrl_stop();
        canvas_reload();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, selectionctrl.mode != SELECTIONCTRL_NONE);
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