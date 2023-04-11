#include "u/button.h"
#include "u/pose.h"
#include "find.h"
#include "feedback.h"
#include "dialog.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;

    float *longpress_time = (float *) self->additional_data;
    if (pointer.action == E_POINTER_DOWN
        && u_pose_aa_contains(self->ro.rect.pose, pointer.pos.xy)) {
        *longpress_time = TOOL_LONG_PRESS_TIME;
    }
    if (pointer.action == E_POINTER_UP
        || !u_pose_aa_contains(self->ro.rect.pose, pointer.pos.xy)) {
        *longpress_time = 0;
    }

    if (u_button_clicked(&self->ro.rect, pointer)) {
        if(!find_is_valid()) {
            dialog_create_find();
        } else {
            find_run();
        }
    }
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    float *longpress_time = (float *) self->additional_data;
    if (*longpress_time > 0) {
        *longpress_time -= dtime;
        if (*longpress_time <= 0) {
            feedback_longpress(u_pose_get_xy(self->ro.rect.pose),
                               R_COLOR_YELLOW);
            dialog_create_find();
        }
    }

    // always active
    return true;
}

//
// public
//

Tool *tool_new_find() {
    return tool_button_new("find",
                           "Find n replace\n"
                           "with a pattern\n"
                           "template image\n\n"
                           "hold for options",
                           "res/button_find.png",
                           pointer_event,
                           is_active);
}
