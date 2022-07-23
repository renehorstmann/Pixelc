#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "io.h"
#include "modal.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//


typedef struct {
    RoText hd_size_txt;
    RoText hd_size_num;
    mat4 hd_size_hitbox;
    
    RoText merge_txt;
    RoSingle merge_toggle;
    
    RoText png_txt;
    RoSingle png_btn;
    RoSingle png_hd_btn;
    
    RoText gif_txt;
    RoSingle gif_btn;
    RoSingle gif_hd_btn;
    
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    
    ro_text_kill(&impl->hd_size_txt);
    ro_text_kill(&impl->hd_size_num);
    
    ro_text_kill(&impl->merge_txt);
    ro_single_kill(&impl->merge_toggle);
    
    ro_text_kill(&impl->png_txt);
    ro_single_kill(&impl->png_btn);
    ro_single_kill(&impl->png_hd_btn);
    
    ro_text_kill(&impl->gif_txt);
    ro_single_kill(&impl->gif_btn);
    ro_single_kill(&impl->gif_hd_btn);
    
    textinput_kill(&impl->textinput);
    
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    if(impl->textinput) {
        char *end;
        int size = (int) strtol(impl->textinput->text, &end, 10);
        bool ok = end && end != impl->textinput->text && size>0 && size<=8192;
        
        impl->textinput->ok_active = ok;
        
        if (impl->textinput->state == TEXTINPUT_DONE) {
            io.hd_min_size = size;
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }
    
    char buf[16];
    snprintf(buf, sizeof buf, "%i", io.hd_min_size);
    ro_text_set_text(&impl->hd_size_num, buf);
    
    impl->merge_toggle.rect.sprite.x = io.image_save_merged? 1 : 0;
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    
    ro_text_render(&impl->hd_size_txt, cam_mat);
    ro_text_render(&impl->hd_size_num, cam_mat);
    
    ro_text_render(&impl->merge_txt, cam_mat);
    ro_single_render(&impl->merge_toggle, cam_mat);
    
    ro_text_render(&impl->png_txt, cam_mat);
    ro_single_render(&impl->png_btn, cam_mat);
    ro_single_render(&impl->png_hd_btn, cam_mat);
    
    ro_text_render(&impl->gif_txt, cam_mat);
    ro_single_render(&impl->gif_btn, cam_mat);
    ro_single_render(&impl->gif_hd_btn, cam_mat);
}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    
    if(pointer.id == 0
            && pointer.action == E_POINTER_DOWN
            && u_pose_aa_contains(impl->hd_size_hitbox, pointer.pos.xy)) {
        s_log("edit hd min size");
        impl->textinput = textinput_new("HD min. size", 0);
        modal_set_textinput(impl->textinput);
        snprintf(impl->textinput->text, TEXTINPUT_MAX_CHARS, "%i", io.hd_min_size);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
    }
    
    if(u_button_toggled(&impl->merge_toggle.rect, pointer)) {
        bool merge = u_button_is_pressed(&impl->merge_toggle.rect);
        s_log("save merged toggled: %i", merge);
        io.image_save_merged = merge;
    }
    
    if(u_button_clicked(&impl->png_btn.rect, pointer)) {
        s_log("save png");
        io_image_save();
        dialog_hide();
    }
    if(u_button_clicked(&impl->png_hd_btn.rect, pointer)) {
        s_log("save png hd");
        io_image_hd_save();
        dialog_hide();
    }
    
    if(u_button_clicked(&impl->gif_btn.rect, pointer)) {
        s_log("save gif");
        io_gif_save();
        dialog_hide();
    }
    if(u_button_clicked(&impl->gif_hd_btn.rect, pointer)) {
        s_log("save gif hd");
        io_gif_hd_save();
        dialog_hide();
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


void dialog_create_save() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;
    
    int pos = 24;
    
    impl->hd_size_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->hd_size_txt, "hd min size:");
    ro_text_set_color(&impl->hd_size_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->hd_size_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->hd_size_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->hd_size_txt.pose = u_pose_new(DIALOG_LEFT + 6, DIALOG_TOP - pos, 1, 2);
    impl->hd_size_num.pose = u_pose_new(DIALOG_LEFT + 80, DIALOG_TOP - pos, 1, 2);
    impl->hd_size_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    
    pos += 20;

    impl->merge_txt = ro_text_new_font55(32);
    ro_text_set_color(&impl->merge_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    ro_text_set_text(&impl->merge_txt, "save layers\n"
            "      merged?");
    impl->merge_txt.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - pos, 1, 2);
    
    impl->merge_toggle = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));
    impl->merge_toggle.rect.pose = u_pose_new_aa(
            DIALOG_LEFT + DIALOG_WIDTH - 20, 
            DIALOG_TOP - pos - 4, 
            16, 16);
            
    pos += 40;
    
    impl->png_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->png_txt, "save .png:");
    
    ro_text_set_color(&impl->png_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->png_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->png_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save.png"));
    impl->png_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->png_hd_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save_hd.png"));
    impl->png_hd_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 18;
    
    impl->gif_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->gif_txt, "save .gif:");
    
    ro_text_set_color(&impl->gif_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->gif_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->gif_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save.png"));
    impl->gif_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->gif_hd_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_save_hd.png"));
    impl->gif_hd_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 10;
    
    dialog.impl_height = pos;

    dialog_set_title("save", (vec4) {{0.6, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_ok_cb = on_action;
}

