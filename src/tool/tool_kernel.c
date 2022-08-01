#include "u/pose.h"
#include "m/int.h"
#include "u/button.h"
#include "brush.h"
#include "camera.h"
#include "feedback.h"
#include "dialog.h"
#include "tool.h"

//
// private
//

enum button_pressed {
    BTN_NONE,
    BTN_MINUS,
    BTN_KERNEL,
    BTN_PLUS,
    BTM_NUM
};


typedef struct {
    Tool super;
    RoSingle kernel;
    RoSingle minus, plus;
    mat4 kernel_press_pose;
    int last_kernel_id;
    float long_press_time;
    enum button_pressed pressed;
} Impl;


static void kill_fn(Tool **super_ptr) {
    Impl *self = (Impl *) *super_ptr;
    if (!self)
        return;
    ro_single_kill(&self->kernel);
    ro_single_kill(&self->minus);
    ro_single_kill(&self->plus);
    s_free(self);
    *super_ptr = NULL;
}

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    Impl *self = (Impl *) super;
    int id = brush.RO.kernel_id;
    if (u_button_clicked(&self->minus.rect, pointer)
        && id > 0) {

        s_log("tool kernel_minus: %i", id - 1);
        brush_load_kernel(id - 1);
    }
    if (u_button_clicked(&self->plus.rect, pointer)
        && id < brush.RO.max_kernels - 1) {

        s_log("tool kernel_plus: %i", id + 1);
        brush_load_kernel(id + 1);
    }

    // long press
    if (u_pose_aa_contains(self->minus.rect.pose, pointer.pos.xy)) {
        if (pointer.action == E_POINTER_DOWN) {
            self->pressed = BTN_MINUS;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if (self->pressed != BTN_MINUS)
            self->pressed = BTN_NONE;
    } else if (u_pose_aa_contains(self->kernel_press_pose, pointer.pos.xy)) {
        if (pointer.action == E_POINTER_DOWN) {
            self->pressed = BTN_KERNEL;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if (self->pressed != BTN_KERNEL)
            self->pressed = BTN_NONE;
    } else if (u_pose_aa_contains(self->plus.rect.pose, pointer.pos.xy)) {
        if (pointer.action == E_POINTER_DOWN) {
            self->pressed = BTN_PLUS;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if (self->pressed != BTN_PLUS)
            self->pressed = BTN_NONE;
    } else {
        self->pressed = BTN_NONE;
    }
    if (pointer.action == E_POINTER_UP)
        self->pressed = BTN_NONE;
}

static void update(struct Tool *super, float dtime) {
    Impl *self = (Impl *) super;

    int id = brush.RO.kernel_id;
    if (self->last_kernel_id == 0 && id > 0)
        u_button_set_pressed(&self->minus.rect, false);
    if (self->last_kernel_id == brush.RO.max_kernels - 1 && id < self->last_kernel_id)
        u_button_set_pressed(&self->plus.rect, false);
    self->last_kernel_id = id;

    if (id == 0)
        u_button_set_pressed(&self->minus.rect, true);
    if (id == brush.RO.max_kernels - 1)
        u_button_set_pressed(&self->plus.rect, true);

    self->kernel.tex = brush.RO.kernel_tex;

    float l[3];
    float t[3];
    if (camera_is_portrait_mode()) {
        for (int i = 0; i < 3; i++) {
            l[i] = 1 + i * 18;
            t[i] = -1;
        }
        super->size = (vec2) {{16 * 3 + 6, 18}};
    } else {
        for (int i = 0; i < 3; i++) {
            l[i] = 1;
            t[i] = -1 - i * 18;
        }
        super->size = (vec2) {{16, 16 * 3 + 6}};
    }

    int k_w = brush.RO.kernel.cols;
    int k_h = brush.RO.kernel.rows;
    k_w = isca_min(k_w, 8);
    k_h = isca_min(k_h, 8);
    self->kernel.rect.pose = u_pose_new(
            l[1] + 8 + super->in.pos.x,
            t[1] - 8 + super->in.pos.y,
            k_w * 2, k_h * 2);
            
    u_pose_aa_set_left(&self->kernel_press_pose, l[1] + super->in.pos.x);
    u_pose_aa_set_top(&self->kernel_press_pose, t[1] + super->in.pos.y);


    u_pose_aa_set_left(&self->minus.rect.pose, l[0] + super->in.pos.x);
    u_pose_aa_set_top(&self->minus.rect.pose, t[0] + super->in.pos.y);

    u_pose_aa_set_left(&self->plus.rect.pose, l[2] + super->in.pos.x);
    u_pose_aa_set_top(&self->plus.rect.pose, t[2] + super->in.pos.y);

    // check long pressed
    if (self->pressed != BTN_NONE && self->long_press_time > 0) {
        self->long_press_time -= dtime;
        if (self->long_press_time <= 0) {
            if (self->pressed == BTN_MINUS) {
                s_log("tool kernel_minus long press");
                brush_load_kernel(0);
                feedback_longpress(u_pose_get_xy(self->minus.rect.pose),
                                    R_COLOR_BLACK);
            } else if (self->pressed == BTN_PLUS) {
                s_log("tool kernel_plus long press");
                brush_load_kernel(brush.RO.max_kernels - 1);
                feedback_longpress(u_pose_get_xy(self->plus.rect.pose),
                                    R_COLOR_WHITE);
            } else if (self->pressed == BTN_KERNEL) {
                s_log("tool kernel long press");
                feedback_longpress(u_pose_get_xy(self->kernel_press_pose),
                                    R_COLOR_CYAN);
                dialog_create_kernel();
            }
            self->pressed = BTN_NONE;
        }
    }
}

static void render(const struct Tool *super, const mat4 *cam_mat) {
    const Impl *self = (const Impl *) super;
    ro_single_render(&self->kernel, cam_mat);
    ro_single_render(&self->minus, cam_mat);
    ro_single_render(&self->plus, cam_mat);
}

//
// public
//

Tool *tool_new_kernel() {
    Impl *self = s_malloc0(sizeof *self);

    self->kernel = ro_single_new(r_texture_new_invalid());
    self->kernel.owns_tex = false;
    self->minus = ro_single_new(r_texture_new_file(2, 1, "res/button_kernel_minus.png"));
    self->plus = ro_single_new(r_texture_new_file(2, 1, "res/button_kernel_plus.png"));
    self->minus.rect.pose = u_pose_new(0, 0, 16, 16);
    self->plus.rect.pose = u_pose_new(0, 0, 16, 16);
    
    self->kernel_press_pose = u_pose_new(0, 0, 16, 16);

    snprintf(self->super.name, TOOL_NAME_LEN, "kernel");
    snprintf(self->super.tip, TOOL_TIP_LEN, "select a \n"
            "Kernel / Stamp\n\n"
            "Long press for\n"
            "first / last\n"
            "and options");

    self->super.kill = kill_fn;
    self->super.update = update;
    self->super.render = render;
    self->super.pointer_event = pointer_event;

    return (Tool *) self;
}
