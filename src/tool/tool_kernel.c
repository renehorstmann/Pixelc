#include "u/pose.h"
#include "mathc/int.h"
#include "u/button.h"
#include "brush.h"
#include "camera.h"
#include "animation.h"
#include "tool.h"

//
// private
//


typedef struct {
    Tool super;
    RoSingle kernel;
    RoSingle minus, plus;
    int last_kernel_id;
    float long_press_time;
    int pressed;
} Impl;


static void kill_fn(Tool **super_ptr) {
    Impl *self = (Impl *) *super_ptr;
    if (!self)
        return;
    ro_single_kill(&self->kernel);
    ro_single_kill(&self->minus);
    ro_single_kill(&self->plus);
    rhc_free(self);
    *super_ptr = NULL;
}

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    Impl *self = (Impl *) super;
    int id = brush.RO.kernel_id;
    if (u_button_clicked(&self->minus.rect, pointer)
        && id > 0) {

        log_info("tool kernel_minus: %i", id - 1);
        brush_load_kernel(id - 1);
    }
    if (u_button_clicked(&self->plus.rect, pointer)
        && id < brush.RO.max_kernels - 1) {

        log_info("tool kernel_plus: %i", id + 1);
        brush_load_kernel(id + 1);
    }

    // long press
    if (u_pose_aa_contains(self->minus.rect.pose, pointer.pos.xy)) {
        if (pointer.action == E_POINTER_DOWN) {
            self->pressed = 1;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if (self->pressed != 1)
            self->pressed = 0;
    } else if (u_pose_aa_contains(self->plus.rect.pose, pointer.pos.xy)) {
        if (pointer.action == E_POINTER_DOWN) {
            self->pressed = 2;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if (self->pressed != 2)
            self->pressed = 0;
    } else {
        self->pressed = 0;
    }
    if (pointer.action == E_POINTER_UP)
        self->pressed = 0;
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
            l[i] = 1 + i * 17;
            t[i] = -1;
        }
        super->size = (vec2) {{16 * 3 + 4, 18}};
    } else {
        for (int i = 0; i < 3; i++) {
            l[i] = 1;
            t[i] = -1 - i * 17;
        }
        super->size = (vec2) {{18, 16 * 3 + 4}};
    }

    int k_w = brush.RO.kernel.cols;
    int k_h = brush.RO.kernel.rows;
    k_w = isca_min(k_w, 8);
    k_h = isca_min(k_h, 8);
    self->kernel.rect.pose = u_pose_new(
            l[1] + 8 + super->in.pos.x,
            t[1] - 8 + super->in.pos.y,
            k_w * 2, k_h * 2);

    u_pose_aa_set_left(&self->minus.rect.pose, l[0] + super->in.pos.x);
    u_pose_aa_set_top(&self->minus.rect.pose, t[0] + super->in.pos.y);

    u_pose_aa_set_left(&self->plus.rect.pose, l[2] + super->in.pos.x);
    u_pose_aa_set_top(&self->plus.rect.pose, t[2] + super->in.pos.y);

    // check long pressed
    if (self->pressed && self->long_press_time > 0) {
        self->long_press_time -= dtime;
        if (self->long_press_time <= 0) {
            if (self->pressed == 1) {
                log_info("tool kernel_minus long press");
                brush_load_kernel(0);
                animation_longpress(u_pose_get_xy(self->minus.rect.pose),
                                    R_COLOR_BLACK);
            } else if (self->pressed == 2) {
                log_info("tool kernel_plus long press");
                brush_load_kernel(brush.RO.max_kernels - 1);
                animation_longpress(u_pose_get_xy(self->plus.rect.pose),
                                    R_COLOR_WHITE);
            }
            self->pressed = 0;
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
    Impl *self = rhc_calloc(sizeof *self);

    self->kernel = ro_single_new(r_texture_new_invalid());
    self->kernel.owns_tex = false;
    self->minus = ro_single_new(r_texture_new_file(2, 1, "res/button_minus.png"));
    self->plus = ro_single_new(r_texture_new_file(2, 1, "res/button_plus.png"));
    self->minus.rect.pose = u_pose_new(0, 0, 16, 16);
    self->plus.rect.pose = u_pose_new(0, 0, 16, 16);

    snprintf(self->super.name, TOOL_NAME_LEN, "kernel");
    snprintf(self->super.tip, TOOL_TIP_LEN, "select a \nkernel / stamp");

    self->super.kill = kill_fn;
    self->super.update = update;
    self->super.render = render;
    self->super.pointer_event = pointer_event;

    return (Tool *) self;
}
