#include "u/button.h"
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
    s_log("tool grid: %i", pressed);
    canvas.show_grid = pressed;
    canvas.alpha = pressed? 0.8 : 1.0;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, canvas.show_grid);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_grid() {
    return tool_button_new("grid",
                           "Blends in the\n"
                           "background\n"
                           "pixel grid\n\n"
                           "Shows the borders\n"
                           "of frames, layers",
                           "res/button_grid.png",
                           pointer_event,
                           is_active);
}
