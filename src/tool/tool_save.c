#include "u/button.h"
#include "dialog.h"
#include "io.h"
#include "tool.h"


// comment out or use the option to just save the png instead of opening the save dialog
// for mods like Tilec
#ifndef PIXELC_JUST_SAVE
#define OPEN_DIALOG
#endif

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
#ifdef OPEN_DIALOG
    if (u_button_pressed(&self->ro.rect, pointer)) {
        s_log("tool save");
        dialog_create_save();
    }
#else
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool save");
        io.image_save_merged = false;
        io_image_save();
    }
#endif
}

static bool is_active(struct Tool *super, float dtime) {
#ifdef OPEN_DIALOG
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, strcmp(dialog.id, "save") == 0);
#endif
    // always actice
    return true;
}

//
// public
//

Tool *tool_new_save() {
    return tool_button_new("save",
#ifdef OPEN_DIALOG
                           "Opens the save\n"
                           "dialog to save as\n"
                           "PNG or GIF",
#else
                            "Saves unmerged\n"
                            "as PNG ",
#endif
                           "res/button_save.png",
                           pointer_event,
                           is_active);
}
