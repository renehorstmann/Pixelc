#include "r/r.h"
#include "u/pose.h"
#include "u/button.h"
#include "textinput.h"
#include "canvas.h"
#include "cameractrl.h"
#include "modal.h"
#include "dialog.h"

static const uColor_s BG_A_COLOR = {{102, 102, 136, 255}};
static const uColor_s BG_B_COLOR = {{102, 102, 143, 255}};
static const vec4 TITLE_COLOR = {{0.6, 0.2, 0.6, 1}};

//
// private
//

typedef struct {
    int cols;
    RoText cols_text;
    RoText cols_num;
    mat4 cols_hitbox;

    int rows;
    RoText rows_text;
    RoText rows_num;
    mat4 rows_hitbox;
    
    int frames;
    RoText frames_text;
    RoText frames_num;
    mat4 frames_hitbox;

    int layers;
    RoText layers_text;
    RoText layers_num;
    mat4 layers_hitbox;

    RoText keep_order_txt;
    RoSingle keep_order_toggle;

    RoText scale_txt;
    RoSingle scale_toggle;

    int textinput_usage;
    TextInput *textinput;
} Impl;

static void kill_fn() {
    Impl *impl = dialog.impl;
    ro_text_kill(&impl->cols_text);
    ro_text_kill(&impl->cols_num);
    ro_text_kill(&impl->rows_text);
    ro_text_kill(&impl->rows_num);
    ro_text_kill(&impl->frames_text);
    ro_text_kill(&impl->frames_num);
    ro_text_kill(&impl->layers_text);
    ro_text_kill(&impl->layers_num);
    ro_text_kill(&impl->keep_order_txt);
    ro_single_kill(&impl->keep_order_toggle);
    ro_text_kill(&impl->scale_txt);
    ro_single_kill(&impl->scale_toggle);
    textinput_kill(&impl->textinput);
    s_free(impl);
}

static void update(float dtime) {
    Impl *impl = dialog.impl;

    if (impl->textinput) {

        char *end;
        int size = strtol(impl->textinput->text, &end, 10);
        bool ok = end && end != impl->textinput->text && size > 0 && size <= CANVAS_MAX_SIZE;
        if (ok && impl->textinput_usage == 2
            && size > CANVAS_MAX_LAYERS)
            ok = false;
        impl->textinput->ok_active = ok;

        if (impl->textinput->state == TEXTINPUT_DONE) {
            switch (impl->textinput_usage) {
                case 0:
                    impl->cols = size;
                    break;
                case 1:
                    impl->rows = size;
                    break;
                case 2:
                    impl->frames = size;
                    break;
                case 3:
                    impl->layers = size;
                    break;
                default:
                    s_assume(0, "wtf");
            }
        }
        if (impl->textinput->state != TEXTINPUT_IN_PROGRESS) {
            textinput_kill(&impl->textinput);
            modal_set_textinput(NULL);
        }
    }

    char buf[16];
    snprintf(buf, sizeof buf, "%i", impl->cols);
    ro_text_set_text(&impl->cols_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->rows);
    ro_text_set_text(&impl->rows_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->frames);
    ro_text_set_text(&impl->frames_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->layers);
    ro_text_set_text(&impl->layers_num, buf);
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_text_render(&impl->cols_text, cam_mat);
    ro_text_render(&impl->cols_num, cam_mat);
    ro_text_render(&impl->rows_text, cam_mat);
    ro_text_render(&impl->rows_num, cam_mat);
    ro_text_render(&impl->frames_text, cam_mat);
    ro_text_render(&impl->frames_num, cam_mat);
    ro_text_render(&impl->layers_text, cam_mat);
    ro_text_render(&impl->layers_num, cam_mat);
    ro_text_render(&impl->keep_order_txt, cam_mat);
    ro_single_render(&impl->keep_order_toggle, cam_mat);
    ro_text_render(&impl->scale_txt, cam_mat);
    ro_single_render(&impl->scale_toggle, cam_mat);
}

static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;

    if(u_button_toggled(&impl->keep_order_toggle.rect, pointer)) {
        s_log("keep_order toggled");
    }

    if(u_button_toggled(&impl->scale_toggle.rect, pointer)) {
        s_log("scale toggled");
    }

    if (pointer.id != 0 || pointer.action != E_POINTER_DOWN)
        return true;
        
    if (u_pose_aa_contains(impl->cols_hitbox, pointer.pos.xy)) {
        impl->textinput = textinput_new("Set canvas cols", 8);
        snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->cols);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
        impl->textinput_usage = 0;
    } else if (u_pose_aa_contains(impl->rows_hitbox, pointer.pos.xy)) {
        impl->textinput = textinput_new("Set canvas rows", 8);
        snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->rows);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
        impl->textinput_usage = 1;
    } else if (u_pose_aa_contains(impl->frames_hitbox, pointer.pos.xy)) {
        impl->textinput = textinput_new("Set frames", 8);
        snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->frames);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
        impl->textinput_usage = 2;
    } else if (u_pose_aa_contains(impl->layers_hitbox, pointer.pos.xy)) {
        impl->textinput = textinput_new("Set layers", 8);   
        snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->layers);
        impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
        impl->textinput_usage = 3;
    } 

    if(impl->textinput)
        modal_set_textinput(impl->textinput);

    return true;
}

static void on_action(bool ok) {
    Impl *impl = dialog.impl;
    int cols = impl->cols;
    int rows = impl->rows;
    int frames = impl->frames;
    int layers = impl->layers;
    bool keep_order = u_button_is_pressed(&impl->keep_order_toggle.rect);
    bool scale = u_button_is_pressed(&impl->scale_toggle.rect);

    dialog_hide();
    if (!ok) {
        s_log("dialog size aborted");
        return;
    }
    
    s_log("dialog size: new size %i %i, %i %i", cols, rows, frames, layers);

    uSprite sprite;
    if(keep_order) {
        s_log("reset size with order");
        uSprite c = canvas_get_sprite();
        if(scale) {
            sprite = u_sprite_new_clone_scaled(cols, rows, false, c);
        } else {
            sprite = u_sprite_new_zeros(cols, rows, frames, layers);
            int fm = s_min(frames, c.cols);
            int lm = s_min(layers, c.rows);
            for(int l=0; l<lm; l++) {
                for(int f=0; f<fm; f++) {
                    uImage from = c.img;
                    from.data = u_sprite_sprite(c, f, l);
                    from.layers = 1;
                    uImage to = sprite.img;
                    to.data = u_sprite_sprite(sprite, f, l);
                    to.layers = 1;
                    u_image_copy_top_left(to, from);
                }
            }
        }

        u_sprite_kill(&c);
    } else {
        s_log("reset size without order");
        uImage img = canvas_get_full_image();
        uImage new_img;

        if(scale) {
            new_img = u_image_new_clone_scaled(cols*frames, rows*layers, false, img);
        } else {
            new_img = u_image_new_zeros(cols*frames, rows*layers, 1);
            u_image_copy_top_left(new_img, img);
        }

        new_img.rows = rows;
        new_img.layers = layers;

        sprite = u_sprite_new_reorder_from_image(frames, new_img);
        u_image_kill(&img);
        u_image_kill(&new_img);
    }
    
    canvas_set_sprite(sprite, true);
    cameractrl_set_home();
}

//
// public
//

void dialog_create_size() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    int pos = 20;

    impl->cols = canvas.RO.cols;
    impl->cols_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->cols_text, "cols:");
    ro_text_set_color(&impl->cols_text, DIALOG_TEXT_COLOR);
    impl->cols_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->cols_num, DIALOG_TEXT_EDIT_COLOR);
    impl->cols_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->cols_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->cols_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    pos += 15;

    impl->rows = canvas.RO.rows;
    impl->rows_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->rows_text, "rows:");
    ro_text_set_color(&impl->rows_text, DIALOG_TEXT_COLOR);
    impl->rows_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->rows_num, DIALOG_TEXT_EDIT_COLOR);
    impl->rows_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->rows_num.pose = u_pose_new(DIALOG_LEFT + 40, DIALOG_TOP - pos, 1, 2);
    impl->rows_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    pos += 20;

    impl->frames = canvas.RO.frames;
    impl->frames_text = ro_text_new_font55(7);
    ro_text_set_text(&impl->frames_text, "frames:");
    ro_text_set_color(&impl->frames_text, DIALOG_TEXT_COLOR);
    impl->frames_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->frames_num, DIALOG_TEXT_EDIT_COLOR);
    impl->frames_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->frames_num.pose = u_pose_new(DIALOG_LEFT + 52, DIALOG_TOP - pos, 1, 2);
    impl->frames_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    pos += 15;

    impl->layers = canvas.RO.layers;
    impl->layers_text = ro_text_new_font55(7);
    ro_text_set_text(&impl->layers_text, "layers:");
    ro_text_set_color(&impl->layers_text, DIALOG_TEXT_COLOR);
    impl->layers_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->layers_num, DIALOG_TEXT_EDIT_COLOR);
    impl->layers_text.pose = u_pose_new(DIALOG_LEFT + 8, DIALOG_TOP - pos, 1, 2);
    impl->layers_num.pose = u_pose_new(DIALOG_LEFT + 52, DIALOG_TOP - pos, 1, 2);
    impl->layers_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP - pos + 4, DIALOG_WIDTH, 10 + 8);
    pos += 20;

    impl->keep_order_txt = ro_text_new_font55(16);
    ro_text_set_color(&impl->keep_order_txt, DIALOG_TEXT_COLOR);
    ro_text_set_text(&impl->keep_order_txt, "keep order?");
    impl->keep_order_txt.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - pos, 1, 2);

    impl->keep_order_toggle = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));
    impl->keep_order_toggle.rect.pose = u_pose_new_aa(
            DIALOG_LEFT + DIALOG_WIDTH - 30,
            DIALOG_TOP - pos + 2,
            16, 16);
    pos += 18;

    impl->scale_txt = ro_text_new_font55(16);
    ro_text_set_color(&impl->scale_txt, DIALOG_TEXT_COLOR);
    ro_text_set_text(&impl->scale_txt, "scale?");
    impl->scale_txt.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP - pos, 1, 2);

    impl->scale_toggle = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));
    impl->scale_toggle.rect.pose = u_pose_new_aa(
            DIALOG_LEFT + DIALOG_WIDTH - 30,
            DIALOG_TOP - pos + 2,
            16, 16);

    pos += 5;


    dialog_set_title("size", TITLE_COLOR);
    dialog_set_bg_color(BG_A_COLOR, BG_B_COLOR);
    dialog.impl_height = pos;
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
    dialog.opt_on_ok_cb = on_action;
}
