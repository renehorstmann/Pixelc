#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "canvas.h"
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
    
    RoText to_canvas_txt;
    RoSingle to_canvas_btn;
    bool image_available;

} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->upload);
    ro_text_kill(&impl->to_canvas_txt);
    ro_single_kill(&impl->to_canvas_btn);
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    if (impl->upload_available) {
        ro_single_render(&impl->upload, cam_mat);
    }
    if(impl->image_available) {
        ro_text_render(&impl->to_canvas_txt, cam_mat);
        ro_single_render(&impl->to_canvas_btn, cam_mat);

    }
}

static void set_info(const char *file_name) {
    Impl *impl = dialog.impl;
    char text[64];
    uImage img = u_image_new_file(1, "import.png");
    impl->image_available = u_image_valid(img);
    if (!impl->image_available) {
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
        s_log("import upload...");
        e_io_ask_for_file_upload("import.png", false, uploaded, NULL);
    }
    
    if (impl->image_available && u_button_clicked(&impl->to_canvas_btn.rect, pointer)) {
        s_log("import to canvas");
        uImage img = u_image_new_file(1, "import.png");
        impl->image_available = u_image_valid(img);
        if(impl->image_available) {
            canvas_set_image(img, true);
        }
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
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;
    
    float pos = 22;

    impl->info = ro_text_new_font55(64);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});

    set_info("import.png");

    impl->info.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    pos += 40;
    
    impl->to_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->to_canvas_txt, "Copy into\n"
                                           "       canvas:");
    ro_text_set_color(&impl->to_canvas_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->to_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    
    impl->to_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_to.png"));
    impl->to_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 22;

    dialog.impl_height = pos;

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

