#include "u/button.h"
#include "cameractrl.h"
#include "brush.h"
#include "modal.h"
#include "colorpicker.h"
#include "tool.h"

//
// private
//

_Static_assert(TOOL_BUTTON_ADDITIONAL_DATA_SIZE >= sizeof (ColorPicker*), "not enough additional space");

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    ColorPicker *picker = *(ColorPicker**) self->additional_data;
    if(picker) {
        s_log_wtf("colorpicker is active while in pointer_event?");
        return;
    }
    if (u_button_pressed(&self->ro.rect, pointer)) {
        s_log("tool rgb");
        picker = colorpicker_new("Set secondary color", brush.current_color);
        modal_set_colorpicker(picker);
        // copy pointer
        *(ColorPicker**) self->additional_data = picker;
    }
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    ColorPicker *picker = *(ColorPicker**) self->additional_data;
    u_button_set_pressed(&self->ro.rect, picker != NULL);

    // handle colorpicker stuff
    if(picker) {
        if(picker->state == COLORPICKER_DONE) {
            s_log("tool rgb sets secondary color");
            brush.secondary_color = picker->color;
            brush.secondary_as_current = true;
        }
        if(picker->state != COLORPICKER_IN_PROGRESS) {
            colorpicker_kill(&picker);
            modal_set_colorpicker(NULL);
            // clear the "pointer" of self->additional_data, too
            memset(self->additional_data, 0, sizeof self->additional_data);
        }
    }

    // always active
    return true;
}

//
// public
//

Tool *tool_new_rgb() {
    return tool_button_new("rgb",
                           "Set the\n"
                           "secondary color\n"
                           "with a\n"
                           "color picker",
                           "res/button_rgb.png",
                           pointer_event,
                           is_active);
}
