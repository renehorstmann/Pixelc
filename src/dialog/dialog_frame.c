#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "brush.h"
#include "canvas.h"
#include "cameractrl.h"
#include "modal.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 136, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 102, 255}};
static const vec4 TITLE_COLOR = {{0.2, 0.2, 0.6, 1}};

//
// private
//

static void on_delete_action(bool ok) {
    s_log("delete: %i", ok);
    if (ok) {
        uSprite old = canvas_get_sprite();
        uSprite sprite = u_sprite_new_clone_remove_col(old, canvas.RO.current_frame);
        u_sprite_kill(&old);
        canvas_set_sprite(sprite, true);
        dialog_create_frame();
    } else 
        dialog_hide();
}


typedef struct {
    RoText info;
    RoSingle frame;

    RoText delete_txt;
    RoSingle delete_btn;
    
    RoText move_txt;
    RoSingle move_prev_btn;
    RoSingle move_next_btn;

    RoText merge_txt;
    RoSingle merge_btn;
    
    RoText frametime_txt;
    RoText frametime_num;
    mat4 frametime_hitbox;
    
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->frame);

    ro_text_kill(&impl->delete_txt);
    ro_single_kill(&impl->delete_btn);
    
    ro_text_kill(&impl->move_txt);
    ro_single_kill(&impl->move_prev_btn);
    ro_single_kill(&impl->move_next_btn);
    
    ro_text_kill(&impl->merge_txt);
    ro_single_kill(&impl->merge_btn);
    
    ro_text_kill(&impl->frametime_txt);
    ro_text_kill(&impl->frametime_num);

    textinput_kill(&impl->textinput);
    
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    if(impl->textinput) {
        char *end;
        float time = (float) strtod(impl->textinput->text, &end);
        bool ok = end && end != impl->textinput->text && time>0 && time<1000;
        
        impl->textinput->ok_active = ok;
        
        if (impl->textinput->state == TEXTINPUT_DONE) {
            canvas.frame_times[canvas.RO.current_frame] = time;
            canvas_save_config();
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }
    
    char buf[16];
    snprintf(buf, sizeof buf, "%.2f", canvas.frame_times[canvas.RO.current_frame]);
    ro_text_set_text(&impl->frametime_num, buf);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_single_render(&impl->frame, cam_mat);
    
    if (canvas.RO.sprite.cols > 1) {
        ro_text_render(&impl->delete_txt, cam_mat);
        ro_single_render(&impl->delete_btn, cam_mat);
        
    }

    ro_text_render(&impl->move_txt, cam_mat);
    
    if(canvas.RO.current_frame<canvas.RO.sprite.cols-1) {
        ro_single_render(&impl->move_next_btn, cam_mat);
    }
    
    if(canvas.RO.current_frame>0) {
        ro_single_render(&impl->move_prev_btn, cam_mat);
        
        ro_text_render(&impl->merge_txt, cam_mat);
        ro_single_render(&impl->merge_btn, cam_mat);
    }
    
    ro_text_render(&impl->frametime_txt, cam_mat);
    ro_text_render(&impl->frametime_num, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if(canvas.RO.sprite.cols<=1)
        return true;

    if (u_button_clicked(&impl->delete_btn.rect, pointer)) {
        s_log("delete dialog");
        dialog_create_prompt("Delete", "delete this\nframe?", on_delete_action, NULL);
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.RO.current_frame>0 
            && u_button_clicked(&impl->move_prev_btn.rect, pointer)) {
        s_log("move with prev frame: %i", canvas.RO.current_frame);
        
        uSprite old = canvas_get_sprite();
        uSprite swap = u_sprite_new_clone_swap_cols(
                old,
                canvas.RO.current_frame-1,
                canvas.RO.current_frame);
        u_sprite_kill(&old);
        canvas_set_sprite(swap, true);
        canvas_set_frame(canvas.RO.current_frame-1);
        dialog_create_frame();
        // return after hide, hide kills this dialog
        return true;
    }
    
    if (canvas.RO.current_frame<(canvas.RO.sprite.cols-1) 
            && u_button_clicked(&impl->move_next_btn.rect, pointer)) {
        s_log("move with next frame: %i", canvas.RO.current_frame);
        
        uSprite old = canvas_get_sprite();
        uSprite swap = u_sprite_new_clone_swap_cols(
                old,
                canvas.RO.current_frame+1,
                canvas.RO.current_frame);
        u_sprite_kill(&old);
        canvas_set_sprite(swap, true);
        canvas_set_frame(canvas.RO.current_frame+1);
        dialog_create_frame();
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.RO.current_frame>0 
            && u_button_clicked(&impl->merge_btn.rect, pointer)) {
        s_log("merge frame: %i", canvas.RO.current_frame);
        uSprite old = canvas_get_sprite();
        uSprite sprite = u_sprite_new_clone_merge_col_down(old, canvas.RO.current_frame);
        u_sprite_kill(&old);
        canvas_set_sprite(sprite, true);
        dialog_create_frame();
        // return after hide, hide kills this dialog
        return true;
    }
    
    if(pointer.id==0
            && pointer.action == E_POINTER_DOWN
            && u_pose_aa_contains(impl->frametime_hitbox, pointer.pos.xy)) {
        s_log("edit frame time");
        impl->textinput = textinput_new("Frame Time", 0);
        modal_set_textinput(impl->textinput);
        snprintf(impl->textinput->text, TEXTINPUT_MAX_CHARS, "%.2f", canvas.frame_times[canvas.RO.current_frame]);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
    }

    return true;
}

static void on_action(bool ok) {
    dialog_hide();
}


//
// public
//

void dialog_create_frame() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos = 24;
    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

    char info_txt[4];
    snprintf(info_txt, sizeof info_txt, "%-2i",
            canvas.RO.current_frame +1);
    ro_text_set_text(&impl->info, info_txt);
    s_log("size is: %s", info_txt);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 64, DIALOG_TOP - pos, 1, 2);
    
    impl->frame = ro_single_new(canvas.RO.tex);
    impl->frame.owns_tex = false;
    impl->frame.rect.sprite = (vec2) {{
        canvas.RO.current_frame,
        canvas.RO.current_frame
    }};
    
    uImage img = canvas.RO.image;
    float width = 16;
    float height = 16;
    if(img.cols > img.rows) {
        height = height * img.rows / img.cols;
    } else if(img.cols < img.rows) {
        width = width * img.cols / img.rows;
    }
    
    impl->frame.rect.pose = u_pose_new(DIALOG_LEFT+48, DIALOG_TOP - 4 - pos, width, height);
    
    pos += 18;
    

    impl->delete_txt = ro_text_new_font55(7);
    ro_text_set_text(&impl->delete_txt, "Delete:");
    ro_text_set_color(&impl->delete_txt, DIALOG_TEXT_DELETE_COLOR);
    impl->delete_txt.pose = u_pose_new(DIALOG_LEFT + 50, DIALOG_TOP - pos - 3, 1, 2);

    impl->delete_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_delete.png"));
    impl->delete_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    pos += 24;

    impl->move_txt = ro_text_new_font55(64);
    if(canvas.RO.sprite.cols<=1) {
        ro_text_set_text(&impl->move_txt, "Need more than\n"
                "a single frame\n"
                "for frame options");
    } else {
        ro_text_set_text(&impl->move_txt, "move frame:");
    }
    ro_text_set_color(&impl->move_txt, DIALOG_TEXT_COLOR);
    impl->move_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->move_prev_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_move_prev.png"));
    impl->move_prev_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->move_next_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_move_next.png"));
    impl->move_next_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 20;

    impl->merge_txt = ro_text_new_font55(32);
    char merge_txt[128];
    snprintf(merge_txt, sizeof merge_txt, "Merge frame\n"
            "into frame: %-2i", canvas.RO.current_frame);
    ro_text_set_text(&impl->merge_txt, merge_txt);
    ro_text_set_color(&impl->merge_txt, DIALOG_TEXT_COLOR);
    impl->merge_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->merge_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->merge_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 32;
    
    impl->frametime_txt = ro_text_new_font55(5);
    ro_text_set_text(&impl->frametime_txt, "time:");
    ro_text_set_color(&impl->frametime_txt, DIALOG_TEXT_COLOR);
    impl->frametime_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->frametime_num, DIALOG_TEXT_EDIT_COLOR);
    impl->frametime_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->frametime_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->frametime_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);

    dialog.impl_height = pos;

    dialog_set_title("frame", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
