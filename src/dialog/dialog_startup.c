#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/button.h"
#include "u/json.h"
#include "m/float.h"
#include "m/utils/color.h"
#include "io.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 136, 136, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 143, 255}};

//
// private
//

static void save_no_reshow() {
    s_log("save");
    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "dialog_startup");

    u_json_append_bool(member, "reshow", false);
    
    u_json_save_file(config, io_config_file(), NULL);
    e_io_savestate_save();

    u_json_kill(&config);
}

static bool load_reshow() {
    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_get_object(config, "dialog_startup");

    bool reshow;
    const bool *item = u_json_get_object_bool(member, "reshow");
    if(!item)
        reshow = true;
    else
        reshow = *item;
    
    s_log("load, reshow: %i", reshow);
    u_json_kill(&config);
    return reshow;
}


typedef struct {
    RoText info;
    
    RoText disp_txt;
    RoSingle disp_btn;
    
    RoText reshow_txt;
    RoSingle reshow_toggle;
    
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_text_kill(&impl->disp_txt);
    ro_single_kill(&impl->disp_btn);
    ro_text_kill(&impl->reshow_txt);
    ro_single_kill(&impl->reshow_toggle);
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_text_render(&impl->disp_txt, cam_mat);
    ro_single_render(&impl->disp_btn, cam_mat);
    ro_text_render(&impl->reshow_txt, cam_mat);
    ro_single_render(&impl->reshow_toggle, cam_mat);
}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    
    if(u_button_clicked(&impl->disp_btn.rect, pointer)) {
        s_log("disp btn");
        if(!u_button_is_pressed(&impl->reshow_toggle.rect)) {
            save_no_reshow();
        }
        dialog_create_display();
        // return after hide, hide kills this dialog
        return true;
    }
    
    if(u_button_toggled(&impl->reshow_toggle.rect, pointer)) {
        s_log("reshow toggled");
    }
    
    return true;
}

static void on_action(bool ok) {
    Impl *impl = dialog.impl;
    
    if(!u_button_is_pressed(&impl->reshow_toggle.rect)) {
        save_no_reshow();
    }
    dialog_hide();
}

//
// public
//


void dialog_create_startup() {
    dialog_hide();
    if(!load_reshow())
        return;
    
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;
    
    int pos = 16;
    
    impl->info = ro_text_new_font55(256);
    ro_text_set_text(&impl->info, "Welcome to Pixelc!\n\n"
            "Have a look at\n"
            "github.com\n"
            " /renehorstmann\n"
            " /pixelc\n\n"
            "for a tutorial");
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 2, DIALOG_TOP - pos, 1, 1);
    
    pos += 60;

    impl->disp_txt = ro_text_new_font55(64);
    ro_text_set_color(&impl->disp_txt, DIALOG_TEXT_COLOR);
    for(int i=0; i< (int)strlen("using a\nbig screen?"); i++) {
        impl->disp_txt.ro.rects[i].color.rgb = (vec3) {{0.2, 0.2, 1.0}};
    }
    ro_text_set_text(&impl->disp_txt, "using a\n"
            "big screen?\n"
            "change the\n"
            "display size:");
    impl->disp_txt.pose = u_pose_new(DIALOG_LEFT+4, DIALOG_TOP - pos, 1, 1);
    
    impl->disp_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_display.png"));
    impl->disp_btn.rect.pose = u_pose_new_aa(
            DIALOG_LEFT + DIALOG_WIDTH - 30, 
            DIALOG_TOP - pos - 8, 
            16, 16);
            
    pos += 30;
    
    impl->reshow_txt = ro_text_new_font55(32);
    ro_text_set_color(&impl->reshow_txt, DIALOG_TEXT_COLOR);
    ro_text_set_text(&impl->reshow_txt, "reshow\n"
            "this dialog?");
    impl->reshow_txt.pose = u_pose_new(DIALOG_LEFT+4, DIALOG_TOP - pos, 1, 1);
    
    impl->reshow_toggle = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));
    impl->reshow_toggle.rect.pose = u_pose_new_aa(
            DIALOG_LEFT + DIALOG_WIDTH - 30, 
            DIALOG_TOP - pos, 
            16, 16);
    impl->reshow_toggle.rect.sprite.x = 1;
    
    pos += 5;
    
    dialog.impl_height = pos;

    dialog_set_title("Pixelc", vec4_set(1));
    for(int i=0; i<6; i++) {
        vec3 hsv = {{i*360.0/6.0, 0.8, 0.8}};
        dialog.title.ro.rects[i].color.rgb = vec3_hsv2rgb(hsv);
    }
    ro_batch_update(&dialog.title.ro);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_ok_cb = on_action;
}

