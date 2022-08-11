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


static const uColor_s BG_A_COLOR = {{136, 124, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 136, 102, 255}};
static const vec4 TITLE_COLOR = {{0.7, 0.7, 0.7, 1}};


static int SIZES[] = {8, 16, 32};

//
// private
//

static void on_delete_action(bool ok) {
    s_log("delete: %i", ok);
    if (ok) {
        brush_delete_kernel(brush.RO.kernel_id);
        brush_save_config();
    }
    dialog_create_kernel();
}


typedef struct {
    bool was_canvas_active;

    RoText info;

    int size_x;
    RoText size_x_txt;
    RoSingle size_x_toggles[3];

    int size_y;
    RoText size_y_txt;
    RoSingle size_y_toggles[3];
    
    RoText to_canvas_txt;
    RoSingle to_canvas_btn;

    RoText from_canvas_txt;
    RoSingle from_canvas_btn;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);

    ro_text_kill(&impl->size_x_txt);
    ro_text_kill(&impl->size_y_txt);
    for(int i=0; i<3; i++) {
        ro_single_kill(&impl->size_x_toggles[i]);
        ro_single_kill(&impl->size_y_toggles[i]);
    }

    ro_text_kill(&impl->to_canvas_txt);
    ro_single_kill(&impl->to_canvas_btn);

    ro_text_kill(&impl->from_canvas_txt);
    ro_single_kill(&impl->from_canvas_btn);

    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;

    for(int i=0; i<3; i++) {
        u_button_set_pressed(&impl->size_x_toggles[i].rect, SIZES[i] == impl->size_x);
        u_button_set_pressed(&impl->size_y_toggles[i].rect, SIZES[i] == impl->size_y);
    }
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);

    ro_text_render(&impl->size_x_txt, cam_mat);
    ro_text_render(&impl->size_y_txt, cam_mat);
    for(int i=0; i<3; i++) {
        ro_single_render(&impl->size_x_toggles[i], cam_mat);
        ro_single_render(&impl->size_y_toggles[i], cam_mat);
    }

    ro_text_render(&impl->to_canvas_txt, cam_mat);
    ro_single_render(&impl->to_canvas_btn, cam_mat);

    ro_text_render(&impl->from_canvas_txt, cam_mat);
    ro_single_render(&impl->from_canvas_btn, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    for(int i=0; i<3; i++) {
        if(u_button_pressed(&impl->size_x_toggles[i].rect, pointer)) {
            impl->size_x = SIZES[i];
        }
        if(u_button_pressed(&impl->size_y_toggles[i].rect, pointer)) {
            impl->size_y = SIZES[i];
        }
    }

    if (u_button_clicked(&impl->to_canvas_btn.rect, pointer)) {
        s_log("copy tilesheet into canvas");
        // canvas_set_image takes ownership of palette
        uImage tilesheet = tile_get_tilesheet(tile.RO.tilesheet_id);
        uSprite sprite = {tilesheet, 1, 1};
        canvas_set_sprite(sprite, true);
        tile.active = false;
        cameractrl_set_home();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    if (u_button_clicked(&impl->from_canvas_btn.rect, pointer)) {
        s_log("update tilesheet from canvas");
        uImage tilesheet = canvas.RO.sprite.img;
        tile_update_tilesheet(tilesheet, tile.RO.tilesheet_id);
        tile.canvas_active = impl->was_canvas_active;
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    return true;
}

static void on_action(bool ok) {
    Impl *impl = dialog.impl;
    if(impl->size_x != tile.RO.tile_size_x || impl->size_y != tile.RO.tile_size_y) {
        s_log("setting new tile size");
        tile_set_size(impl->size_x, impl->size_y);
    }
    // show tiles
    tile.canvas_active = impl->was_canvas_active;
    cameractrl_set_home();
    dialog_hide();
}


//
// public
//

void dialog_create_tile() {
    dialog_hide();
    s_log("create");

    // show image in the background
    cameractrl_set_home();

    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->was_canvas_active = tile.canvas_active;
    tile.canvas_active = false;

    impl->size_x = tile.RO.tile_size_x;
    impl->size_y = tile.RO.tile_size_y;


    float pos = 16;
    impl->info = ro_text_new_font55(32);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

    char text[64];
    snprintf(text, sizeof text, "Tileset: %i", tile.RO.tilesheet_id);
    ro_text_set_text(&impl->info, text);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 16, DIALOG_TOP - pos - 4, 1, 2);
    pos += 20;

    impl->size_x_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->size_x_txt, "Size X:");
    ro_text_set_color(&impl->size_x_txt, DIALOG_TEXT_COLOR);
    impl->size_x_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 4, 1, 2);
    impl->size_y_txt = ro_text_new_font55(16);
    ro_text_set_text(&impl->size_y_txt, "Size Y:");
    ro_text_set_color(&impl->size_y_txt, DIALOG_TEXT_COLOR);
    impl->size_y_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 24, 1, 2);
    rTexture tex = r_texture_new_file(2, 3, "res/button_tilesize.png");
    for(int i=0; i<3; i++) {
        impl->size_x_toggles[i] = ro_single_new(tex);
        impl->size_x_toggles[i].owns_tex = false;
        impl->size_x_toggles[i].rect.sprite.y = i;
        impl->size_x_toggles[i].rect.pose = u_pose_new_aa(DIALOG_LEFT + 60 + 18*i, DIALOG_TOP - pos, 16, 16);
        impl->size_y_toggles[i] = ro_single_new(tex);
        impl->size_y_toggles[i].owns_tex = false;
        impl->size_y_toggles[i].rect.sprite.y = i;
        impl->size_y_toggles[i].rect.pose = u_pose_new_aa(DIALOG_LEFT + 60 + 18*i, DIALOG_TOP - pos - 20, 16, 16);
    }
    impl->size_x_toggles[0].owns_tex = true;

    pos += 40;

    impl->to_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->to_canvas_txt, "Copy into\n"
                                           "       canvas:");
    ro_text_set_color(&impl->to_canvas_txt, DIALOG_TEXT_COLOR);
    impl->to_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->to_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_to.png"));
    impl->to_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 28;

    impl->from_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->from_canvas_txt, "Update from\n"
                                             "       canvas:");
    ro_text_set_color(&impl->from_canvas_txt, DIALOG_TEXT_COLOR);
    impl->from_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->from_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->from_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 20;

    dialog.impl_height = pos;

    dialog_set_title("tile", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
//    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
