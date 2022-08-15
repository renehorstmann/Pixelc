#include "u/button.h"
#include "tile.h"
#include "cameractrl.h"
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
    s_log("tool tile");
    tile.active = pressed;
    tile_save_config();
    cameractrl_set_home();
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, tile.active);
    // always active
    return true;
}

//
// public
//

Tool *tool_new_tile() {
    return tool_button_new("tile",
                           "Switch to the\n"
                           "tiling mode",
                           "res/button_tile.png",
                           pointer_event,
                           is_active);
}

