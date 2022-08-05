#include "u/button.h"
#include "u/pose.h"
#include "toolbar.h"
#include "canvas.h"
#include "cameractrl.h"
#include "animation.h"
#include "feedback.h"
#include "dialog.h"
#include "tool.h"

// comment out or use the option to hide the animation preview and dialog
// for mods like Tilec
#ifndef PIXELC_HIDE_ANIMATION
#define SHOW_ANIMATION
#endif

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
    if (pressed) {
        s_log("enable frames");
        canvas_enable_frames(true);
    } else {
        s_log("disble frames");
        canvas_enable_frames(false);
    }

    cameractrl_set_home();
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, canvas.RO.frames_enabled);
    bool active = toolbar_container_valid(&toolbar.frames);
    if (!canvas.RO.frames_enabled && active) {
        toolbar_hide_frames();
#ifdef SHOW_ANIMATION
        animation.show = false;
#endif
    }
    if (canvas.RO.frames_enabled && !active) {
        toolbar_show_frames();
#ifdef SHOW_ANIMATION
        animation.show = true;
#endif
    }

    float *longpress_time = (float *) self->additional_data;
    if (*longpress_time > 0) {
        *longpress_time -= dtime;
        if (*longpress_time <= 0) {
#ifdef SHOW_ANIMATION
            feedback_longpress(u_pose_get_xy(self->ro.rect.pose),
                               R_COLOR_GREEN);
            dialog_create_animation();
#endif
        }
    }

    // always active
    return true;
}

//
// public
//

Tool *tool_new_frames() {
    return tool_button_new("frames",
#ifdef SHOW_ANIMATION
                           "Enable / disable\n"
                           "frames and show\n"
                           "the animation\n\n"
                           "Hold for\n"
                           "animation options",
#else
                            "Enable / disable\n"
                           "frames",
#endif
                           "res/button_play.png",
                           pointer_event,
                           is_active);
}
