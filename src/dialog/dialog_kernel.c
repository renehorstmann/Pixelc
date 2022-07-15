#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "brush.h"
#include "canvas.h"
#include "cameractrl.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//

static void on_delete_action(bool ok) {
    s_log("delete: %i", ok);
    if (ok) {
        brush_delete_kernel(brush.RO.kernel_id);
        brush_save_config();
    }
    dialog_create_kernel();
}


typedef struct {
    RoText info;
    RoSingle kernel;

    RoText delete_txt;
    RoSingle delete_btn;
    
    RoText to_canvas_txt;
    RoSingle to_canvas_btn;

    RoText from_canvas_txt;
    RoSingle from_canvas_btn;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->kernel);

    ro_text_kill(&impl->delete_txt);
    ro_single_kill(&impl->delete_btn);
    
    ro_text_kill(&impl->to_canvas_txt);
    ro_single_kill(&impl->to_canvas_btn);
    
    ro_text_kill(&impl->from_canvas_txt);
    ro_single_kill(&impl->from_canvas_btn);

    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    
    impl->kernel.tex = brush.RO.kernel_tex;
    
    int k_w = brush.RO.kernel.cols;
    int k_h = brush.RO.kernel.rows;
    k_w = isca_min(k_w, 8);
    k_h = isca_min(k_h, 8);
    u_pose_set_size(&impl->kernel.rect.pose, k_w*4, k_h*4);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_single_render(&impl->kernel, cam_mat);
    
    if (brush.RO.max_kernels > 1) {
        ro_text_render(&impl->delete_txt, cam_mat);
        ro_single_render(&impl->delete_btn, cam_mat);    }

    ro_text_render(&impl->to_canvas_txt, cam_mat);
    ro_single_render(&impl->to_canvas_btn, cam_mat);

    ro_text_render(&impl->from_canvas_txt, cam_mat);
    ro_single_render(&impl->from_canvas_btn, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (brush.RO.max_kernels>1 
            && u_button_clicked(&impl->delete_btn.rect, pointer)) {
        s_log("delete dialog");
        dialog_create_prompt("Delete", "delete this\nkernel?", on_delete_action, NULL);
        // return after hide, hide kills this dialog
        return true;
    }

    if (u_button_clicked(&impl->to_canvas_btn.rect, pointer)) {
        s_log("copy kernel into canvas");
        // canvas_set_image takes ownership of palette
        uImage kernel = u_image_new_clone(brush.RO.kernel);
        uSprite sprite = {kernel, 1, 1};
        canvas_set_sprite(sprite, true);
        cameractrl_set_home();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    if (u_button_clicked(&impl->from_canvas_btn.rect, pointer)) {
        s_log("new kernel from canvas");
        uSprite sprite = u_sprite_new_clone_merge_row_down_full(canvas.RO.sprite);
        brush_append_kernel(sprite.img);
        u_sprite_kill(&sprite);
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    return true;
}

static void on_action(bool ok) {
    dialog_hide();
}


//
// public
//

void dialog_create_kernel() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos = 24;
    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});

    char info_txt[32];
    snprintf(info_txt, sizeof info_txt, "%ix%i",
            brush.RO.kernel.cols, 
            brush.RO.kernel.rows);
    ro_text_set_text(&impl->info, info_txt);
    s_log("size is: %s", info_txt);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 64, DIALOG_TOP - pos, 1, 2);
    
    impl->kernel = ro_single_new(r_texture_new_invalid());
    impl->kernel.owns_tex = false;
    u_pose_set_xy(&impl->kernel.rect.pose, DIALOG_LEFT + 48, DIALOG_TOP - 4 - pos);
    pos += 18;
    

    impl->delete_txt = ro_text_new_font55(7);
    ro_text_set_text(&impl->delete_txt, "Delete:");
    ro_text_set_color(&impl->delete_txt, (vec4) {{0.7, 0.0, 0.2, 1.0}});
    impl->delete_txt.pose = u_pose_new(DIALOG_LEFT + 50, DIALOG_TOP - pos - 3, 1, 2);

    impl->delete_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_delete.png"));
    impl->delete_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    pos += 16;

    impl->to_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->to_canvas_txt, "Copy into\n"
                                           "       canvas:");
    ro_text_set_color(&impl->to_canvas_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->to_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->to_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_to.png"));
    impl->to_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 28;

    impl->from_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->from_canvas_txt, "New kernel\n"
                                             "  from canvas:");
    ro_text_set_color(&impl->from_canvas_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->from_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->from_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->from_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 32;

    dialog.impl_height = pos;

    dialog_set_title("kernel", (vec4) {{0.2, 0.6, 0.6, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
//    dialog.opt_on_ok_cb = on_action;
}
