#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//


typedef struct {
    RoText info;
    RoSingle upload;
    bool upload_available;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->upload);
    rhc_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    if (impl->upload_available)
        ro_single_render(&impl->upload, cam_mat);
}

static void set_info(const char *file_name) {
    Impl *impl = dialog.impl;
    char text[64];
    uImage img = u_image_new_file(1, "import.png");
    if (!u_image_valid(img)) {
        snprintf(text, sizeof text, "failed to load\n  image\n%s", file_name);
    } else {
        snprintf(text, sizeof text, "%s\n   cols: %i\n   rows: %i", file_name, img.cols, img.rows);
    }
    ro_text_set_text(&impl->info, text);
    u_image_kill(&img);
}

static void uploaded(const char *file, bool ascii, const char *user_file_name, void *user_data) {
    set_info(user_file_name);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (impl->upload_available && u_button_clicked(&impl->upload.rect, pointer)) {
        e_io_ask_for_file_upload("import.png", false, uploaded, NULL);
    }

    return true;
}

static void on_action(bool ok) {
    dialog_hide();
}

//
// public
//


void dialog_create_image_upload() {
    dialog_hide();
    log_info("create");
    Impl *impl = rhc_calloc(sizeof *impl);
    dialog.impl = impl;

    impl->info = ro_text_new_font55(64);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});

    set_info("import.png");

    impl->info.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - 22, 1, 2);

    dialog.impl_height = 44;

#ifdef __EMSCRIPTEN__
    impl->upload = ro_single_new(r_texture_new_file(2, 1, "res/button_dialog_upload.png"));
    impl->upload_available = true;
    impl->upload.rect.pose = u_pose_new_aa(DIALOG_LEFT + 8, DIALOG_TOP-62, 64, 16);
#endif

    dialog_set_title("import", (vec4) {{0.6, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = tooltip_on_action;
    dialog.opt_on_ok_cb = on_action;
}

