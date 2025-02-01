#include "r/r.h"
#include "u/pose.h"
#include "u/button.h"
#include "textinput.h"
#include "canvas.h"
#include "tile.h"
#include "cameractrl.h"
#include "modal.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 136, 136, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 143, 255}};
static const vec4 TITLE_COLOR = {{0.6, 0.8, 0.6, 1}};

//
// private
//

typedef struct {
    RoText tile_txt;
    RoSingle tile;
    
    RoText show_txt;
    RoSingle show;
    
    int pattern_cols;
    RoText pattern_cols_text;
    RoText pattern_cols_num;
    mat4 pattern_cols_hitbox;

    int pattern_rows;
    RoText pattern_rows_text;
    RoText pattern_rows_num;
    mat4 pattern_rows_hitbox;

    int textinput_usage;
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->tile_txt);
    ro_single_kill(&impl->tile);
    ro_text_kill(&impl->show_txt);
    ro_single_kill(&impl->show);
    ro_text_kill(&impl->pattern_cols_text);
    ro_text_kill(&impl->pattern_cols_num);
    ro_text_kill(&impl->pattern_rows_text);
    ro_text_kill(&impl->pattern_rows_num);
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
                    impl->pattern_cols = size;
                    break;
                case 1:
                    impl->pattern_rows = size;
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
    snprintf(buf, sizeof buf, "%i", impl->pattern_cols);
    ro_text_set_text(&impl->pattern_cols_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->pattern_rows);
    ro_text_set_text(&impl->pattern_rows_num, buf);
    
    u_button_set_pressed(&impl->tile.rect, tile.active);
    
    u_button_set_pressed(&impl->show.rect, canvas.show_bg);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->tile_txt, cam_mat);
    ro_single_render(&impl->tile, cam_mat);
    ro_text_render(&impl->show_txt, cam_mat);
    ro_single_render(&impl->show, cam_mat);
    ro_text_render(&impl->pattern_cols_text, cam_mat);
    ro_text_render(&impl->pattern_cols_num, cam_mat);
    ro_text_render(&impl->pattern_rows_text, cam_mat);
    ro_text_render(&impl->pattern_rows_num, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    
    if(u_button_toggled(&impl->tile.rect, pointer)) {
        // only passed if button state toggled
        bool pressed = u_button_is_pressed(&impl->tile.rect);
        s_log("tile button");
        tile.active = pressed;
        tile_save_config();
        cameractrl_set_home();
    }
    
    if(u_button_toggled(&impl->show.rect, pointer)) {
        s_log("canvas show_bg");
        canvas.show_bg = u_button_is_pressed(&impl->show.rect);
    }
    

    if (pointer.id != 0 || pointer.action != E_POINTER_DOWN)
        return true;
        
    if (u_pose_aa_contains(impl->pattern_cols_hitbox, pointer.pos.xy)) {
        impl->textinput = textinput_new("Set pattern cols", 8);
        snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->pattern_cols);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
        impl->textinput_usage = 0;
    } else if (u_pose_aa_contains(impl->pattern_rows_hitbox, pointer.pos.xy)) {
        impl->textinput = textinput_new("Set pattern rows", 8);
        snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->pattern_rows);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
        impl->textinput_usage = 1;
    }

    if(impl->textinput)
        modal_set_textinput(impl->textinput);

    return true;
}

static void on_action(bool ok) {
    Impl *impl = dialog.impl;
    int pattern_cols = impl->pattern_cols;
    int pattern_rows = impl->pattern_rows;

    dialog_hide();
    if (!ok) {
        s_log("dialog grid aborted");
        return;
    }
    
    s_log("dialog grid: new pattern size %i %i", pattern_cols, pattern_rows);

    canvas_set_pattern_size(pattern_cols, pattern_rows);
    canvas_save_config();
}

//
// public
//

void dialog_create_grid() {
    dialog_hide();
    canvas_reload();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos = 20;
    
    impl->tile_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->tile_txt, "tilemode:");
    ro_text_set_color(&impl->tile_txt, DIALOG_TEXT_COLOR);
    impl->tile_txt.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - pos - 2, 1, 2);

    impl->tile = ro_single_new(r_texture_new_file(2, 1, "res/button_tile.png"));
    impl->tile.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 30, DIALOG_TOP - pos + 2, 16, 16);

    pos += 15;
    
    impl->show_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->show_txt, "show\n"
            "  background:");
    ro_text_set_color(&impl->show_txt, DIALOG_TEXT_COLOR);
    impl->show_txt.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - pos - 2, 1, 2);

    impl->show = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));
    impl->show.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 30, DIALOG_TOP - pos - 10, 16, 16);

    pos += 40;

    impl->pattern_cols = canvas.RO.pattern_size.x;
    impl->pattern_cols_text = ro_text_new_font55(16);
    ro_text_set_text(&impl->pattern_cols_text, "Pattern cols:");
    ro_text_set_color(&impl->pattern_cols_text, DIALOG_TEXT_COLOR);
    impl->pattern_cols_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->pattern_cols_num, DIALOG_TEXT_EDIT_COLOR);
    impl->pattern_cols_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->pattern_cols_num.pose = u_pose_new(DIALOG_LEFT + 90, DIALOG_TOP - pos, 1, 2);
    impl->pattern_cols_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    pos += 15;

    impl->pattern_rows = canvas.RO.pattern_size.y;
    impl->pattern_rows_text = ro_text_new_font55(16);
    ro_text_set_text(&impl->pattern_rows_text, "Pattern rows:");
    ro_text_set_color(&impl->pattern_rows_text, DIALOG_TEXT_COLOR);
    impl->pattern_rows_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->pattern_rows_num, DIALOG_TEXT_EDIT_COLOR);
    impl->pattern_rows_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->pattern_rows_num.pose = u_pose_new(DIALOG_LEFT + 90, DIALOG_TOP - pos, 1, 2);
    impl->pattern_rows_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    pos += 5;


    dialog_set_title("grid", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.impl_height = pos;
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
