#include "r/r.h"
#include "u/pose.h"
#include "textinput.h"
#include "canvas.h"
#include "cameractrl.h"
#include "modal.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//

typedef struct {
    int cols;
    RoText cols_text;
    RoText cols_num;
    mat4 cols_hitbox;

    int rows;
    RoText rows_text;
    RoText rows_num;
    mat4 rows_hitbox;

    int layers;
    RoText layers_text;
    RoText layers_num;
    mat4 layers_hitbox;

    int p_cols;
    RoText p_cols_text;
    RoText p_cols_num;
    mat4 p_cols_hitbox;

    int p_rows;
    RoText p_rows_text;
    RoText p_rows_num;
    mat4 p_rows_hitbox;

    int textinput_usage;
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->cols_text);
    ro_text_kill(&impl->cols_num);
    ro_text_kill(&impl->rows_text);
    ro_text_kill(&impl->rows_num);
    ro_text_kill(&impl->layers_text);
    ro_text_kill(&impl->layers_num);
    ro_text_kill(&impl->p_cols_text);
    ro_text_kill(&impl->p_cols_num);
    ro_text_kill(&impl->p_rows_text);
    ro_text_kill(&impl->p_rows_num);
    textinput_kill(&impl->textinput);
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;

    if (impl->textinput) {

        char *end;
        int size = strtol(impl->textinput->text, &end, 10);
        bool ok = end && end != impl->textinput->text && size > 0 && size <= CANVAS_MAX_SIZE;
        if (ok && impl->textinput_usage == 2
            && size > CANVAS_MAX_LAYERS)
            ok = false;
        impl->textinput->ok_active = ok;

        if (impl->textinput->state == TEXTINPUT_DONE) {
            switch (impl->textinput_usage) {
                case 0:
                    impl->cols = size;
                    break;
                case 1:
                    impl->rows = size;
                    break;
                case 2:
                    impl->layers = size;
                    break;
                case 3:
                    impl->p_cols = size;
                    break;
                case 4:
                    impl->p_rows = size;
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
    snprintf(buf, sizeof buf, "%i", impl->cols);
    ro_text_set_text(&impl->cols_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->rows);
    ro_text_set_text(&impl->rows_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->layers);
    ro_text_set_text(&impl->layers_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->p_cols);
    ro_text_set_text(&impl->p_cols_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->p_rows);
    ro_text_set_text(&impl->p_rows_num, buf);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->cols_text, cam_mat);
    ro_text_render(&impl->cols_num, cam_mat);
    ro_text_render(&impl->rows_text, cam_mat);
    ro_text_render(&impl->rows_num, cam_mat);
    ro_text_render(&impl->layers_text, cam_mat);
    ro_text_render(&impl->layers_num, cam_mat);
    ro_text_render(&impl->p_cols_text, cam_mat);
    ro_text_render(&impl->p_cols_num, cam_mat);
    ro_text_render(&impl->p_rows_text, cam_mat);
    ro_text_render(&impl->p_rows_num, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (pointer.id == 0 && pointer.action == E_POINTER_DOWN) {
        if (u_pose_aa_contains(impl->cols_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new("Set canvas cols", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->cols);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 0;
        } else if (u_pose_aa_contains(impl->rows_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new("Set canvas rows", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->rows);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 1;
        } else if (u_pose_aa_contains(impl->layers_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new("Set layers", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->layers);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 2;
        } else if (u_pose_aa_contains(impl->p_cols_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new("Set pattern cols", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->p_cols);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 3;
        } else if (u_pose_aa_contains(impl->p_rows_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new("Set pattern rows", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->p_rows);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 4;
        }

        if(impl->textinput)
            modal_set_textinput(impl->textinput);
    }

    return true;
}

static void on_action(bool ok) {
    Impl *impl = dialog.impl;
    uImage img = canvas.RO.image;
    int cols = impl->cols;
    int rows = impl->rows;
    int layers = impl->layers;
    int p_cols = impl->p_cols;
    int p_rows = impl->p_rows;

    dialog_hide();
    if (!ok) {
        s_log("dialog canvas_size aborted");
        return;
    }
    if (cols != img.cols || rows != img.rows || layers != img.layers) {
        s_log("dialog canvas_size: new size %i %i", cols, rows);

        uImage new_img = u_image_new_zeros(cols, rows, layers);
        if (layers != img.layers) {
            // copy top left as if there were no layers
            new_img.rows *= layers;
            new_img.layers = 1;
            img.rows *= img.layers;
            img.layers = 1;
        }

        u_image_copy_top_left(new_img, img);

        // reset the size to use layers and udpate the canvas
        new_img.rows = rows;
        new_img.layers = layers;
        canvas_set_image(new_img, true);
        cameractrl_set_home();
    }
    if (p_cols != canvas.RO.pattern_cols
        || p_rows != canvas.RO.pattern_rows) {
        s_log("dialog canvas_size: new pattern size %i %i", p_cols, p_rows);
        canvas_set_pattern_size(p_cols, p_rows);
    }
}

//
// public
//

void dialog_create_canvas_size() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos;

    pos = 20;
    impl->cols = canvas.RO.image.cols;
    impl->cols_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->cols_text, "cols:");
    ro_text_set_color(&impl->cols_text, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->cols_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->cols_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->cols_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->cols_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->cols_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);

    pos = 35;
    impl->rows = canvas.RO.image.rows;
    impl->rows_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->rows_text, "rows:");
    ro_text_set_color(&impl->rows_text, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->rows_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->rows_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->rows_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->rows_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->rows_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);

    pos = 50;
    impl->layers = canvas.RO.image.layers;
    impl->layers_text = ro_text_new_font55(7);
    ro_text_set_text(&impl->layers_text, "layers:");
    ro_text_set_color(&impl->layers_text, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->layers_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->layers_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->layers_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->layers_num.pose = u_pose_new(DIALOG_LEFT + 52, DIALOG_TOP - pos, 1, 2);
    impl->layers_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);


    pos = 70;
    impl->p_cols = canvas.RO.pattern_cols;
    impl->p_cols_text = ro_text_new_font55(13);
    ro_text_set_text(&impl->p_cols_text, "pattern cols:");
    ro_text_set_color(&impl->p_cols_text, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->p_cols_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->p_cols_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->p_cols_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->p_cols_num.pose = u_pose_new(DIALOG_LEFT + 88, DIALOG_TOP - pos, 1, 2);
    impl->p_cols_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);

    pos = 85;
    impl->p_rows = canvas.RO.pattern_rows;
    impl->p_rows_text = ro_text_new_font55(13);
    ro_text_set_text(&impl->p_rows_text, "pattern rows:");
    ro_text_set_color(&impl->p_rows_text, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->p_rows_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->p_rows_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->p_rows_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->p_rows_num.pose = u_pose_new(DIALOG_LEFT + 88, DIALOG_TOP - pos, 1, 2);
    impl->p_rows_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);


    dialog_set_title("set size", (vec4) {{0.8, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.impl_height = pos;
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
