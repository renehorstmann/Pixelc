#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "canvas.h"
#include "cameractrl.h"
#include "selectionctrl.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 136, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 102, 255}};
static const vec4 TITLE_COLOR = {{0, 0.6, 0.3, 1}};

//
// private
//


typedef struct {
    RoText info;
    RoSingle import;

    bool import_available;

    RoText to_canvas_txt;
    RoSingle to_canvas_btn;

    RoText as_selection_txt;
    RoSingle as_selection_btn;

    RoSingle upload;
    bool upload_available;

} Impl;


static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->import);
    ro_single_kill(&impl->upload);
    ro_text_kill(&impl->to_canvas_txt);
    ro_single_kill(&impl->to_canvas_btn);
    ro_text_kill(&impl->as_selection_txt);
    ro_single_kill(&impl->as_selection_btn);
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    if (impl->import_available) {
        ro_single_render(&impl->import, cam_mat);

        ro_text_render(&impl->to_canvas_txt, cam_mat);
        ro_single_render(&impl->to_canvas_btn, cam_mat);

        ro_text_render(&impl->as_selection_txt, cam_mat);
        ro_single_render(&impl->as_selection_btn, cam_mat);
    }
    if (impl->upload_available) {
        ro_single_render(&impl->upload, cam_mat);
    }
}

static void uploaded(const char *file, bool ascii, const char *user_file_name, void *user_data) {
    dialog_create_import();
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (impl->upload_available && u_button_clicked(&impl->upload.rect, pointer)) {
        s_log("import upload...");
        e_io_ask_for_file_upload("import.png", false, uploaded, NULL);
    }

    if (impl->import_available && u_button_clicked(&impl->to_canvas_btn.rect, pointer)) {
        s_log("import to canvas");
        uSprite sprite = u_sprite_new_file(1, 1, "import.png");
        if (!u_sprite_valid(sprite)) {
            dialog_create_import();
            return true;
        }
        canvas_set_sprite(sprite, true);
        cameractrl_set_home();
        dialog_hide();
        return true;
    }

    if (impl->import_available && u_button_clicked(&impl->as_selection_btn.rect, pointer)) {
        s_log("import to canvas");
        uImage img = u_image_new_file(1, "import.png");
        if (!u_image_valid(img)) {
            dialog_create_import();
            return true;
        }
        s_log("tool import");
        selectionctrl_paste_image(img);
        u_image_kill(&img);
        dialog_hide();
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


void dialog_create_import() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_new0(Impl, 1);
    dialog.impl = impl;

    uImage img = u_image_new_file(1, "import.png");
    impl->import_available = u_image_valid(img)
                             && img.cols <= CANVAS_MAX_SIZE
                             && img.rows <= CANVAS_MAX_SIZE;

    float pos = 16;

    impl->info = ro_text_new_font55(64);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

    if (!impl->import_available) {
        ro_text_set_text(&impl->info, "failed to load\n"
                                      "import.png image");
        impl->info.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 4, 1, 2);
        pos += 26;

    } else {

        char text[64];
        snprintf(text, sizeof text, "cols: %i\n"
                                    "rows: %i", img.cols, img.rows);
        ro_text_set_text(&impl->info, text);
        impl->info.pose = u_pose_new(DIALOG_LEFT + 50, DIALOG_TOP - pos - 4, 1, 2);

        impl->import = ro_single_new(r_texture_new(img.cols, img.rows,
                                                   1, 1, img.data));

        float width = 32;
        float height = 32;
        if (img.cols > img.rows) {
            height = height * img.rows / img.cols;
        } else if (img.cols < img.rows) {
            width = width * img.cols / img.rows;
        }
        impl->import.rect.pose = u_pose_new(DIALOG_LEFT + 8 + 16, DIALOG_TOP - pos -16, width, height);

        pos += 34;


        impl->to_canvas_txt = ro_text_new_font55(32);
        ro_text_set_text(&impl->to_canvas_txt, "Copy into\n"
                                               "      canvas:");
        ro_text_set_color(&impl->to_canvas_txt, DIALOG_TEXT_COLOR);
        impl->to_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);

        impl->to_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_to.png"));
        impl->to_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 4,
                                                      16, 16);
        pos += 30;


        impl->as_selection_txt = ro_text_new_font55(32);
        ro_text_set_text(&impl->as_selection_txt, "As selection:");
        ro_text_set_color(&impl->as_selection_txt, DIALOG_TEXT_COLOR);
        impl->as_selection_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);

        impl->as_selection_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_selection.png"));
        impl->as_selection_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20,
                                                         DIALOG_TOP - pos + 2,
                                                         16, 16);
        pos += 8;
    }

    u_image_kill(&img);

    dialog.impl_height = pos;

#ifndef PLATFORM_CXXDROID
    impl->upload = ro_single_new(r_texture_new_file(2, 1, "res/button_dialog_upload.png"));
    impl->upload_available = true;
    impl->upload.rect.pose = u_pose_new_aa(DIALOG_LEFT + 8, DIALOG_TOP - pos - 18, 64, 16);
#endif


    dialog_set_title("import", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = tooltip_on_action;
    dialog.opt_on_ok_cb = on_action;
}

