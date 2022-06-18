#include "u/button.h"
#include "u/pose.h"
#include "e/io.h"
#include "rhc/str.h"
#include "rhc/file.h"
#include "brush.h"
#include "animation.h"
#include "dialog.h"
#include "tool.h"

//
// private
//

static void on_reset_all(bool ok) {
    log_info("reset all: %i", ok);
    dialog_hide();
    if(ok) {
        file_write(e_io_savestate_file_path("config.json"), strc(""), true);
        e_io_savestate_save();
        dialog_create_restart();
    }
}


static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        log_info("tool clear");
        brush_clear();
    }
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    float *longpress_time = (float *) self->additional_data;
    if (!u_button_is_pressed(&self->ro.rect)) {
        *longpress_time = 0;
        return true;
    }
    if (*longpress_time >= TOOL_LONG_PRESS_TIME)
        return true;
    *longpress_time += dtime;

    // check for longpress
    if (*longpress_time >= TOOL_LONG_PRESS_TIME) {
        animation_longpress(u_pose_get_xy(self->ro.rect.pose),
                            R_COLOR_RED);
        dialog_create_prompt("reset app", "reset the\nwhole app?", on_reset_all);
    }
    // always actice
    return true;
}

//
// public
//

Tool *tool_new_clear() {
    return tool_button_new("clear",
                           "resets the canvas\n"
                           "or selection\n"
                           "to transparent\n\n"
                           "hold to reset\n"
                           "everything",
                           "res/button_clear.png",
                           pointer_event,
                           is_active);
}
