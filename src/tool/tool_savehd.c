#include "u/button.h"
#include "u/pose.h"
#include "io.h"
#include "animation.h"
#include "dialog.h"
#include "tool.h"

//
// private
//

_Static_assert(sizeof(TOOL_BUTTON_ADDITIONAL_DATA_SIZE) >= sizeof(float), "wtf");

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool save hd");
        io_image_hd_save();
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
                            R_COLOR_YELLOW);
        dialog_create_save();
        u_button_set_pressed(&self->ro.rect, false);
    }
    // always actice
    return true;
}


//
// public
//

Tool *tool_new_save_hd() {
    return tool_button_new("save hd",
                           "saves the canvas\n"
                           "as hd version\n"
                           "as image_hd.png\n\n"
                           "The hd version\n"
                           "has a size of\n"
                           "at least 1024px\n\n"
                           "long press\n"
                           "for options",
                           "res/button_save_hd.png",
                           pointer_event,
                           is_active);
}
