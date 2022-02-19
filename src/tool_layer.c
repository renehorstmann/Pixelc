#include "e/io.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "button.h"
#include "tool.h"




typedef struct {
    Tool super;
    RoText layer;
    RoSingle prev, next;
    int last_layer_id;
    float long_press_time;
    int pressed;
} Select;


static void select_kill(Tool **super_ptr) {
    Select *self = (Select*) *super_ptr;
    if(!self)
        return;
    ro_text_kill(&self->layer);
    ro_single_kill(&self->prev);
    ro_single_kill(&self->next);
    rhc_free(self);
    *super_ptr = NULL;
}
static void select_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    Select *self = (Select*) super;
    int id = refs.canvas->current_layer;
    if(button_clicked(&self->prev.rect, pointer)
            && id>0) {
        
        log_info("tool layer_prev: %i", id-1);
        refs.canvas->current_layer = id-1;
    }
    if(button_clicked(&self->next.rect, pointer)
            && id<refs.canvas->RO.image.layers-1) {
        
        log_info("tool layer_next: %i", id+1);
        refs.canvas->current_layer = id+1;
    }
    
    // long press
    if(u_pose_aa_contains(self->prev.rect.pose, pointer.pos.xy)) {
        if(pointer.action == E_POINTER_DOWN) {
            self->pressed = 1;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if(self->pressed != 1)
            self->pressed = 0;
    } else if(u_pose_aa_contains(self->next.rect.pose, pointer.pos.xy)){
        if(pointer.action == E_POINTER_DOWN) {
            self->pressed = 2;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if(self->pressed != 2)
            self->pressed = 0;
    } else {
        self->pressed = 0;
    }
    if(pointer.action == E_POINTER_UP)
        self->pressed = 0;
}
static void select_update(struct Tool *super, float dtime, ToolRefs refs) {
    Select *self = (Select*) super;
    
    int id = refs.canvas->current_layer;
    if(self->last_layer_id == 0 && id>0)
        button_set_pressed(&self->prev.rect, false);
    if(self->last_layer_id == refs.canvas->RO.image.layers-1 && id<self->last_layer_id)
        button_set_pressed(&self->next.rect, false);
    self->last_layer_id = id;
        
    if(id==0)
        button_set_pressed(&self->prev.rect, true);
    if(id==refs.canvas->RO.image.layers-1)
        button_set_pressed(&self->next.rect, true);
    
    // todo
    char layer_num[3];
    snprintf(layer_num, sizeof layer_num, "%i", refs.canvas->current_layer);
    ro_text_set_text(&self->layer, layer_num);
    
    int l_x_offset = refs.canvas->current_layer<10? 3 : 0;

    if(camera_is_portrait_mode(refs.cam)) {
        self->layer.pose = u_pose_new(
                18 + l_x_offset + super->in.pos.x,
                -8 + super->in.pos.y,
                1, 1);
        u_pose_aa_set_left(&self->prev.rect.pose, 
                1 + super->in.pos.x);
        u_pose_aa_set_top(&self->prev.rect.pose, 
                -1 + super->in.pos.y);
            
        u_pose_aa_set_left(&self->next.rect.pose,
                30 + super->in.pos.x);
        u_pose_aa_set_top(&self->next.rect.pose,
                -1 + super->in.pos.y);
                
        super->size = (vec2) {{47, 18}};
    } else {
        self->layer.pose = u_pose_new(
                3 + l_x_offset + super->in.pos.x,
                -18 + super->in.pos.y,
                1, 1);
        u_pose_aa_set_left(&self->prev.rect.pose, 
                1 + super->in.pos.x);
        u_pose_aa_set_top(&self->prev.rect.pose, 
                -1 + super->in.pos.y);
            
        u_pose_aa_set_left(&self->next.rect.pose,
                1 + super->in.pos.x);
        u_pose_aa_set_top(&self->next.rect.pose,
                -24 + super->in.pos.y);
                
        super->size = (vec2) {{18, 41}};
    }
    
    // check long pressed
    if(self->pressed && self->long_press_time>0) {
        self->long_press_time -= dtime;
        if(self->long_press_time <= 0) {
            if(self->pressed == 1) {
                log_info("tool layer_prev long press");
                refs.canvas->current_layer = 0;
                animation_longpress(refs.animation,
                        u_pose_get_xy(self->prev.rect.pose), 
                        R_COLOR_BLACK);
            } else if(self->pressed == 2) {
                log_info("tool layer_next long press");
                refs.canvas->current_layer = refs.canvas->RO.image.layers-1;
                animation_longpress(refs.animation, 
                        u_pose_get_xy(self->next.rect.pose), 
                        R_COLOR_WHITE);
            }
            self->pressed = 0;
        }
    }
}
static void select_render(const struct Tool *super, const mat4 *cam_mat) {
    const Select *self = (const Select*) super;
    ro_text_render(&self->layer, cam_mat);
    ro_single_render(&self->prev, cam_mat);
    ro_single_render(&self->next, cam_mat);
}
Tool *tool_new_layer_select() {
    Select *self = rhc_calloc(sizeof *self);

    self->layer = ro_text_new_font55(2);
    self->prev = ro_single_new(r_texture_new_file(2, 1, "res/button_prev.png"));
    self->next = ro_single_new(r_texture_new_file(2, 1, "res/button_next.png"));
    self->prev.rect.pose = u_pose_new(0, 0, 16, 16);
    self->next.rect.pose = u_pose_new(0, 0, 16, 16);
    
    snprintf(self->super.name, TOOL_NAME_LEN, "layer");
    snprintf(self->super.tip, TOOL_TIP_LEN, "select a\ncanvas layer");

    self->super.kill = select_kill;
    self->super.update = select_update;
    self->super.render = select_render;
    self->super.pointer_event = select_pe;

    return (Tool*) self;
}

