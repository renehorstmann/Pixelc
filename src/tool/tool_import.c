#include "u/image.h"
#include "u/pose.h"
#include "u/button.h"
#include "dialog.h"
#include "selectionctrl.h"
#include "animation.h"
#include "tool.h"

//
// private
//

_Static_assert(sizeof(TOOL_BUTTON_ADDITIONAL_DATA_SIZE) >= sizeof(float), "wtf");

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        uImage img = u_image_new_file(1, "import.png");
        if (!u_image_valid(img)) {
            dialog_create_import();
            return;
        }
        s_log("tool import");
        selectionctrl_paste_image(img);
        u_image_kill(&img);
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
        dialog_create_import();
        u_button_set_pressed(&self->ro.rect, false);
    }
    // always actice
    return true;
}

//
// public
//

Tool *tool_new_import() {
    return tool_button_new("import",
                           "tip to load\n"
                           "import.png\n"
                           "as selection\n\n"
                           "long press to show\n"
                           "import options",
                           "res/button_import.png",
                           pointer_event,
                           is_active);
}
