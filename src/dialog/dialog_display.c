#include "r/r.h"
#include "u/pose.h"
#include "u/button.h"
#include "textinput.h"
#include "camera.h"
#include "cameractrl.h"
#include "modal.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//


typedef struct {
    int size;
    RoText size_text;
    RoText size_num;
    mat4 size_hitbox;

    enum camera_rotate_mode mode;
    RoText mode_text;

    RoBatch buttons;

    int textinput_usage;
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->size_text);
    ro_text_kill(&impl->size_num);
    ro_text_kill(&impl->mode_text);
    ro_batch_kill(&impl->buttons);
    textinput_kill(&impl->textinput);
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;

    if (impl->textinput) {
        char *end;
        int size = strtol(impl->textinput->text, &end, 10);
        bool ok = end && end != impl->textinput->text && size >= CAMERA_SIZE_MIN && size <= CAMERA_SIZE_MAX;
        impl->textinput->ok_active = ok;

        if (impl->textinput->state == TEXTINPUT_DONE) {
            switch (impl->textinput_usage) {
                case 0:
                    impl->size = size;
                    break;
                default:
                    s_assume(0, "wtf");
            }
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }

    char buf[16];
    snprintf(buf, sizeof buf, "%i", impl->size);
    ro_text_set_text(&impl->size_num, buf);

    impl->buttons.rects[2].sprite.x = impl->mode == CAMERA_ROTATE_MODE_PORTRAIT;
    impl->buttons.rects[3].sprite.x = impl->mode == CAMERA_ROTATE_MODE_LANDSCAPE;
    impl->buttons.rects[4].sprite.x = impl->mode == CAMERA_ROTATE_MODE_AUTO;
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->size_text, cam_mat);
    ro_text_render(&impl->size_num, cam_mat);
    ro_text_render(&impl->mode_text, cam_mat);
    ro_batch_render(&impl->buttons, cam_mat, true);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (pointer.id != 0)
        return true;

    if (pointer.action == E_POINTER_DOWN) {
        if (u_pose_aa_contains(impl->size_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new("Internal Min. Size", 8);
            modal_set_textinput(impl->textinput);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->size);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 0;
        }
    }

    if (u_button_clicked(&impl->buttons.rects[0], pointer)) {
        impl->size = CAMERA_SIZE_SMALL;
    }
    if (u_button_clicked(&impl->buttons.rects[1], pointer)) {
        impl->size = CAMERA_SIZE_BIG;
    }

    if (u_button_pressed(&impl->buttons.rects[2], pointer)) {
        impl->mode = CAMERA_ROTATE_MODE_PORTRAIT;
    }
    if (u_button_pressed(&impl->buttons.rects[3], pointer)) {
        impl->mode = CAMERA_ROTATE_MODE_LANDSCAPE;
    }
    if (u_button_pressed(&impl->buttons.rects[4], pointer)) {
        impl->mode = CAMERA_ROTATE_MODE_AUTO;
    }


    return true;
}

static void on_action(bool ok) {
    Impl *impl = dialog.impl;
    int size = impl->size;
    enum camera_rotate_mode mode = impl->mode;

    bool save_cam = false;

    dialog_hide();
    if (!ok) {
        s_log("dialog display aborted");
        return;
    }
    if (size >= CAMERA_SIZE_MIN && size <= CAMERA_SIZE_MAX) {
        s_log("dialog display new size %i", size);
        camera.size = size;
        save_cam = true;
    }
    if (mode >= 0 && mode < CAMERA_ROTATE_NUM_MODES) {
        s_log("dialog display new mode %i", mode);
        camera.rotate_mode = mode;
        save_cam = true;
    }

    if (save_cam) {
        camera_save_config();
        cameractrl_set_home();
    }
}

//
// public
//

void dialog_create_display() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->buttons = ro_batch_new(5, r_texture_new_file(2, 5, "res/button_display_settings.png"));

    int pos;

    pos = 20;
    impl->size = camera.size;
    impl->size_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->size_text, "size:");
    ro_text_set_color(&impl->size_text, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->size_num = ro_text_new_font55(4);
    ro_text_set_color(&impl->size_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->size_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->size_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->size_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, 64, 10 + 8);


    impl->buttons.rects[0].pose = u_pose_new_aa(DIALOG_LEFT + 76, DIALOG_TOP - pos + 4, 16, 16);
    impl->buttons.rects[0].sprite.y = 0;
    impl->buttons.rects[1].pose = u_pose_new_aa(DIALOG_LEFT + 96, DIALOG_TOP - pos + 4, 16, 16);
    impl->buttons.rects[1].sprite.y = 1;


    pos = 45;
    impl->mode = camera.rotate_mode;
    impl->mode_text = ro_text_new_font55(12);
    ro_text_set_text(&impl->mode_text, "rotate mode:");
    impl->mode_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    ro_text_set_color(&impl->mode_text, (vec4) {{0.9, 0.9, 0.9, 1}});

    pos = 60;
    for (int i = 0; i < 3; i++) {
        impl->buttons.rects[i + 2].sprite.y = i + 2;
        impl->buttons.rects[i + 2].pose = u_pose_new_aa(DIALOG_LEFT + 56 + i * 20, DIALOG_TOP - pos + 4, 16, 16);
    }

    dialog_set_title("display", (vec4) {{0.8, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.impl_height = pos;
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
