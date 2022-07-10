#include "u/button.h"
#include "u/pose.h"
#include "s/str.h"
#include "s/file.h"
#include "io.h"
#include "brush.h"
#include "animation.h"
#include "dialog.h"
#include "tool.h"

//
// private
//

static void on_reset_all(bool ok) {
    s_log("reset all: %i", ok);
    if(ok) {
        io_config_clear_files();
        dialog_create_restart();
    } else {
        ToolButton *self = dialog_prompt_get_user_data("reset app");
        if(!self) {
            s_log_error("could not get prompt user data");
        } else {
            u_button_set_pressed(&self->ro.rect, false);
        }
        dialog_hide();
    }
}


static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool clear");
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
        dialog_create_prompt("reset app", "reset the\nwhole app?", on_reset_all, self);
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
