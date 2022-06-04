#include "button.h"
#include "dialog.h"
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
        log_info("tool display start");
        dialog_create_display();
    } else {
        log_info("tool display stop");
        dialog_hide();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    bool active = strcmp(dialog.id, "display") == 0;
    button_set_pressed(&self->ro.rect, active);
    // always active
    return true;
}

//
// public
//


Tool *tool_new_display() {
    return tool_button_new("display",
                           "change the internal\n"
                           "display size\n\n"
                           "and the\n"
                           "rotation mode",
                           "res/button_display.png",
                           pointer_event,
                           is_active);
}
