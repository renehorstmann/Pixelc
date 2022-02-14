#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "button.h"
#include "tool.h"

static void update_canvas(ToolRefs refs) {
    Selection *s = refs.selectionctrl->selection;
    if(!s)
        return;
    canvas_reload(refs.canvas);
    selection_paste(s, refs.canvas->RO.image, refs.canvas->current_layer);
}


static void rotate_l_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = refs.selectionctrl->selection;
    if(!s)
        return;
    if (button_clicked(&self->ro.rect, pointer)) {
        log_info("tool selection paste rotate left");
        selection_rotate(s, false);
        update_canvas(refs);
    }
}
Tool *tool_new_selection_paste_rotate_l() {
    return tool_button_new("rotate left",
                           "rotates the\nselection left",
                           "res/button_rotate_left.png",
                           rotate_l_pe,
                           NULL);
}

static void rotate_r_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = refs.selectionctrl->selection;
    if(!s)
        return;
    if (button_clicked(&self->ro.rect, pointer)) {
        log_info("tool selection paste rotate right");
        selection_rotate(s, true);
        update_canvas(refs);
    }
}
Tool *tool_new_selection_paste_rotate_r() {
    return tool_button_new("rotate right",
                           "rotates the\nselection right",
                           "res/button_rotate_right.png",
                           rotate_r_pe,
                           NULL);
}

static void mirror_v_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = refs.selectionctrl->selection;
    if(!s)
        return;
    if (button_clicked(&self->ro.rect, pointer)) {
        log_info("tool selection paste mirror vertical");
        selection_mirror(s, true);
        update_canvas(refs);
    }
}
Tool *tool_new_selection_paste_mirror_v() {
    return tool_button_new("mirror vertical",
                           "mirrors the\nselection\nvertically",
                           "res/button_vertical.png",
                           mirror_v_pe,
                           NULL);
}

static void mirror_h_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = refs.selectionctrl->selection;
    if(!s)
        return;
    if (button_clicked(&self->ro.rect, pointer)) {
        log_info("tool selection paste mirror horizontal");
        selection_mirror(s, false);
        update_canvas(refs);
    }
}
Tool *tool_new_selection_paste_mirror_h() {
    return tool_button_new("mirror horizontal",
                           "mirrors the\nselection\nhorizontally",
                           "res/button_horizontal.png",
                           mirror_h_pe,
                           NULL);
}

static void blend_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = refs.selectionctrl->selection;
    if (!s)
        return;
    if (button_toggled(&self->ro.rect, pointer)) {
        bool pressed = button_is_pressed(&self->ro.rect);
        log_info("tool selection paste blend: %i", pressed);
        s->blend = pressed;
        update_canvas(refs);
    }
}
static bool blend_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    Selection *s = refs.selectionctrl->selection;
    bool active = s ? s->blend : false;
    button_set_pressed(&self->ro.rect, active);
    // always active
    return true;
}
Tool *tool_new_selection_paste_blend() {
    return tool_button_new("blend",
                           "blends alpha\nof selection",
                           "res/button_blend.png",
                           blend_pe,
                           blend_is_a);
}

static void copy_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    if (button_clicked(&self->ro.rect, pointer)) {
        log_info("tool selection paste copy");
        canvas_save(refs.canvas);
    }
}
Tool *tool_new_selection_paste_copy() {
    return tool_button_new("copy",
                           "copies the current\nselection paste",
                           "res/button_copy.png",
                           copy_pe,
                           NULL);
}

static void ok_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    if (button_clicked(&self->ro.rect, pointer)) {
        log_info("tool selection paste ok");
        canvas_save(refs.canvas);
        selectionctrl_stop(refs.selectionctrl);
    }
}
Tool *tool_new_selection_paste_ok() {
    return tool_button_new("ok",
                           "copies thecurrent\nselection paste\nand stops the\nselection mode",
                           "res/button_ok.png",
                           ok_pe,
                           NULL);
}


