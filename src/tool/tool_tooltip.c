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
        log_info("tool tooltip start");
        dialog_create_tooltip();
    } else {
        log_info("tool tooltip stop");
        dialog_hide();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    bool tooltip = strcmp(dialog.id, "tooltip") == 0;
    button_set_pressed(&self->ro.rect, tooltip);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_tooltip() {
    return tool_button_new("tooltip",
                           "click on a tool\nto get its tip",
                           "res/button_tooltip.png",
                           pointer_event,
                           is_active);
}