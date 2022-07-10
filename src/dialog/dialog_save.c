#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "io.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//


typedef struct {
    RoText info;
    RoSingle btn_merge;
} Impl;

static void kill_fn() {
    // should not be called...
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->btn_merge);
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_single_render(&impl->btn_merge, cam_mat);
}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    if(u_button_toggled(&impl->btn_merge.rect, pointer)) {
        bool merge = u_button_is_pressed(&impl->btn_merge.rect);
        s_log("save merged toggled: %i", merge);
        io.image_save_merged = merge;
    }
    return true;
}

static void on_action(bool ok) {
    // cancel
    dialog_hide();
}

//
// public
//


void dialog_create_save() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});
    ro_text_set_text(&impl->info, "save layers\n"
            "      merged?");
    impl->info.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - 20, 1, 2);
    
    impl->btn_merge = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));
    impl->btn_merge.rect.pose = u_pose_new_aa(
            DIALOG_LEFT + DIALOG_WIDTH - 20, 
            DIALOG_TOP - 24, 
            16, 16);
    impl->btn_merge.rect.sprite.x = io.image_save_merged? 1 : 0;
    
    dialog.impl_height = 40;

    dialog_set_title("save", (vec4) {{0.6, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_ok_cb = on_action;
}

