#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "io.h"
#include "modal.h"
#include "dialog.h"


static const uColor_s BG_A_COLOR = {{136, 136, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 102, 255}};
static const vec4 TITLE_COLOR = {{0, 0.6, 0.3, 1}};

//
// private
//


typedef struct {
    RoText hd_multiplyer_txt;
    RoText hd_multiplyer_num;
    mat4 hd_multiplyer_hitbox;
    
    RoText tilemap_txt;
    RoSingle tilemap_btn;
    
    RoText preview_txt;
    RoSingle preview_btn;
    RoSingle preview_hd_btn;
    
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    
    ro_text_kill(&impl->hd_multiplyer_txt);
    ro_text_kill(&impl->hd_multiplyer_num);

    ro_text_kill(&impl->tilemap_txt);
    ro_single_kill(&impl->tilemap_btn);
    
    ro_text_kill(&impl->preview_txt);
    ro_single_kill(&impl->preview_btn);
    ro_single_kill(&impl->preview_hd_btn);
    
    textinput_kill(&impl->textinput);
    
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    if(impl->textinput) {
        char *end;
        int size = (int) strtol(impl->textinput->text, &end, 10);
        bool ok = end && end != impl->textinput->text && size>0 && size<=128;
        
        impl->textinput->ok_active = ok;
        
        if (impl->textinput->state == TEXTINPUT_DONE) {
            io.hd_multiplyer = size;
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }
    
    char buf[16];
    snprintf(buf, sizeof buf, "%i", io.hd_multiplyer);
    ro_text_set_text(&impl->hd_multiplyer_num, buf);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    
    ro_text_render(&impl->hd_multiplyer_txt, cam_mat);
    ro_text_render(&impl->hd_multiplyer_num, cam_mat);
    
    ro_text_render(&impl->tilemap_txt, cam_mat);
    ro_single_render(&impl->tilemap_btn, cam_mat);
    
    ro_text_render(&impl->preview_txt, cam_mat);
    ro_single_render(&impl->preview_btn, cam_mat);
    ro_single_render(&impl->preview_hd_btn, cam_mat);
}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    
    if(pointer.id == 0
            && pointer.action == E_POINTER_DOWN
            && u_pose_aa_contains(impl->hd_multiplyer_hitbox, pointer.pos.xy)) {
        s_log("edit hd min size");
        impl->textinput = textinput_new("HD multiplyer", 0);
        modal_set_textinput(impl->textinput);
        snprintf(impl->textinput->text, TEXTINPUT_MAX_CHARS, "%i", io.hd_multiplyer);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
    }
    
    if(u_button_clicked(&impl->tilemap_btn.rect, pointer)) {
        s_log("save png");
        bool was_merged = io.image_save_merged;
        io.image_save_merged = false;
        io_image_save();
        io.image_save_merged = was_merged;
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }
    
    if(u_button_clicked(&impl->preview_btn.rect, pointer)) {
        s_log("save gif");
        io_tilemap_save();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }
    if(u_button_clicked(&impl->preview_hd_btn.rect, pointer)) {
        s_log("save gif hd");
        io_tilemap_hd_save();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }
    return true;
}

static void on_action(bool ok) {
    // cancel
    dialog_hide();
}

//
// public
//


void dialog_create_save_tile() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;
    
    int pos = 24;
    
    impl->hd_multiplyer_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->hd_multiplyer_txt, "hd multiplyer:");
    ro_text_set_color(&impl->hd_multiplyer_txt, DIALOG_TEXT_COLOR);
    impl->hd_multiplyer_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->hd_multiplyer_num, DIALOG_TEXT_EDIT_COLOR);
    impl->hd_multiplyer_txt.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - pos, 1, 2);
    impl->hd_multiplyer_num.pose = u_pose_new(DIALOG_LEFT + 95, DIALOG_TOP - pos, 1, 2);
    impl->hd_multiplyer_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    
    pos += 20;
    
    impl->tilemap_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->tilemap_txt, "tilemap\n"
                                         " save .png:");
    
    ro_text_set_color(&impl->tilemap_txt, DIALOG_TEXT_COLOR);
    impl->tilemap_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->tilemap_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save.png"));
    impl->tilemap_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos - 10, 16, 16);

    pos += 32;
    
    impl->preview_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->preview_txt, "preview\n"
                                         " save .png:");
    
    ro_text_set_color(&impl->preview_txt, DIALOG_TEXT_COLOR);
    impl->preview_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->preview_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save.png"));
    impl->preview_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos - 10, 16, 16);
    
    impl->preview_hd_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save_hd.png"));
    impl->preview_hd_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    
    pos += 18;
    
    dialog.impl_height = pos;

    dialog_set_title("save", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_ok_cb = on_action;
}

