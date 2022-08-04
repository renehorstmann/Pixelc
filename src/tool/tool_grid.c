#include "u/button.h"
#include "u/pose.h"
#include "canvas.h"
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

    if (!u_button_toggled(&self->ro.rect, pointer))
        return;

    // only passed if button state toggled
    bool pressed = u_button_is_pressed(&self->ro.rect);
    s_log("tool grid: %i", pressed);
    canvas.show_grid = pressed;
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, canvas.show_grid);

    float *longpress_time = (float *) self->additional_data;
    if (*longpress_time > 0) {
        *longpress_time -= dtime;
        if (*longpress_time <= 0) {
            feedback_longpress(u_pose_get_xy(self->ro.rect.pose),
                               R_COLOR_GREEN);
            feedback_longpress(u_pose_get_xy(self->ro.rect.pose),
                               (vec4) {{0.5, 0.5, 0.5, 1.0}});
            dialog_create_grid();
        }
    }

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
                           "of frames, layers\n\n"
                           "hold for options",
                           "res/button_grid.png",
                           pointer_event,
                           is_active);
}
