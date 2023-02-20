#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "palette.h"
#include "modal.h"
#include "canvas.h"
#include "cameractrl.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 124, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 136, 102, 255}};
static const vec4 TITLE_COLOR = {{0.7, 0.7, 0.7, 1}};

//
// private
//

// local data, because the dialog prompt overwrite would kill impls name
static struct {
    char from_name[2 * PALETTE_NAME_MAX]; 
} L;

static void on_delete_action(bool ok) {
    s_log("delete: %i", ok);
    if (ok) {
        palette_delete_palette(palette.RO.palette_id);
        palette_save_config();
    }
    dialog_create_palette();
}

static void on_new_palette_action(bool ok) {
    s_log("new_palette: %i", ok);
    if (ok) {
        palette_append_palette(canvas.RO.image, L.from_name);
        dialog_hide();
    } else {
        dialog_create_palette();
    }
}


typedef struct {
    RoText info;

    RoText delete_txt;
    RoSingle delete_btn;

    RoText to_canvas_txt;
    RoSingle to_canvas_btn;

    RoText from_canvas_txt;
    RoText from_canvas_name;
    RoSingle from_canvas_btn;

    mat4 from_canvas_name_hitbox;
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);

    ro_text_kill(&impl->delete_txt);
    ro_single_kill(&impl->delete_btn);

    ro_text_kill(&impl->to_canvas_txt);
    ro_single_kill(&impl->to_canvas_btn);

    ro_text_kill(&impl->from_canvas_txt);
    ro_text_kill(&impl->from_canvas_name);
    ro_single_kill(&impl->from_canvas_btn);

    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    char name[2 * PALETTE_NAME_MAX] = {0};
    {
        int size = strlen(L.from_name);
        strncpy(name, L.from_name, isca_min(size, 18));
        if (size > 18) {
            strcat(name, "\n  ");
            strcat(name, L.from_name + 18);
        }
    }
    ro_text_set_text(&impl->from_canvas_name, name);
    if (impl->textinput) {
        // at least a name with 1 char
        s_str_toupper(s_strc(impl->textinput->text));
        impl->textinput->ok_active = strlen(impl->textinput->text) >= 1;
        if (impl->textinput->state == TEXTINPUT_DONE) {
            snprintf(L.from_name, sizeof L.from_name, "%s", impl->textinput->text);
            s_log("new palette name: %s", L.from_name);
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);

    if (palette.RO.max_palettes > 1) {
        ro_text_render(&impl->delete_txt, cam_mat);
        ro_single_render(&impl->delete_btn, cam_mat);
    }
    ro_text_render(&impl->to_canvas_txt, cam_mat);
    ro_single_render(&impl->to_canvas_btn, cam_mat);
    ro_text_render(&impl->from_canvas_txt, cam_mat);
    ro_text_render(&impl->from_canvas_name, cam_mat);
    ro_single_render(&impl->from_canvas_btn, cam_mat);

}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (palette.RO.max_palettes > 1
        && u_button_clicked(&impl->delete_btn.rect, pointer)) {
        s_log("delete dialog");
        dialog_create_prompt("Delete", "delete this\npalette?", on_delete_action, NULL);
        // return after hide, hide kills this dialog
        return true;
    }

    if (u_button_clicked(&impl->to_canvas_btn.rect, pointer)) {
        s_log("copy palette into canvas");
        uImage palette = palette_as_image();
        // canvas_set_image takes ownership of palette
        uSprite sprite = {palette, 1, 1};
        canvas_set_sprite(sprite, true);
        cameractrl_set_home();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    if (u_button_clicked(&impl->from_canvas_btn.rect, pointer)) {
        s_log("new palette from canvas");
        if (palette_name_exists(L.from_name)) {
            dialog_create_prompt("Overwrite",
                                 "Do you really\n"
                                 "want to overwrite\n"
                                 "the palette?",
                                 on_new_palette_action, NULL);
        } else {
            on_new_palette_action(true);
        }
        // return after hide, hide kills this dialog
        return true;
    }

    if (pointer.id == 0
            && pointer.action == E_POINTER_DOWN
            && u_pose_aa_contains(impl->from_canvas_name_hitbox, pointer.pos.xy)) {
        s_log("palette dialog: change from canvas name");
        impl->textinput = textinput_new("set palette name", 0);
        modal_set_textinput(impl->textinput);
        snprintf(impl->textinput->text, TEXTINPUT_MAX_CHARS, "%s", L.from_name);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_UPPER;
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


void dialog_create_palette() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos = 18;
    impl->info = ro_text_new_font55(2 * PALETTE_NAME_MAX);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

//    snprintf(palette.RO.palette_name, PALETTE_NAME_MAX, "1234567890123456789012345678901234567890");

    char name[2 * PALETTE_NAME_MAX] = {0};
    {
        int size = strlen(palette.RO.palette_name);
        strncpy(name, palette.RO.palette_name, isca_min(size, 18));
        if (size > 18) {
            strcat(name, "\n  ");
            strcat(name, palette.RO.palette_name + 18);
        }
    }
    ro_text_set_text(&impl->info, name);
    s_log("name is: %s", palette.RO.palette_name);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - pos, 1, 2);
    pos += 22;

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
    ro_text_set_text(&impl->from_canvas_txt, "Set palette\n"
                                             "  from canvas:");
    ro_text_set_color(&impl->from_canvas_txt, DIALOG_TEXT_COLOR);
    impl->from_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->from_canvas_name = ro_text_new_font55(2 * PALETTE_NAME_MAX);
    snprintf(L.from_name, sizeof L.from_name, "%s", palette.RO.palette_name);
    ro_text_set_color(&impl->from_canvas_name, DIALOG_TEXT_EDIT_COLOR);
    impl->from_canvas_name.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - pos - 27, 1, 2);
    impl->from_canvas_name_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos - 27, DIALOG_WIDTH, 10);

    impl->from_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->from_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 28;

    dialog.impl_height = pos;

    dialog_set_title("palette", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
//    dialog.opt_on_ok_cb = on_action;
}

