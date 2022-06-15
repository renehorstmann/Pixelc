#include "e/e.h"
#include "r/r.h"
#include "u/pose.h"
#include "toolbar.h"
#include "palette.h"
#include "u/button.h"
#include "dialog.h"
#include "textinput.h"
#include "canvas.h"
#include "camera.h"

#define BG_A "#776666"
#define BG_B "#887777"

struct Dialog_Globals dialog;

void dialog_init() {
    dialog.bg_alpha_layer = ro_single_new(r_texture_new_invalid());
    dialog.bg_alpha_layer.rect.color = (vec4) {{0, 0, 0, 0.2}};
    
    dialog.bg = ro_single_new(r_texture_new_invalid());
    dialog.bg_shadow = ro_single_new(r_texture_new_invalid());
    dialog.bg_shadow.owns_tex = false;
    dialog.bg_shadow.rect.color = (vec4) {{0.2, 0.2, 0.2, 0.5}};
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));

    dialog.title = ro_text_new_font55(16);
    dialog.title_shadow = ro_text_new_font55(16);
    ro_text_set_color(&dialog.title_shadow, (vec4) {{0, 0, 0, 0.33}});

    dialog.cancel = ro_single_new(r_texture_new_file(2, 3, "res/textinput_key_special.png"));
    dialog.cancel.rect.sprite.y = 1;
    dialog.ok = ro_single_new(dialog.cancel.tex);
    dialog.ok.owns_tex = false;

    dialog.cancel.rect.pose = u_pose_new_aa(DIALOG_LEFT + 10, 0,
                                            dialog.cancel.tex.sprite_size.x, dialog.cancel.tex.sprite_size.y);
    dialog.ok.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 10 - dialog.ok.tex.sprite_size.x, 0,
                                        dialog.ok.tex.sprite_size.x, dialog.ok.tex.sprite_size.y);

}


void dialog_update(float dtime) {
    if (!dialog_valid())
        return;
    dialog.textinput_active = false;
    dialog.update(dtime);
    
    dialog.bg_alpha_layer.rect.pose = u_pose_new_aa(camera.RO.left, camera.RO.top, camera_width(), camera_height());

    float height = 16 + dialog.impl_height;
    if (dialog.opt_on_cancel_cb || dialog.opt_on_ok_cb)
        height += 20;

    dialog.bg.rect.pose = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP, DIALOG_WIDTH, height);
    dialog.bg_shadow.rect.pose = dialog.bg.rect.pose;
    u_pose_shift_xy(&dialog.bg_shadow.rect.pose, 2, -2);
    u_pose_set_size(&dialog.bg.rect.uv, DIALOG_WIDTH / 2, height / 2);
    dialog.bg_shadow.rect.uv = dialog.bg.rect.uv;

    u_pose_aa_set_bottom(&dialog.cancel.rect.pose, DIALOG_TOP - height + 2);
    u_pose_aa_set_bottom(&dialog.ok.rect.pose, DIALOG_TOP - height + 2);
}

void dialog_render(const mat4 *cam_mat) {
    if (!dialog_valid())
        return;
    ro_single_render(&dialog.bg_alpha_layer, cam_mat);
    ro_single_render(&dialog.bg_shadow, cam_mat);
    ro_single_render(&dialog.bg, cam_mat);
    ro_text_render(&dialog.title_shadow, cam_mat);
    ro_text_render(&dialog.title, cam_mat);
    if (dialog.opt_on_cancel_cb)
        ro_single_render(&dialog.cancel, cam_mat);
    if (dialog.opt_on_ok_cb)
        ro_single_render(&dialog.ok, cam_mat);
    dialog.render(cam_mat);
}

bool dialog_pointer_event(ePointer_s pointer) {
    if (!dialog_valid())
        return false;
    if (pointer.id == 0 && dialog.opt_on_cancel_cb && u_button_clicked(&dialog.cancel.rect, pointer)) {
        dialog.opt_on_cancel_cb(false);
        dialog_hide();
        return true;
    }
    if (pointer.id == 0 && dialog.opt_on_ok_cb && u_button_clicked(&dialog.ok.rect, pointer)) {
        dialog.opt_on_ok_cb(true);
        dialog_hide();
        return true;
    }
    return dialog.pointer_event(pointer);
}


void dialog_hide() {
    if (!dialog_valid())
        return;
    log_info("hide");
    dialog.kill(dialog.impl);
    dialog.impl = NULL;
    dialog.id[0] = '\0';
    dialog.opt_on_ok_cb = NULL;
    dialog.opt_on_cancel_cb = NULL;
    dialog.kill = NULL;
    dialog.update = NULL;
    dialog.render = NULL;
    dialog.pointer_event = NULL;
}

void dialog_set_bg_color(uColor_s a, uColor_s b) {
    uColor_s buf[4];
    buf[0] = buf[3] = a;
    buf[1] = buf[2] = b;
    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    ro_single_set_texture(&dialog.bg, tex);
    ro_single_set_texture(&dialog.bg_shadow, tex);
}

void dialog_set_title(const char *title_id, vec4 color) {
    assume(strlen(title_id) < DIALOG_MAX_TITLE_LEN, "title to long");
    strcpy(dialog.id, title_id);
    vec2 size = ro_text_set_text(&dialog.title, title_id);
    ro_text_set_text(&dialog.title_shadow, title_id);
    ro_text_set_color(&dialog.title, color);
    dialog.title.pose = u_pose_new(DIALOG_LEFT + DIALOG_WIDTH / 2 - sca_ceil(size.x),
                                   DIALOG_TOP - 2, 2, 2);
    dialog.title_shadow.pose = dialog.title.pose;
    u_pose_shift_xy(&dialog.title_shadow.pose, 1, -1);
}
