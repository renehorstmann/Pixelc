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
        s_log("tool save");
        io_image_save();
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

Tool *tool_new_save() {
    return tool_button_new("save",
                           "saves the canvas\n"
                           "as image.png\n\n"
                           "long press to show\n"
                           "save options",
                           "res/button_save.png",
                           pointer_event,
                           is_active);
}
