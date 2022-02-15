#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "tooltip.h"


#define BG_A "#776666"
#define BG_B "#887777"


Tooltip *tooltip_new() {
    Tooltip *self = rhc_calloc(sizeof *self);
    uColor_s buf[4];
    buf[0] = buf[3] = u_color_from_hex(BG_A);
    buf[1] = buf[2] = u_color_from_hex(BG_B);

    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    self->L.bg = ro_single_new(tex);
    self->L.bg_shadow = ro_single_new(tex);
    self->L.bg_shadow.owns_tex = false;
    self->L.bg_shadow.rect.color = (vec4){{0.2, 0.2, 0.2, 0.5}};
    
    self->L.title = ro_text_new_font55(16);
    ro_text_set_text(&self->L.title, "tooltip");
    ro_text_set_color(&self->L.title, (vec4){{0.2, 0.6, 0.2, 1}});
    
    self->L.title_shadow = ro_text_new_font55(16);
    ro_text_set_text(&self->L.title_shadow, "tooltip");
    ro_text_set_color(&self->L.title_shadow, (vec4){{0, 0, 0, 0.33}});
    
    self->L.name = ro_text_new_font55(TOOL_NAME_LEN);
    ro_text_set_color(&self->L.name, (vec4){{0.9, 0.9, 0.9, 1}});
    
    self->L.tip = ro_text_new_font55(TOOL_TIP_LEN);
    
    ro_text_set_color(&self->L.tip, (vec4){{0.8, 0.8, 0.8, 1}});
    
    self->L.title.pose = u_pose_new(-41, 58, 2, 2);
    self->L.title_shadow.pose = u_pose_new(-40, 57, 2, 2);
    
    self->L.name.pose = u_pose_new(-54, 42, 1, 2);
    self->L.tip.pose = u_pose_new(-58, 24, 1, 1);
    
    return self;
}

void tooltip_update(Tooltip *self, float dtime) {
    if(!self->active)
        return;
}

void tooltip_render(const Tooltip *self, const mat4 *cam_mat) {
    if(!self->active)
        return;
    ro_single_render(&self->L.bg_shadow, cam_mat);
    ro_single_render(&self->L.bg, cam_mat);
    ro_text_render(&self->L.title_shadow, cam_mat);
    ro_text_render(&self->L.title, cam_mat);
    ro_text_render(&self->L.name, cam_mat);
    ro_text_render(&self->L.tip, cam_mat);
}

bool tooltip_pointer_event(Tooltip *self, ePointer_s pointer) {
    if(!self->active)
        return false;
        
    assert(self->toolbar_ref);
    
    Tool *tool = toolbar_get_tool_by_pos(self->toolbar_ref, pointer.pos.xy);
    
    if(!tool)
        return true;
    
    if(strcmp(tool->name, "tooltip")==0)
        return false;
    
    tooltip_set(self, tool->name, tool->tip);
    
    return true;
}

void tooltip_set(Tooltip *self, const char *name, const char *tip) {
    ro_text_set_text(&self->L.name, name);
    vec2 size = ro_text_set_text(&self->L.tip, tip);
    
    float height = size.y + 40;
    
    self->L.bg.rect.pose = u_pose_new_aa(-60, 60, 120, height);
    u_pose_set_size(&self->L.bg.rect.uv, 60, height/2);
    self->L.bg_shadow.rect.pose = u_pose_new_aa(-58, 58, 120, height);
    self->L.bg_shadow.rect.uv = self->L.bg.rect.uv;
    
    self->active = true;
}

