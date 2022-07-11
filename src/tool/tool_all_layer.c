#include "e/io.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/sca/int.h"
#include "animation.h"
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
    
    uImage img = canvas.RO.image;
    int layer = self->pos - SELECT_CURRENT + canvas.current_layer;
    if(layer<0 || layer>=img.layers)
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
        canvas.current_layer = layer;
        cameractrl_set_home();
    }
}

static void select_update(struct Tool *super, float dtime) {
    Select *self = (Select *) super;
    
    uImage img = canvas.RO.image;
    int layer = self->pos - SELECT_CURRENT + canvas.current_layer;
    if(layer<0 || layer>=img.layers) {
        // empty
        self->bg.rect.color.a = 0;
        self->layer.rect.color.a = 0;
        ro_text_set_text(&self->num, "");
    } else {
        self->bg.rect.color.a = self->pos==SELECT_CURRENT? 0.5 : 0.25;
        self->layer.rect.color.a = 1;
        
        rTexture tex = r_texture_new(img.cols, img.rows, 1, 1, u_image_layer(img, layer));
        ro_single_set_texture(&self->layer, tex);
        
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
    
    if(img.cols > img.rows) {
        height = height * img.rows / img.cols;
    } else if(img.cols < img.rows) {
        width = width * img.cols / img.rows;
    }
    
    self->layer.rect.pose = u_pose_new(x, y, width, height);
    
    u_pose_set_xy(&self->num.pose, x-8, y-4);
            
    // longpress
    if(self->pressed && self->long_press_time>0) {
        self->long_press_time -= dtime;
        if(self->long_press_time<=0) {
            self->pressed = false;
            s_log("layer longpress: %i", layer);
            animation_longpress(u_pose_get_xy(self->bg.rect.pose), R_COLOR_BLACK);
            canvas.current_layer = layer;
            dialog_create_layer();
        }
    }
}

static void select_render(const struct Tool *super, const mat4 *cam_mat) {
    Select *self = (Select *) super;
    ro_single_render(&self->bg, cam_mat);
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
    
    self->layer = ro_single_new(r_texture_new_white_pixel());
    
    self->num = ro_text_new_font55(4);
    ro_text_set_color(&self->num, pos==SELECT_CURRENT? 
            (vec4) {{0.2, 0.2, 0.8, 1}}
            : (vec4) {{0.2, 0.2, 0.2, 1}});
    
    snprintf(self->super.name, TOOL_NAME_LEN, "layer"); 
    snprintf(self->super.tip, TOOL_TIP_LEN, "select a\n"
            "canvas layer\n\n"
            "long press for\n"
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
        canvas.blend_layers++;
        canvas.blend_layers %= CANVAS_LAYER_BLEND_NUM_MODES;
        s_log("canvas layer blend mode: %i", canvas.blend_layers);
    }
}

static bool blend_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    self->ro.rect.sprite.x = canvas.blend_layers;
    // always active
    return true;
}

Tool *tool_new_layer_blend() {
    Tool *super = tool_button_new("blend",
                           "blends in the\n"
                           "previous layers\n"
                           "with or without\n"
                           "onion skinning",
                           "res/button_blend.png",
                           blend_pe,
                           blend_is_a);
    ToolButton *self = (ToolButton*) super;
    // button with 3 instead of 2 modes
    //     so reload
    ro_single_set_texture(&self->ro, r_texture_new_file(3, 1, "res/button_blend.png"));
    super->size = vec2_cast_from_int(self->ro.tex.sprite_size.v);
    u_pose_set_size(&self->ro.rect.pose, 
            super->size.x, super->size.y);
    return super;
}


static void add_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;

    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool layer add");
        int layer = canvas.current_layer;
        uImage old = canvas.RO.image;
        uImage img = u_image_new_empty(old.cols, old.rows, old.layers + 1);

        // copy until current layer
        memcpy(img.data, old.data, u_image_layer_data_size(img) * (layer + 1));

        // set next (new) layer to 0
        memset(u_image_layer(img, layer + 1), 0,
               u_image_layer_data_size(img));

        // copy tail
        if (layer < old.layers - 1) {
            memcpy(u_image_layer(img, layer + 2),
                   u_image_layer(old, layer + 1),
                   u_image_layer_data_size(img)
                   * (old.layers - layer - 1)
            );
        }

        canvas.current_layer++;
        canvas_set_image(img, true);
    }
}

static bool add_is_a(struct Tool *super, float dtime) {
    return canvas.RO.image.layers < CANVAS_MAX_LAYERS;
}

Tool *tool_new_layer_add() {
    return tool_button_new("add",
                           "adds a layer\n"
                           "next to the\n"
                           "current layer",
                           "res/button_plus.png",
                           add_pe,
                           add_is_a);
}
