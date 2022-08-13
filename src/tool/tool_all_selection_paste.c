#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/sca/int.h"
#include "u/button.h"
#include "canvas.h"
#include "selectionctrl.h"
#include "tool.h"

static void update_canvas() {
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    canvas_reload();
    selection_paste(s, canvas.RO.image, canvas.RO.current_image_layer);
}


static void rotate_l_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool selection paste rotate left");
        selection_rotate(s, false);
        update_canvas();
    }
}

Tool *tool_new_selection_paste_rotate_l() {
    return tool_button_new("rotate left",
                           "Rotates the\n"
                           "selection left",
                           "res/button_rotate_left.png",
                           rotate_l_pe,
                           NULL);
}

static void rotate_r_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool selection paste rotate right");
        selection_rotate(s, true);
        update_canvas();
    }
}

Tool *tool_new_selection_paste_rotate_r() {
    return tool_button_new("rotate right",
                           "Rotates the\n"
                           "selection right",
                           "res/button_rotate_right.png",
                           rotate_r_pe,
                           NULL);
}

static void mirror_v_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool selection paste mirror vertical");
        selection_mirror(s, true);
        update_canvas();
    }
}

Tool *tool_new_selection_paste_mirror_v() {
    return tool_button_new("flip vertical",
                           "Mirrors the\n"
                           "selection\n"
                           "vertically",
                           "res/button_vertical.png",
                           mirror_v_pe,
                           NULL);
}

static void mirror_h_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool selection paste mirror horizontal");
        selection_mirror(s, false);
        update_canvas();
    }
}

Tool *tool_new_selection_paste_mirror_h() {
    return tool_button_new("flip horizontal",
                           "Mirrors the\n"
                           "selection\n"
                           "horizontally",
                           "res/button_horizontal.png",
                           mirror_h_pe,
                           NULL);
}

static void blend_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    if (u_button_toggled(&self->ro.rect, pointer)) {
        bool pressed = u_button_is_pressed(&self->ro.rect);
        s_log("tool selection paste blend: %i", pressed);
        s->blend = pressed;
        update_canvas();
    }
}

static bool blend_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = selectionctrl.selection;
    bool active = s ? s->blend : false;
    u_button_set_pressed(&self->ro.rect, active);
    // always active
    return true;
}

Tool *tool_new_selection_paste_blend() {
    return tool_button_new("blend",
                           "Blends in the\n"
                           "previous color\n"
                           "with the\n"
                           "selection\n"
                           "alpha /\n"
                           "transparency",
                           "res/button_blend.png",
                           blend_pe,
                           blend_is_a);
}

static void copy_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool selection paste copy");
        canvas_save();
    }
}

Tool *tool_new_selection_paste_copy() {
    return tool_button_new("copy",
                           "Copies the\n"
                           "current\n"
                           "selection\n"
                           "paste",
                           "res/button_copy.png",
                           copy_pe,
                           NULL);
}

static void ok_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool selection paste ok");
        canvas_save();
        selectionctrl_stop();
    }
}

Tool *tool_new_selection_paste_ok() {
    return tool_button_new("ok",
                           "Copies the\n"
                           "current\n"
                           "selection\n"
                           "paste\n"
                           "and stops the\n"
                           "selection mode",
                           "res/button_ok.png",
                           ok_pe,
                           NULL);
}


