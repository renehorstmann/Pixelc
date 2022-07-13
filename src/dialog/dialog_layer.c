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
        uImage img = u_image_new_clone_remove_layer(canvas.RO.image, canvas.current_layer);
        canvas_set_image(img, true);
        dialog_create_layer();
    } else 
        dialog_hide();
}


typedef struct {
    RoText info;
    RoSingle layer;

    RoText delete_txt;
    RoSingle delete_btn;
    
    RoText swap_txt;
    RoSingle swap_prev_btn;
    RoSingle swap_next_btn;

    RoText merge_txt;
    RoSingle merge_btn;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->layer);

    ro_text_kill(&impl->delete_txt);
    ro_single_kill(&impl->delete_btn);
    
    ro_text_kill(&impl->swap_txt);
    ro_single_kill(&impl->swap_prev_btn);
    ro_single_kill(&impl->swap_next_btn);
    
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
    
    if (canvas.RO.image.layers > 1) {
        ro_text_render(&impl->delete_txt, cam_mat);
        ro_single_render(&impl->delete_btn, cam_mat);
        
    }

    ro_text_render(&impl->swap_txt, cam_mat);
    
    if(canvas.current_layer<canvas.RO.image.layers-1) {
        ro_single_render(&impl->swap_next_btn, cam_mat);
    }
    
    if(canvas.current_layer>0) {
        ro_single_render(&impl->swap_prev_btn, cam_mat);
        
        ro_text_render(&impl->merge_txt, cam_mat);
        ro_single_render(&impl->merge_btn, cam_mat);
    }
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if(canvas.RO.image.layers<=1)
        return true;

    if (u_button_clicked(&impl->delete_btn.rect, pointer)) {
        s_log("delete dialog");
        dialog_create_prompt("Delete", "delete this\nlayer?", on_delete_action, NULL);
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.current_layer>0 
            && u_button_clicked(&impl->swap_prev_btn.rect, pointer)) {
        s_log("swap with prev layer: %i", canvas.current_layer);
        
        uImage swap = u_image_new_clone(canvas.RO.image);
        memcpy(u_image_layer(swap, canvas.current_layer-1), 
                u_image_layer(canvas.RO.image, canvas.current_layer),    
                u_image_layer_data_size(swap));
        memcpy(u_image_layer(swap, canvas.current_layer), 
                u_image_layer(canvas.RO.image, canvas.current_layer-1),    
                u_image_layer_data_size(swap));
        
        canvas_set_image(swap, true);
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }
    
    if (canvas.current_layer<(canvas.RO.image.layers-1) 
            && u_button_clicked(&impl->swap_next_btn.rect, pointer)) {
        s_log("swap with next layer: %i", canvas.current_layer);
        
        uImage swap = u_image_new_clone(canvas.RO.image);
        memcpy(u_image_layer(swap, canvas.current_layer+1), 
                u_image_layer(canvas.RO.image, canvas.current_layer),    
                u_image_layer_data_size(swap));
        memcpy(u_image_layer(swap, canvas.current_layer), 
                u_image_layer(canvas.RO.image, canvas.current_layer+1),    
                u_image_layer_data_size(swap));
        
        canvas_set_image(swap, true);
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.current_layer>0 
            && u_button_clicked(&impl->merge_btn.rect, pointer)) {
        s_log("merge layer: %i", canvas.current_layer);
        uImage img = u_image_new_clone_merge_down(canvas.RO.image, canvas.current_layer);
        canvas_set_image(img, true);
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
            canvas.current_layer +1);
    ro_text_set_text(&impl->info, info_txt);
    s_log("size is: %s", info_txt);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 64, DIALOG_TOP - pos, 1, 2);
    
    uImage img = canvas.RO.image;
    rTexture tex = r_texture_new(img.cols, img.rows, 1, 1, u_image_layer(img, canvas.current_layer));
    impl->layer = ro_single_new(tex);
    
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

    impl->swap_txt = ro_text_new_font55(64);
    if(canvas.RO.image.layers<=1) {
        ro_text_set_text(&impl->swap_txt, "Need more than\n"
                "a single layer\n"
                "for layer options");
    } else {
        ro_text_set_text(&impl->swap_txt, "swap layer:");
    }
    ro_text_set_color(&impl->swap_txt, (vec4) {{0.9, 0.9, 0.9, 1}});
    impl->swap_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 2, 1, 2);

    impl->swap_prev_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_move_prev.png"));
    impl->swap_prev_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 40, DIALOG_TOP - pos, 16, 16);
    
    impl->swap_next_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_move_next.png"));
    impl->swap_next_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos, 16, 16);
    
    pos += 20;

    impl->merge_txt = ro_text_new_font55(32);
    char merge_txt[128];
    snprintf(merge_txt, sizeof merge_txt, "Merge layer\n"
            "into layer: %-2i", canvas.current_layer);
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
    dialog.opt_on_cancel_cb = on_action;
//    dialog.opt_on_ok_cb = on_action;
}
