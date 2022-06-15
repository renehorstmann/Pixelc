#include "r/r.h"
#include "u/pose.h"
#include "palette.h"
#include "tool.h"
#include "toolbar.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//

typedef struct {
    RoText name;
    RoText tip;
} Impl;

static void kill_fn(void *impl) {
    Impl *self = impl;
    ro_text_kill(&self->name);
    ro_text_kill(&self->tip);
    rhc_free(self);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->name, cam_mat);
    ro_text_render(&impl->tip, cam_mat);
}

static void set(const char *name, const char *tip) {
    Impl *impl = dialog.impl;
    ro_text_set_text(&impl->name, name);
    vec2 size = ro_text_set_text(&impl->tip, tip);
    dialog.impl_height = size.y + 24;
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    if (palette_contains_pos(pointer.pos.xy)) {
        set("palette", "tip to select\na color\n\n"
                       "swipe left or\nright to change\nthe palette\n\n"
                       "swipe up for\nmultitouchmode\n\n"
                       "hold for options");
        return true;
    }
    Tool *tool = toolbar_get_tool_by_pos(pointer.pos.xy);
    if (!tool)
        return true;
    if (strcmp(tool->name, "tooltip") == 0)
        return false;
    set(tool->name, tool->tip);
    return true;
}

static void on_action(bool ok) {
    log_info("tooltip closed, ok=%i", ok);
    dialog_hide();
}

//
// public
//

void dialog_create_tooltip() {
    dialog_hide();
    log_info("create");
    Impl *impl = rhc_calloc(sizeof *impl);
    dialog.impl = impl;

    impl->name = ro_text_new_font55(TOOL_NAME_LEN);
    ro_text_set_color(&impl->name, (vec4) {{0.9, 0.9, 0.9, 1}});

    impl->tip = ro_text_new_font85(TOOL_TIP_LEN);

    impl->name.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - 18, 1, 2);
    impl->tip.pose = u_pose_new(DIALOG_LEFT + 2, DIALOG_TOP - 36, 1, 1);
    set("tooltip", "click on a tool\nto get its tip");

    dialog_set_title("tooltip", (vec4) {{0.2, 0.6, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = tooltip_on_action;
//    dialog.opt_on_ok_cb = tooltip_on_action;
}
