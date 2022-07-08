#include "u/button.h"
#include "dialog.h"
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
        s_log("tool tab start");
        dialog_create_tab();
    } else {
        s_log("tool tab stop");
        dialog_hide();
    }

}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    bool active = strcmp(dialog.id, "tab") == 0;
    u_button_set_pressed(&self->ro.rect, active);
    // always active
    return true;
}

//
// public
//


Tool *tool_new_tab() {
    return tool_button_new("tab",
                           "select one of\n"
                           "nine different\n"
                           "images to edit",
                           "res/button_tab.png",
                           pointer_event,
                           is_active);
}

