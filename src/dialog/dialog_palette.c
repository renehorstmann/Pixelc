#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "mathc/int.h"
#include "palette.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"

//
// private
//


typedef struct {
    RoText info;
    RoText delete_txt;
    RoSingle delete_btn;
    
    RoSingle upload;
    bool upload_available;
} Impl;

static void kill_fn(void *impl) {
    Impl *self = impl;
    ro_text_kill(&self->info);
    ro_text_kill(&self->delete_txt);
    ro_single_kill(&self->delete_btn);
    
    ro_single_kill(&self->upload);
    rhc_free(self);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_text_render(&impl->delete_txt, cam_mat);
    ro_single_render(&impl->delete_btn, cam_mat);
    
    if (impl->upload_available)
        ro_single_render(&impl->upload, cam_mat);
}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    
    if(u_button_clicked(&impl->delete_btn.rect, pointer)) {
        log_info("delete dialog");
        dialog_hide();
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
    log_info("create");
    Impl *impl = rhc_calloc(sizeof *impl);
    dialog.impl = impl;

    int pos = 20;
    impl->info = ro_text_new_font55(2*PALETTE_NAME_MAX);
    ro_text_set_color(&impl->info, (vec4) {{0.9, 0.9, 0.9, 1}});
    
    //snprintf(palette.RO.palette_name, PALETTE_NAME_MAX, "1234567890123456789012345678901234567890");
    
    char name[2*PALETTE_NAME_MAX] = {0};
    {
        int size = strlen(palette.RO.palette_name);
        strncpy(name, palette.RO.palette_name, isca_min(size, 18));
        if(size>18) {
            strcat(name, "\n  ");
            strcat(name, palette.RO.palette_name+18);
        }
    }
    ro_text_set_text(&impl->info, name);
    log_info("name is: %s", palette.RO.palette_name);    
    impl->info.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - pos, 1, 2);

    pos += 22;
    
    impl->delete_txt = ro_text_new_font55(7);
    ro_text_set_text(&impl->delete_txt, "Delete:");
    ro_text_set_color(&impl->delete_txt, (vec4) {{0.7, 0.0, 0.2, 1.0}});
    impl->delete_txt.pose = u_pose_new(DIALOG_LEFT+50, DIALOG_TOP-pos-3, 1, 2);
    
    impl->delete_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_delete.png"));
    impl->delete_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 24, DIALOG_TOP - pos, 16, 16);
    
    pos += 16;

#ifdef __EMSCRIPTEN__
    impl->upload = ro_single_new(r_texture_new_file(2, 1, "res/button_dialog_upload.png"));
    impl->upload_available = true;
    impl->upload.rect.pose = u_pose_new_aa(DIALOG_LEFT + 8, DIALOG_TOP-62, 64, 16);
#endif

    dialog.impl_height = pos;

    dialog_set_title("palette", (vec4) {{0.6, 0.2, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = tooltip_on_action;
    dialog.opt_on_ok_cb = on_action;
}

