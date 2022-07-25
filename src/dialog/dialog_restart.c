#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "palette.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 102, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 102, 102, 255}};
static const vec4 TITLE_COLOR = {{0.7, 0.7, 0.7, 1}};

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


void dialog_create_restart() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);
    ro_text_set_text(&impl->info, "please restart\nthe app");
    impl->info.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - 20, 1, 2);
    
    dialog.impl_height = 42;

    dialog_set_title("restart", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
}

