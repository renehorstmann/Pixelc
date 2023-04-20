#include "u/button.h"
#include "u/pose.h"
#include "find.h"
#include "feedback.h"
#include "dialog.h"
#include "tool.h"
#include "tooltip.h"

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
            FindRunResult_s result = find_run();
            char text[256];
            int written = 0;
            for(int i=0; i<result.runs; i++) {
                written += snprintf(text+written, sizeof text - written,
                         "run: %2i  matches: %i\n"
                         "        replaced: %i\n",
                         i+1, result.matches[i],
                         result.replaced[i]);

                // snprintf returns the would have been written size, if buffer is big enough.
                // so written may be larger than the buffer
                if(written>=sizeof text) {
                    break;
                }
            }
            tooltip_set("find", text);
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

    if(strcmp(dialog.id, "find") == 0) {
        // reset press if dialog is active,
        //      else it remains active if dialog finishs
        self->ro.rect.sprite.x = 0;
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
