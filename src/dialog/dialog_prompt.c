#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "palette.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//


typedef struct {
    RoText info;
} Impl;

static void kill_fn() {
    // should not be called...
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
}


static bool pointer_event(ePointer_s pointer) {
    // noop 
    return true;
}

//
// public
//


void dialog_create_prompt(const char *title, const char *msg, dialog_on_action_cb on_action) {
    dialog_hide();
    s_log("prompt: %s", title);
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->info = ro_text_new_font55(128);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});
    vec2 size = ro_text_set_text(&impl->info, msg);
    impl->info.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - 20, 1, 2);
    
    dialog.impl_height = 22+size.y;

    dialog_set_title(title, (vec4) {{0.6, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}

