#include "button.h"
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
    log_info("tool grid: %i", pressed);
    canvas.show_grid = pressed;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, canvas.show_grid);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_grid() {
    return tool_button_new("grid",
                           "shows or hides\na pixel grid",
                           "res/button_grid.png",
                           pointer_event,
                           is_active);
}
