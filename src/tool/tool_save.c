#include "u/button.h"
#include "dialog.h"
#include "io.h"
#include "tile.h"
#include "tool.h"


//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_pressed(&self->ro.rect, pointer)) {
        if (tile.active && tile.canvas_active) {
            s_log("tool save tile");
            dialog_create_save_tile();
        } else {
            s_log("tool save");
            dialog_create_save();
        }
    }
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, strcmp(dialog.id, "save") == 0);
    // always actice
    return true;
}

//
// public
//

Tool *tool_new_save() {
    return tool_button_new("save",
                           "Opens the save\n"
                           "dialog to save as\n"
                           "PNG or GIF",
                           "res/button_save.png",
                           pointer_event,
                           is_active);
}
