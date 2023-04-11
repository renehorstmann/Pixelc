#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/button.h"
#include "io.h"
#include "canvas.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 136, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 102, 255}};
static const vec4 TITLE_COLOR = {{0, 0.6, 0.3, 1}};

//
// private
//


typedef struct {
    RoText save_txt;
    RoSingle save_btn;

    bool import_available;

    RoText info;

    RoText load_txt;
    RoSingle load_btn;

    RoSingle upload;
    bool upload_available;

} Impl;


static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->save_txt);
    ro_single_kill(&impl->save_btn);
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->upload);
    ro_text_kill(&impl->load_txt);
    ro_single_kill(&impl->load_btn);
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->save_txt, cam_mat);
    ro_single_render(&impl->save_btn, cam_mat);
    ro_text_render(&impl->info, cam_mat);
    if (impl->import_available) {
        ro_text_render(&impl->load_txt, cam_mat);
        ro_single_render(&impl->load_btn, cam_mat);
    }
    if (impl->upload_available) {
        ro_single_render(&impl->upload, cam_mat);
    }
}

static void uploaded(const char *file, bool ascii, const char *user_file_name, void *user_data) {
    dialog_create_project();
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (impl->upload_available && u_button_clicked(&impl->upload.rect, pointer)) {
        s_log("import upload...");
        e_io_ask_for_file_upload("project_load.tar", false, uploaded, NULL);
        // return after hide, hide kills this dialog
        return true;
    }

    if (u_button_clicked(&impl->save_btn.rect, pointer)) {
        s_log("save project .tar");
        io_project_save();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    if (impl->import_available && u_button_clicked(&impl->load_btn.rect, pointer)) {
        s_log("load project .tar");
        io_project_apply_loaded();
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


void dialog_create_project() {
    dialog_hide();
    canvas_reload();
    s_log("create");
    Impl *impl = s_new0(Impl, 1);
    dialog.impl = impl;

    impl->import_available = io_project_load();

    float pos = 16;


    impl->save_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->save_txt, "Save .tar:");
    ro_text_set_color(&impl->save_txt, DIALOG_TEXT_COLOR);
    impl->save_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->save_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save.png"));
    impl->save_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);

    pos += 24;

    impl->info = ro_text_new_font55(64);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

    if (!impl->import_available) {
        ro_text_set_text(&impl->info, "failed to load\n"
                                      "project_load.tar\narchive");
        impl->info.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 4, 1, 2);
        pos += 32;

    } else {

        char text[64];
        snprintf(text, sizeof text, "ready to reload");
        ro_text_set_text(&impl->info, text);
        impl->info.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 4, 1, 2);

        pos += 32;

        impl->load_txt = ro_text_new_font55(32);
        ro_text_set_text(&impl->load_txt, "Reload .tar:");
        ro_text_set_color(&impl->load_txt, DIALOG_TEXT_COLOR);
        impl->load_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

        impl->load_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_import.png"));
        impl->load_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
        pos += 8;
    }

    dialog.impl_height = pos;

#ifndef PLATFORM_CXXDROID
    impl->upload = ro_single_new(r_texture_new_file(2, 1, "res/button_dialog_upload.png"));
    impl->upload_available = true;
    impl->upload.rect.pose = u_pose_new_aa(DIALOG_LEFT + 8, DIALOG_TOP - pos - 18, 64, 16);
#endif


    dialog_set_title("project", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = tooltip_on_action;
    dialog.opt_on_ok_cb = on_action;
}

