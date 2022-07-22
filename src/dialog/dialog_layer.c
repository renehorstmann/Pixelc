#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "brush.h"
#include "canvas.h"
#include "cameractrl.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//

static void on_delete_action(bool ok) {
    s_log("delete: %i", ok);
    if (ok) {
        uSprite old = canvas_get_sprite();
        uSprite sprite = u_sprite_new_clone_remove_row(canvas.RO.sprite, canvas.RO.current_layer);
        u_sprite_kill(&old);
        canvas_set_sprite(sprite, true);
        dialog_create_layer();
    } else 
        dialog_hide();
}


typedef struct {
    RoText info;
    RoSingle layer;

    RoText delete_txt;
    RoSingle delete_btn;
    
    RoText move_txt;
    RoSingle move_prev_btn;
    RoSingle move_next_btn;

    RoText merge_txt;
    RoSingle merge_btn;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->layer);

    ro_text_kill(&impl->delete_txt);
    ro_single_kill(&impl->delete_btn);
    
    ro_text_kill(&impl->move_txt);
    ro_single_kill(&impl->move_prev_btn);
    ro_single_kill(&impl->move_next_btn);
    
    ro_text_kill(&impl->merge_txt);
    ro_single_kill(&impl->merge_btn);

    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_single_render(&impl->layer, cam_mat);
    
    if (canvas.RO.sprite.rows > 1) {
        ro_text_render(&impl->delete_txt, cam_mat);
        ro_single_render(&impl->delete_btn, cam_mat);
        
    }

    ro_text_render(&impl->move_txt, cam_mat);
    
    if(canvas.RO.current_layer<canvas.RO.sprite.rows-1) {
        ro_single_render(&impl->move_next_btn, cam_mat);
    }
    
    if(canvas.RO.current_layer>0) {
        ro_single_render(&impl->move_prev_btn, cam_mat);
        
        ro_text_render(&impl->merge_txt, cam_mat);
        ro_single_render(&impl->merge_btn, cam_mat);
    }
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if(canvas.RO.sprite.rows<=1)
        return true;

    if (u_button_clicked(&impl->delete_btn.rect, pointer)) {
        s_log("delete dialog");
        dialog_create_prompt("Delete", "delete this\nlayer?", on_delete_action, NULL);
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.RO.current_layer>0 
            && u_button_clicked(&impl->move_prev_btn.rect, pointer)) {
        s_log("move with prev layer: %i", canvas.RO.current_layer);
        
        uSprite old = canvas_get_sprite();
        uSprite swap = u_sprite_new_clone_swap_rows(
                old,
                canvas.RO.current_layer-1,
                canvas.RO.current_layer);
        u_sprite_kill(&old);
        canvas_set_sprite(swap, true);
        canvas_set_layer(canvas.RO.current_layer-1);
        dialog_create_layer();
        // return after hide, hide kills this dialog
        return true;
    }
    
    if (canvas.RO.current_layer<(canvas.RO.sprite.rows-1) 
            && u_button_clicked(&impl->move_next_btn.rect, pointer)) {
        s_log("move with next layer: %i", canvas.RO.current_layer);
        
        uSprite old = canvas_get_sprite();
        uSprite swap = u_sprite_new_clone_swap_rows(
                old,
                canvas.RO.current_layer+1,
                canvas.RO.current_layer);
        u_sprite_kill(&old);
        canvas_set_sprite(swap, true);
        canvas_set_layer(canvas.RO.current_layer+1);
        dialog_create_layer();
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.RO.current_layer>0 
            && u_button_clicked(&impl->merge_btn.rect, pointer)) {
        s_log("merge layer: %i", canvas.RO.current_layer);
        
        uSprite old = canvas_get_sprite();
        uSprite sprite = u_sprite_new_clone_merge_row_down(old, canvas.RO.current_layer);
        u_sprite_kill(&old);
        canvas_set_sprite(sprite, true);
        dialog_create_layer();
        // return after hide, hide kills this dialog
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

void dialog_create_layer() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos = 24;
    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});

    char info_txt[4];
    snprintf(info_txt, sizeof info_txt, "%-2i",
            canvas.RO.current_layer +1);
    ro_text_set_text(&impl->info, info_txt);
    s_log("size is: %s", info_txt);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 64, DIALOG_TOP - pos, 1, 2);
    
    impl->layer = ro_single_new(canvas.RO.tex);
    impl->layer.owns_tex = false;
    impl->layer.rect.sprite = (vec2) {{
        canvas.RO.current_frame,
        canvas.RO.current_layer
    }};
    
    uImage img = canvas.RO.image;
    float width = 16;
    float height = 16;
    if(img.cols > img.rows) {
        height = height * img.rows / img.cols;
    } else if(img.cols < img.rows) {
        width = width * img.cols / img.rows;
    }
    
    impl->layer.rect.pose = u_pose_new(DIALOG_LEFT+48, DIALOG_TOP - 4 - pos, width, height);
    
    pos += 18;
    

    impl->delete_txt = ro_text_new_font55(7);
    ro_text_set_text(&impl->delete_txt, "Delete:");
    ro_text_set_color(&impl->delete_txt, (vec4) {{0.7, 0.0, 0.2, 1.0}});
    impl->delete_txt.pose = u_pose_new(DIALOG_LEFT + 50, DIALOG_TOP - pos - 3, 1, 2);

    impl->delete_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_delete.png"));
    impl->delete_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    pos += 24;

    impl->move_txt = ro_text_new_font55(64);
    if(canvas.RO.sprite.rows<=1) {
        ro_text_set_text(&impl->move_txt, "Need more than\n"
                "a single layer\n"
                "for layer options");
    } else {
        ro_text_set_text(&impl->move_txt, "move layer:");
    }
    ro_text_set_color(&impl->move_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->move_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->move_prev_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_move_prev.png"));
    impl->move_prev_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->move_next_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_move_next.png"));
    impl->move_next_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 20;

    impl->merge_txt = ro_text_new_font55(32);
    char merge_txt[128];
    snprintf(merge_txt, sizeof merge_txt, "Merge layer\n"
            "into layer: %-2i", canvas.RO.current_layer);
    ro_text_set_text(&impl->merge_txt, merge_txt);
    ro_text_set_color(&impl->merge_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->merge_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->merge_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->merge_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 32;

    dialog.impl_height = pos;

    dialog_set_title("layer", (vec4) {{0.2, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
