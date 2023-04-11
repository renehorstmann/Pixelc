#include "u/pose.h"
#include "m/float.h"
#include "u/button.h"
#include "brush.h"
#include "palette.h"
#include "feedback.h"
#include "tool.h"
#include "tile.h"

//
// private
//


typedef struct {
    Tool super;
    RoSingle bg;
    RoSingle color_drop;
    RoSingle tile;
    vec4 padding_lrbt; // left, right, bottom, top
    float long_press_time;
    bool pressed;
} Impl;


static void kill_fn(Tool **super_ptr) {
    Impl *self = (Impl *) *super_ptr;
    if (!self)
        return;
    ro_single_kill(&self->bg);
    ro_single_kill(&self->color_drop);
    ro_single_kill(&self->tile);
    s_free(self);
    *super_ptr = NULL;
}

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    Impl *self = (Impl *) super;
    if (!u_pose_aa_contains(self->color_drop.rect.pose, pointer.pos.xy)) {
        self->pressed = false;
        return;
    }
    if (pointer.action == E_POINTER_DOWN) {
        self->long_press_time = TOOL_LONG_PRESS_TIME;
        self->pressed = true;
    } else if (pointer.action == E_POINTER_UP) {
        if (self->long_press_time > 0 && self->pressed) {
            s_log("tool secondary_color: active");
            brush.secondary_as_current = true;
        }
        self->pressed = false;
    }
}

static void update(struct Tool *super, float dtime) {
    Impl *self = (Impl *) super;
    self->color_drop.rect.color = u_color_to_vec4(brush.secondary_color);

    u_pose_aa_set_left(&self->bg.rect.pose, super->in.pos.x + self->padding_lrbt.v0);
    u_pose_aa_set_top(&self->bg.rect.pose, super->in.pos.y - self->padding_lrbt.v3);
    self->color_drop.rect.pose = self->bg.rect.pose;
    self->tile.rect.pose = self->bg.rect.pose;

    super->size.x = self->bg.tex.sprite_size.x + self->padding_lrbt.v0 + self->padding_lrbt.v1;
    super->size.y = self->bg.tex.sprite_size.y + self->padding_lrbt.v2 + self->padding_lrbt.v3;

    // check tipped / secondary active
    if (brush.secondary_as_current) {
        palette_set_custom_select(self->color_drop.rect.pose);
        brush.current_color = brush.secondary_color;
    }

    // long press
    if (self->pressed && self->long_press_time > 0) {
        self->long_press_time -= dtime;
        if (self->long_press_time <= 0) {
            s_log("tool secondary_color: set");
            brush.secondary_color = brush.current_color;
            vec4 col = u_color_to_vec4(brush.current_color);
            col.a = 1;
            feedback_longpress(u_pose_get_xy(self->color_drop.rect.pose),
                                col);
        }
    }

    self->bg.rect.color.a = 1;
    if(tile.active && tile.canvas_active) {
        bool found = tile_get_tile_from_colorcode(&self->tile.tex, &self->tile.rect, brush.secondary_color);
        if(found) {
            self->bg.rect.color.a = 0;
        }
    }
}

static void render(const struct Tool *super, const mat4 *cam_mat) {
    const Impl *self = (const Impl *) super;
    ro_single_render(&self->bg, cam_mat);
    if(tile.active && tile.canvas_active) {
        ro_single_render(&self->tile, cam_mat);
    } else {
        ro_single_render(&self->color_drop, cam_mat);
    }
}

//
// public
//

Tool *tool_new_secondary_color() {
    Impl *self = s_malloc0(sizeof *self);

    self->bg = ro_single_new(r_texture_new_file(1, 1, "res/toolbar_color_bg.png"));
    self->color_drop = ro_single_new(r_texture_new_file(1, 1, "res/color_drop.png"));
    self->bg.rect.pose = u_pose_new(0, 0,
                                    self->bg.tex.sprite_size.x,
                                    self->bg.tex.sprite_size.y
    );
    self->color_drop.rect.pose = self->bg.rect.pose;

    // borrows tex from tile module
    self->tile = ro_single_new(r_texture_new_invalid());
    self->tile.owns_tex = false;
    self->tile.rect.pose = self->bg.rect.pose;

    snprintf(self->super.name, TOOL_NAME_LEN, "secondary color");
    snprintf(self->super.tip, TOOL_TIP_LEN, "Tip to use\n\nHold to set");

    self->super.size = vec2_cast_from_int(self->bg.tex.sprite_size.v);

    self->super.kill = kill_fn;
    self->super.update = update;
    self->super.render = render;
    self->super.pointer_event = pointer_event;

    self->padding_lrbt = vec4_set(1);

    return (Tool *) self;
}
