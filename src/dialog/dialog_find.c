#include "r/r.h"
#include "u/pose.h"
#include "u/button.h"
#include "textinput.h"
#include "canvas.h"
#include "cameractrl.h"
#include "find.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{136, 136, 102, 255}};
static const uColor_s BG_B_COLOR = {{143, 143, 102, 255}};
static const vec4 TITLE_COLOR = {{0.6, 0.8, 0.6, 1}};

//
// private
//

typedef struct {
    RoText info;
    RoSingle pattern;

    RoText to_canvas_txt;
    RoSingle to_canvas_btn;

    RoText from_canvas_txt;
    RoSingle from_canvas_btn;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->info);
    ro_single_kill(&impl->pattern);

    ro_text_kill(&impl->to_canvas_txt);
    ro_single_kill(&impl->to_canvas_btn);

    ro_text_kill(&impl->from_canvas_txt);
    ro_single_kill(&impl->from_canvas_btn);

    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->info, cam_mat);
    ro_single_render(&impl->pattern, cam_mat);

    ro_text_render(&impl->to_canvas_txt, cam_mat);
    ro_single_render(&impl->to_canvas_btn, cam_mat);

    if(canvas.RO.frames >= FIND_MIN_COLS) {
        ro_text_render(&impl->from_canvas_txt, cam_mat);
        ro_single_render(&impl->from_canvas_btn, cam_mat);
    }
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if (u_button_clicked(&impl->to_canvas_btn.rect, pointer)) {
        s_log("copy pattern into canvas");
        // canvas_set_image takes ownership of palette
        uSprite sprite = find_get_pattern_template();
        canvas_set_sprite(sprite, true);
        cameractrl_set_home();
        dialog_hide();
        // return after hide, hide kills this dialog
        return true;
    }

    if (canvas.RO.frames >= FIND_MIN_COLS && u_button_clicked(&impl->from_canvas_btn.rect, pointer)) {
        s_log("new pattern from canvas");
        uSprite sprite = canvas_get_sprite();

        // for both if layers or frames are disabled, useful, else up to the current frame, layer
        // easier for frames, because current_frame 0 is equal to frames off
        int targets = canvas.RO.current_frame>0? canvas.RO.current_frame : sprite.cols-1;
        int runs;
        if(canvas.RO.sprite.rows == 1) {
            runs = canvas.RO.layers;
        } else {
            runs = canvas.RO.current_layer+1;
        }

        // copy up to targets(+1) and runs
        uSprite pattern = u_sprite_new_empty(sprite.img.cols, sprite.img.rows, targets+1, runs);
        for(int r=0; r<pattern.rows; r++) {
            for(int c=0; c<pattern.cols; c++) {
                memcpy(u_sprite_sprite(pattern, c, r), u_sprite_sprite(sprite, c, r), u_sprite_sprite_data_size(pattern));
            }
        }

        // pattern and max target, run
        find_set_pattern_template(pattern, sprite.cols-1, sprite.rows);

        u_sprite_kill(&pattern);
        u_sprite_kill(&sprite);

        // restart dialog
        dialog_create_find();
        // return after hide, create calls hide that kills this dialog
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

void dialog_create_find() {
    dialog_hide();
    canvas_reload();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    float pos = 16;
    impl->info = ro_text_new_font55(128);
    ro_text_set_color(&impl->info, DIALOG_TEXT_COLOR);

    char text[64];
    uSprite sprite = find_get_pattern_template();
    ivec2 max = find_get_max_targets_runs();
    snprintf(text, sizeof text, "targets: %i/%i\n"
                                "runs:    %i/%i",
                                sprite.cols-1, max.x,
                                sprite.rows, max.y);
    ro_text_set_text(&impl->info, text);
    impl->info.pose = u_pose_new(DIALOG_LEFT + 42, DIALOG_TOP - pos - 4, 1, 2);

    rTexture tex = r_texture_new_invalid();
    if(sprite.img.cols>0 && sprite.img.rows>0) {
        tex = r_texture_new(sprite.img.cols, sprite.img.rows, 1, 1, sprite.img.data);
    }
    impl->pattern = ro_single_new(tex);
    impl->pattern.rect.pose = u_pose_new(DIALOG_LEFT + 4 + 16, DIALOG_TOP - pos - 16, 32, 32);

    u_sprite_kill(&sprite);

    pos += 34;


    impl->to_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->to_canvas_txt, "Copy into\n"
                                           "       canvas:");
    ro_text_set_color(&impl->to_canvas_txt, DIALOG_TEXT_COLOR);
    impl->to_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->to_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_to.png"));
    impl->to_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 28;

    impl->from_canvas_txt = ro_text_new_font55(32);
    ro_text_set_text(&impl->from_canvas_txt, "New pattern\n"
                                             "  from canvas:");
    ro_text_set_color(&impl->from_canvas_txt, DIALOG_TEXT_COLOR);
    impl->from_canvas_txt.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos - 3, 1, 2);

    impl->from_canvas_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_from.png"));
    impl->from_canvas_btn.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 20, DIALOG_TOP - pos - 10, 16, 16);
    pos += 12;

    dialog_set_title("find", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.impl_height = pos;
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_ok_cb = on_action;
}
