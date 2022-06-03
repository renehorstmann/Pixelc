#include "e/io.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "animation.h"
#include "button.h"
#include "toolbar.h"
#include "canvas.h"
#include "brush.h"
#include "cameractrl.h"
#include "dialog.h"
#include "camera.h"
#include "palette.h"
#include "tool.h"

static void tool_button_kill(Tool **super_ptr) {
    ToolButton *self = (ToolButton *) *super_ptr;
    if (!self)
        return;
    ro_single_kill(&self->ro);
    rhc_free(self);
    *super_ptr = NULL;
}

static void tool_button_update(Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;

    u_pose_aa_set_left(&self->ro.rect.pose, super->in.pos.x + self->padding_lrbt.v0);
    u_pose_aa_set_top(&self->ro.rect.pose, super->in.pos.y - self->padding_lrbt.v3);

    super->size.x = self->ro.tex.sprite_size.x + self->padding_lrbt.v0 + self->padding_lrbt.v1;
    super->size.y = self->ro.tex.sprite_size.y + self->padding_lrbt.v2 + self->padding_lrbt.v3;

    if (self->opt_is_active) {
        bool active = self->opt_is_active(super, dtime);
        if (active && !self->active)
            self->ro.rect.sprite.x = 0;
        self->active = active;
    }

    if (!self->active)
        self->ro.rect.sprite.x = 1;
}

static void tool_button_render(const struct Tool *super, const mat4 *cam_mat) {
    ToolButton *self = (ToolButton *) super;
    ro_single_render(&self->ro, cam_mat);
}

static rRect_s *tool_button_get_rect(Tool *super) {
    ToolButton *self = (ToolButton *) super;
    return &self->ro.rect;
}

Tool *tool_button_new(const char *name,
                      const char *tip,
                      const char *tex_file,
                      tool_pointer_event_fun pointer_event,
                      tool_button_active opt_is_active) {
    ToolButton *self = rhc_calloc(sizeof *self);

    self->ro = ro_single_new(r_texture_new_file(2, 1, tex_file));
    self->ro.rect.pose = u_pose_new(0, 0,
                                    self->ro.tex.sprite_size.x,
                                    self->ro.tex.sprite_size.y
    );

    snprintf(self->super.name, TOOL_NAME_LEN, "%s", name);
    snprintf(self->super.tip, TOOL_TIP_LEN, "%s", tip);

    self->super.size = vec2_cast_from_int(self->ro.tex.sprite_size.v);

    self->super.kill = tool_button_kill;
    self->super.update = tool_button_update;
    self->super.render = tool_button_render;

    self->super.pointer_event = pointer_event;

    self->active = true;
    self->opt_is_active = opt_is_active;

    self->padding_lrbt = vec4_set(1);

    return (Tool *) self;
}
