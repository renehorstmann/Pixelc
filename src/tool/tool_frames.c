#include "u/button.h"
#include "toolbar.h"
#include "canvas.h"
#include "cameractrl.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
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
    if(!canvas.RO.frames_enabled && active) {
        toolbar_hide_frames();
    }
    if(canvas.RO.frames_enabled && !active) {
        toolbar_show_frames();
    }
    // always active
    return true;
}

//
// public
//

Tool *tool_new_frames() {
    return tool_button_new("frames",
                           "enable / disable\n"
                           "frames and show\n"
                           "the animation",
                           "res/button_play.png",
                           pointer_event,
                           is_active);
}
