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
        s_log("enable layers");
        canvas_enable_layers(true);
        toolbar_show_layer();
    } else {
        s_log("disable layers");
        canvas_enable_layers(false);
    }
    
    cameractrl_set_home();
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, canvas.RO.layers_enabled);
    bool active = toolbar_container_valid(&toolbar.layer);
    if(!canvas.RO.layers_enabled && active) {
        toolbar_hide_layer();
    }
    if(canvas.RO.layers_enabled && !active) {
        toolbar_show_layer();
    }
    
    // always active
    return true;
}

//
// public
//

Tool *tool_new_layer() {
    return tool_button_new("layer",
                           "Enable / Disable\n"
                           "layers",
                           "res/button_layer.png",
                           pointer_event,
                           is_active);
}
