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


static const uColor_s BG_A_COLOR = {{136, 102, 136, 255}};
static const uColor_s BG_B_COLOR = {{143, 102, 143, 255}};
static const vec4 TITLE_COLOR = {{0.7, 0.7, 0.7, 1}};

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
    k_w = s_min(k_w, 8);
    k_h = s_min(k_h, 8);
    u_pose_set_size(&impl->kernel.rect.pose, k_w * 4, k_h * 4);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_single_render(&impl->kernel, cam_mat);

    if (brush.RO.max_kernels > 1) {
        ro_text_render(&impl->delete_txt, cam_mat);
        ro_single_render(&impl->delete_btn, cam_mat);
    }

    ro_text_render(&impl->to_canvas_txt, cam_mat);
    ro_single_render(&impl->to_canvas_btn, cam_mat);

    ro_text_render(&impl->from_canvas_txt, cam_mat);
    ro_single_render(&impl->from_canvas_btn, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (brush.RO.max_kernels > 1
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
    canvas_reload();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    float pos = 16;
    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

    char text[64];
    uImage img = brush.RO.kernel;
    snprintf(text, sizeof text, "cols: %i\n"
                                "rows: %i", img.cols, img.rows);
    ro_text_set_text(&impl->info, text);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 50, DIALOG_TOP - pos - 4, 1, 2);

    impl->kernel = ro_single_new(brush.RO.kernel_tex);
    impl->kernel.owns_tex = false;

    int width = brush.RO.kernel.cols;
    int height = brush.RO.kernel.rows;
    width = s_min(width, 8) * 4;
    height = s_min(height, 8) * 4;
    impl->kernel.rect.pose = u_pose_new(DIALOG_LEFT + 8 + 16, DIALOG_TOP - pos - 16, width, height);

    pos += 34;

    impl->delete_txt = ro_text_new_font55(7);
    ro_text_set_text(&impl->delete_txt, "Delete:");
    ro_text_set_color(&impl->delete_txt, DIALOG_TEXT_DELETE_COLOR);
    impl->delete_txt.pose = u_pose_new(DIALOG_LEFT + 50, DIALOG_TOP - pos - 3, 1, 2);

    impl->delete_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_delete.png"));
    impl->delete_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    pos += 16;

    impl->to_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->to_canvas_txt, "Copy into\n"
                                           "       canvas:");
    ro_text_set_color(&impl->to_canvas_txt, DIALOG_TEXT_COLOR);
    impl->to_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->to_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_to.png"));
    impl->to_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 28;

    impl->from_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->from_canvas_txt, "New kernel\n"
                                             "  from canvas:");
    ro_text_set_color(&impl->from_canvas_txt, DIALOG_TEXT_COLOR);
    impl->from_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->from_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->from_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 12;

    dialog.impl_height = pos;

    dialog_set_title("kernel", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
