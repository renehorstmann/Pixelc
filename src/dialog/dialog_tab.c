#include "e/io.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/button.h"
#include "m/int.h"
#include "canvas.h"
#include "cameractrl.h"
#include "dialog.h"

#define BG_A "#666666"
#define BG_B "#777777"

#define ROWS 3
#define COLS 3

#define WIDTH 32
#define HEIGHT 32

#define OFFSET 4

//
// private
//

_Static_assert(CANVAS_MAX_TABS == 9, "rewrite this file with a container, etc.");

static uImage create_tab_img(int tab_id) {
    uImage layers = canvas_get_tab(tab_id);
    uImage tab = u_image_new_clone_merge_down_full(layers);
    u_image_kill(&layers);
    return tab;
}

typedef struct {
    RoBatch img_bg;
    RoSingle imgs[CANVAS_MAX_TABS];
} Impl;

static void kill_fn() {
    // should not be called...
    Impl *impl = dialog.impl;
    ro_batch_kill(&impl->img_bg);
    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        ro_single_kill(&impl->imgs[i]);
    }
    s_free(impl);
}

static void update(float dtime) {
    // noop
}

static void render(const mat4 *cam_mat) {
    Impl *impl = dialog.impl;
    ro_batch_render(&impl->img_bg, cam_mat, false);
    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        ro_single_render(&impl->imgs[i], cam_mat);
    }
}


static bool pointer_event(ePointer_s pointer) {
    Impl *impl = dialog.impl;
    if(pointer.action != E_POINTER_DOWN)
        return true;
    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        if(u_pose_aa_contains(impl->img_bg.rects[i].pose, pointer.pos.xy)) {
            canvas_set_tab_id(i);
            cameractrl_set_home();
            dialog_hide();
            return true;
        }
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


void dialog_create_tab() {
    dialog_hide();
    s_log("create");
    Impl *impl = s_malloc0(sizeof *impl);
    dialog.impl = impl;

    impl->img_bg = ro_batch_new(CANVAS_MAX_TABS, r_texture_new_white_pixel());
    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        uImage img = create_tab_img(i);
        impl->imgs[i] = ro_single_new(r_texture_new(img.cols, img.rows, 1, 1, img.data));

        int r = i / ROWS;
        int c = i % COLS;

        int left = DIALOG_LEFT + (DIALOG_WIDTH - COLS * WIDTH - (COLS - 1) * OFFSET) / 2 + WIDTH/2;
        int top = DIALOG_TOP - 20 - HEIGHT/2;
        float width = WIDTH;
        float height = HEIGHT;

        impl->img_bg.rects[i].pose = u_pose_new(
                left + c * (WIDTH + OFFSET),
                top - r * (HEIGHT + OFFSET),
                width, height);
        impl->img_bg.rects[i].color.a = 0.25;

        if(img.cols > img.rows) {
            height = height * img.rows / img.cols;
        } else if(img.cols < img.rows) {
            width = width * img.cols / img.rows;
        }

        impl->imgs[i].rect.pose = u_pose_new(
                left + c * (WIDTH + OFFSET),
                top - r * (HEIGHT + OFFSET),
                width, height);

        u_image_kill(&img);
    }

    ro_batch_update(&impl->img_bg);

    dialog.impl_height = 110;

    dialog_set_title("tab", (vec4) {{0.2, 0.6, 0.2, 1}});
    dialog_set_bg_color(u_color_from_hex(BG_A), u_color_from_hex(BG_B));
    dialog.kill = kill_fn;
    dialog.update = update;
    dialog.render = render;
    dialog.pointer_event = pointer_event;
    dialog.opt_on_cancel_cb = on_action;
}

