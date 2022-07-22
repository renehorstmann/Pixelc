#include "r/r.h"
#include "u/button.h"
#include "u/pose.h"
#include "modal.h"
#include "animation.h"
#include "io.h"
#include "dialog.h"

#define BG_A "#667766"
#define BG_B "#778877"

//
// private
//

typedef struct {
    RoText size_txt;
    RoText size_num;
    mat4 size_hitbox;
    
    RoText repeat_txt;
    RoSingle repeat_h;
    RoSingle repeat_v;
    
    RoText save_txt;
    RoSingle save;
    RoSingle save_hd;
    
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->size_txt);
    ro_text_kill(&impl->size_num);
    
    ro_text_kill(&impl->repeat_txt);
    ro_single_kill(&impl->repeat_h);
    ro_single_kill(&impl->repeat_v);
    
    ro_text_kill(&impl->save_txt);
    ro_single_kill(&impl->save);
    ro_single_kill(&impl->save_hd);
    
    textinput_kill(&impl->textinput);
    
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    if(impl->textinput) {
        char *end;
        float size = (float) strtod(impl->textinput->text, &end);
        bool ok = end && end != impl->textinput->text && size>0 && size<=128;
        
        impl->textinput->ok_active = ok;
        
        if (impl->textinput->state == TEXTINPUT_DONE) {
            animation.size = size;
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }
    
    char buf[16];
    snprintf(buf, sizeof buf, "%.1f", animation.size);
    ro_text_set_text(&impl->size_num, buf);
    
    impl->repeat_h.rect.sprite.x = (animation.mode == ANIMATION_MODE_REPEAT_H 
            || animation.mode == ANIMATION_MODE_REPEAT_HV) ? 1: 0;
            
    impl->repeat_v.rect.sprite.x = (animation.mode == ANIMATION_MODE_REPEAT_V 
            || animation.mode == ANIMATION_MODE_REPEAT_HV) ? 1: 0;
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->size_txt, cam_mat);
    ro_text_render(&impl->size_num, cam_mat);
    ro_text_render(&impl->repeat_txt, cam_mat);
    ro_single_render(&impl->repeat_h, cam_mat);
    ro_single_render(&impl->repeat_v, cam_mat);
    ro_text_render(&impl->save_txt, cam_mat);
    ro_single_render(&impl->save, cam_mat);
    ro_single_render(&impl->save_hd, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if(u_pose_aa_contains(impl->size_hitbox, pointer.pos.xy)) {
        s_log("edit animation size");
        impl->textinput = textinput_new("Size", 0);
        modal_set_textinput(impl->textinput);
        snprintf(impl->textinput->text, TEXTINPUT_MAX_CHARS, "%.1f", animation.size);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
    }
    
    if(u_button_toggled(&impl->repeat_h.rect, pointer)) {
        if(u_button_is_pressed(&impl->repeat_h.rect)) {
            if(animation.mode == ANIMATION_MODE_SINGLE) 
                animation.mode = ANIMATION_MODE_REPEAT_H;
            else
                animation.mode = ANIMATION_MODE_REPEAT_HV;
        } else {
            if(animation.mode == ANIMATION_MODE_REPEAT_H) 
                animation.mode = ANIMATION_MODE_SINGLE;
            else
                animation.mode = ANIMATION_MODE_REPEAT_V;
        }
    }
    
    if(u_button_toggled(&impl->repeat_v.rect, pointer)) {
        if(u_button_is_pressed(&impl->repeat_v.rect)) {
            if(animation.mode == ANIMATION_MODE_SINGLE) 
                animation.mode = ANIMATION_MODE_REPEAT_V;
            else
                animation.mode = ANIMATION_MODE_REPEAT_HV;
        } else {
            if(animation.mode == ANIMATION_MODE_REPEAT_V) 
                animation.mode = ANIMATION_MODE_SINGLE;
            else
                animation.mode = ANIMATION_MODE_REPEAT_H;
        }
    }
    
    if(u_button_clicked(&impl->save.rect, pointer)) {
        s_log("save gif");
        io_gif_save();
    }
    
    if(u_button_clicked(&impl->save_hd.rect, pointer)) {
        s_log("save hd gif");
        io_gif_hd_save();
    }
    
    return true;
}

static void on_action(bool ok) {
    dialog_hide();
}

//
// public
//

void dialog_create_animation() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;
    
    int pos = 24;

    impl->size_txt = ro_text_new_font55(5);
    ro_text_set_text(&impl->size_txt, "size:");
    ro_text_set_color(&impl->size_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->size_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->size_num, (vec4) {{0.1, 0.1, 0.9, 1}});
    impl->size_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->size_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->size_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    
    pos += 16;
    
    impl->repeat_txt = ro_text_new_font55(8);
    ro_text_set_text(&impl->repeat_txt, "repeat:");
    
    ro_text_set_color(&impl->repeat_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->repeat_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->repeat_h = ro_single_new(r_texture_new_file(2, 2, "res/button_repeat.png"));
    impl->repeat_h.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->repeat_v = ro_single_new(impl->repeat_h.tex);
    impl->repeat_v.owns_tex = false;
    impl->repeat_v.rect.sprite.y = 1;
    impl->repeat_v.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 24;
    
    impl->save_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->save_txt, "save .gif:");
    
    ro_text_set_color(&impl->save_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->save_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->save = ro_single_new(r_texture_new_file(2, 1, "res/button_save.png"));
    impl->save.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->save_hd = ro_single_new(r_texture_new_file(2, 1, "res/button_save_hd.png"));
    impl->save_hd.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 8;
    
    dialog.impl_height = pos;
    
    dialog_set_title("animation", (vec4) {{0.2, 0.6, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_ok_cb = on_action;
}
