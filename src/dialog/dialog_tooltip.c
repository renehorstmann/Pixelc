#include "r/r.h"
#include "u/pose.h"
#include "palette.h"
#include "tool.h"
#include "toolbar.h"
#include "dialog.h"


static const uColor_s BG_A_COLOR = {{102, 136, 102, 255}};
static const uColor_s BG_B_COLOR = {{102, 143, 102, 255}};
static const vec4 TITLE_COLOR = {{0.7, 0.7, 0.7, 1}};

//
// private
//

typedef struct {
    RoText name;
    RoText tip;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->name);
    ro_text_kill(&impl->tip);
    s_free(impl);
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
    if(pointer.action == E_POINTER_HOVER)
        return false;
    
    if (palette_contains_pos(pointer.pos.xy)) {
        set("palette", "Tip to select\na color\n\n"
                       "Swipe left or\nright to change\nthe palette\n\n"
                       "Swipe up for\nmultitouchmode\n\n"
                       "Hold for options");
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

//
// public
//

void dialog_create_tooltip() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->name = ro_text_new_font55(TOOL_NAME_LEN);
    ro_text_set_color(&impl->name, DIALOG_TEXT_COLOR);

    impl->tip = ro_text_new_font85(TOOL_TIP_LEN);

    impl->name.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - 18, 1, 2);
    impl->tip.pose = u_pose_new(DIALOG_LEFT + 2, DIALOG_TOP - 36, 1, 1);
    set("tooltip", "Click on a tool\nto get its tip");

    dialog_set_title("tooltip", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
}
