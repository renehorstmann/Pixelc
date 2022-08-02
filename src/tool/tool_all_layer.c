#include "e/io.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/sca/int.h"
#include "feedback.h"
#include "u/button.h"
#include "canvas.h"
#include "cameractrl.h"
#include "dialog.h"
#include "tool.h"

#define SELECT_CURRENT 3

typedef struct {
    Tool super;
    RoSingle bg;
    RoSingle layer;
    RoText num;
    int pos;
    float long_press_time;
    int pressed;
} Select;

static void select_kill(Tool **super_ptr) {
   Select *self = (Select *) *super_ptr;
   if(!self)
       return;
   ro_single_kill(&self->bg);
   ro_single_kill(&self->layer);
   ro_text_kill(&self->num);
   s_free(self);
   *super_ptr = NULL;
}

static void select_pe(struct Tool *super, ePointer_s pointer) {
    Select *self = (Select *) super;
    
    uSprite sprite = canvas.RO.sprite;
    int layer = self->pos - SELECT_CURRENT + canvas.RO.current_layer;
    if(layer<0 || layer>=sprite.rows)
        return;
    
    if(!u_pose_aa_contains(self->bg.rect.pose, pointer.pos.xy)) {
        self->pressed = false;
        return;
    }
    
    if(pointer.action == E_POINTER_DOWN) {
        self->pressed = true;
        self->long_press_time = TOOL_LONG_PRESS_TIME;
    }
    
    if(self->pressed && pointer.action == E_POINTER_UP) {
        s_log("setting current layer to: %i", layer);
        self->pressed = false;
        canvas_reload();
        canvas_set_layer(layer);
    }
}

static void select_update(struct Tool *super, float dtime) {
    Select *self = (Select *) super;
    
    uSprite sprite = canvas.RO.sprite;
    int layer = self->pos - SELECT_CURRENT + canvas.RO.current_layer;
    if(layer<0 || layer>=sprite.rows) {
        // empty
        self->bg.rect.color.a = 0;
        self->layer.rect.color.a = 0;
        ro_text_set_text(&self->num, "");
    } else {
        self->bg.rect.color.a = self->pos==SELECT_CURRENT? 0.5 : 0.25;
        self->layer.rect.color.a = 1;

        self->layer.rect.sprite.x = canvas.RO.current_frame;
        self->layer.rect.sprite.y = layer;
        
        char num[4];
        const char *format;
        if(self->pos==0 && layer>0)
            format = "+%2i";
        else if(self->pos==TOOL_LAYER_SELECT_NUM-1 && layer<canvas.RO.image.layers-1)
            format = "%2i+";
        else 
            format = " %2i";
        snprintf(num, sizeof num, format, layer+1);
        ro_text_set_text(&self->num, num);
    }
    
    float x = 10+super->in.pos.x;
    float y = -10+super->in.pos.y;
    
    float width = 16;
    float height = 16;
    
    self->bg.rect.pose = u_pose_new(x, y, width+2, height+2);

    ivec2 size = canvas_get_size();
    if(size.x > size.y) {
        height = height * size.y / size.x;
    } else if(size.x < size.y) {
        width = width * size.x / size.y;
    }
    
    self->layer.rect.pose = u_pose_new(x, y, width, height);
    
    u_pose_set_xy(&self->num.pose, x-8, y-4);
            
    // longpress
    if(self->pressed && self->long_press_time>0) {
        self->long_press_time -= dtime;
        if(self->long_press_time<=0) {
            self->pressed = false;
            s_log("layer longpress: %i", layer);
            feedback_longpress(u_pose_get_xy(self->bg.rect.pose), (vec4) {{0.8, 0.2, 0.2, 1.0}});
            canvas_reload();
            canvas_set_layer(layer);
            dialog_create_layer();
        }
    }
}

static void select_render(const struct Tool *super, const mat4 *cam_mat) {
    Select *self = (Select *) super;
    ro_single_render(&self->bg, cam_mat);

    ro_single_set_texture(&self->layer, canvas.RO.tex);
    ro_single_render(&self->layer, cam_mat);

    ro_text_render(&self->num, cam_mat);
}


Tool *tool_new_layer_select(int pos) {
    assert(pos>=0 && pos<TOOL_LAYER_SELECT_NUM);
    Select *self = s_new0(Select, 1);
    
    self->super.size = (vec2) {{20, 20}};
    
    self->pos = pos;
    
    self->bg = ro_single_new(r_texture_new_white_pixel());
    self->bg.rect.color.rgb = pos==SELECT_CURRENT?
            (vec3) {{0.8, 0.8, 0.8}}
            : (vec3) {{0.2, 0.2, 0.2}};
    
    self->layer = ro_single_new(canvas.RO.tex);
    self->layer.owns_tex = false;
    
    self->num = ro_text_new_font55(4);
    ro_text_set_color(&self->num, pos==SELECT_CURRENT? 
            (vec4) {{0.2, 0.2, 0.8, 1}}
            : (vec4) {{0.2, 0.2, 0.2, 1}});
    
    snprintf(self->super.name, TOOL_NAME_LEN, "layer"); 
    snprintf(self->super.tip, TOOL_TIP_LEN, "Select a\n"
            "canvas layer\n\n"
            "Long press for\n"
            "layer options"); 
    
    self->super.kill = select_kill; 
    self->super.update = select_update; 
    self->super.render = select_render; 
    self->super.pointer_event = select_pe; 
    
    return (Tool *) self;
}


static void blend_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    
    if(pointer.action != E_POINTER_DOWN)
        return;
     
    if(u_pose_aa_contains(self->ro.rect.pose, pointer.pos.xy)) {
        switch(canvas.blend_mode) {
        case CANVAS_BLEND_LAYER_ONION:
            canvas.blend_mode = CANVAS_BLEND_LAYER_FULL;
            break;
        case CANVAS_BLEND_LAYER_FULL:
            canvas.blend_mode = CANVAS_BLEND_NONE;
            break;
        default:
            canvas.blend_mode = CANVAS_BLEND_LAYER_ONION;
        }
        s_log("canvas blend mode: %i", canvas.blend_mode);
    }
}

static bool blend_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    switch(canvas.blend_mode) {
    case CANVAS_BLEND_LAYER_ONION:
        self->ro.rect.sprite.x = 1;
        break;
    case CANVAS_BLEND_LAYER_FULL:
        self->ro.rect.sprite.x = 2;
        break;
    default:
        self->ro.rect.sprite.x = 0;
    }
    // always active
    return true;
}

Tool *tool_new_layer_blend() {
    Tool *super = tool_button_new("blend",
                           "Blends in the\n"
                           "previous layers\n"
                           "with or without\n"
                           "onion skinning",
                           "res/button_blend3.png",
                           blend_pe,
                           blend_is_a);
    ToolButton *self = (ToolButton*) super;
    // button with 3 instead of 2 modes
    //     so reload
    ro_single_set_texture(&self->ro, r_texture_new_file(3, 1, "res/button_blend3.png"));
    super->size = vec2_cast_from_int(self->ro.tex.sprite_size.v);
    u_pose_set_size(&self->ro.rect.pose, 
            super->size.x, super->size.y);
    return super;
}


static void add_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;

    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool layer add");
        int layer = canvas.RO.current_layer;
        uSprite old = canvas_get_sprite();
        uSprite sprite = u_sprite_new_clone_insert_row(old, layer);
        u_sprite_kill(&old);
        canvas_set_sprite(sprite, true);
        canvas_set_layer(layer+1);
    }
}

static bool add_is_a(struct Tool *super, float dtime) {
    return canvas.RO.image.layers < CANVAS_MAX_LAYERS;
}

Tool *tool_new_layer_add() {
    return tool_button_new("add",
                           "Adds a layer\n"
                           "next to the\n"
                           "current layer",
                           "res/button_plus.png",
                           add_pe,
                           add_is_a);
}
