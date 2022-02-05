#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "button.h"
#include "tool.h"

static void tool_button_kill(Tool **super_ptr) {
    ToolButton *self = (ToolButton*) *super_ptr;
    if(!self)
        return;
    ro_single_kill(&self->ro);
    rhc_free(self);
    *super_ptr = NULL;
}

static void tool_button_update(Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    
    self->ro.rect.pose = u_pose_new_aa(
            super->in.pos.x + self->padding_lrbt.v0,
            super->in.pos.y - self->padding_lrbt.v3,
            self->ro.tex.sprite_size.x,
            self->ro.tex.sprite_size.y
            );
            
    super->size.x = self->ro.tex.sprite_size.x + self->padding_lrbt.v0 + self->padding_lrbt.v1;
    super->size.y = self->ro.tex.sprite_size.y + self->padding_lrbt.v2 + self->padding_lrbt.v3;
    
    if(self->opt_is_active) {
        bool active = self->opt_is_active(super, dtime, refs);
        if(active && !self->active)
            self->ro.rect.sprite.x = 0;
        self->active = active;
    }
    
    if(!self->active)
        self->ro.rect.sprite.x = 1;
}

static void tool_button_render(const struct Tool *super, const mat4 *cam_mat) {
    puts("hej");
    ToolButton *self = (ToolButton*) super;
    
    ro_single_render(&self->ro, cam_mat);
}

static rRect_s *tool_button_get_rect(Tool *super) {
    ToolButton *self = (ToolButton*) super;
    return &self->ro.rect;
}

Tool *tool_button_new(const char *name, 
        const char *tip, 
        const char *tex_file, 
        tool_pointer_event_fun pointer_event,
        tool_button_active opt_is_active) {
    ToolButton *self = rhc_calloc(sizeof *self);
    
    self->ro = ro_single_new(r_texture_new_file(2, 1, tex_file));
    
    snprintf(self->super.name, TOOL_NAME_LEN, "%s", name);
    snprintf(self->super.tip, TOOL_TIP_LEN, "%s", tip);
    
    self->super.size = vec2_cast_from_int(self->ro.tex.sprite_size.v);
    
    self->super.kill = tool_button_kill;
    self->super.update = tool_button_update;
    self->super.render = tool_button_render;
    
    self->super.pointer_event = pointer_event;
    
    self->opt_is_active = opt_is_active;
 
    self->padding_lrbt = vec4_set(1);
        
    return (Tool*) self;
}


//
// tool list
//  

static void tool_undo_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(self->active && button_clicked(&self->ro.rect, pointer)) {
        canvas_undo(refs.canvas);
    } 
}
static bool tool_undo_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    return canvas_undo_available(refs.canvas);
}      
Tool *tool_new_undo() {
    return tool_button_new("undo", 
            "undos the last canvas changes", 
            "res/button_undo.png", 
            tool_undo_pe,
            tool_undo_is_a);
}



static void tool_redo_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(self->active && button_clicked(&self->ro.rect, pointer)) {
        canvas_redo(refs.canvas);
    } 
}
static bool tool_redo_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    return canvas_redo_available(refs.canvas);
}      
Tool *tool_new_redo() {
    return tool_button_new("redo", 
            "redos the undone canvas changes", 
            "res/button_undo.png", 
            tool_redo_pe,
            tool_redo_is_a);
}

