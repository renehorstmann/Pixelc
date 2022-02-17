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
    
    u_pose_aa_set_left(&self->ro.rect.pose,super->in.pos.x + self->padding_lrbt.v0);
    u_pose_aa_set_top(&self->ro.rect.pose,super->in.pos.y - self->padding_lrbt.v3);
            
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
        
    return (Tool*) self;
}




//
// tool list
//  


static void tool_tooltip_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(!button_toggled(&self->ro.rect, pointer))
        return;
    
    // only passed if button state toggled
    bool pressed = button_is_pressed(&self->ro.rect);
    if(pressed) {
        log_info("tool tooltip start");
        dialog_create_tooltip(refs.dialog, refs.toolbar);
    } else {
        log_info("tool tooltip stop");
        dialog_hide(refs.dialog);
    }
    
}
static bool tool_tooltip_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    bool tooltip = strcmp(refs.dialog->id, "tooltip") == 0;
    button_set_pressed(&self->ro.rect, tooltip);
    // always active
    return true;
}      
Tool *tool_new_tooltip() {
    return tool_button_new("tooltip", 
            "click on a tool\nto get its tip", 
            "res/button_tooltip.png", 
            tool_tooltip_pe,
            tool_tooltip_is_a);
}


static void tool_clear_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(self->active && button_clicked(&self->ro.rect, pointer)) {
        log_info("tool clear");
        brush_clear(refs.brush);
    } 
}
Tool *tool_new_clear() {
    return tool_button_new("clear", 
            "resets the canvas\nor selection\nto transparent", 
            "res/button_clear.png", 
            tool_clear_pe,
            NULL);
}


static void tool_undo_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(self->active && button_clicked(&self->ro.rect, pointer)) {
        log_info("tool undo");
        canvas_undo(refs.canvas);
    } 
}
static bool tool_undo_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    return canvas_undo_available(refs.canvas);
}      
Tool *tool_new_undo() {
    return tool_button_new("undo", 
            "undos the last\ncanvas changes", 
            "res/button_undo.png", 
            tool_undo_pe,
            tool_undo_is_a);
}



static void tool_redo_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(self->active && button_clicked(&self->ro.rect, pointer)) {
        log_info("tool redo");
        canvas_redo(refs.canvas);
    } 
}
static bool tool_redo_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    return canvas_redo_available(refs.canvas);
}      
Tool *tool_new_redo() {
    return tool_button_new("redo", 
            "redos the undone\ncanvas changes", 
            "res/button_redo.png", 
            tool_redo_pe,
            tool_redo_is_a);
}

static void tool_import_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(self->active && button_clicked(&self->ro.rect, pointer)) {
        uImage img = u_image_new_file(1, "import.png");
        if(!u_image_valid(img))
            return;
        log_info("tool import");
        selectionctrl_paste_image(refs.selectionctrl, img);
        u_image_kill(&img);
    } 
}
Tool *tool_new_import() {
    return tool_button_new("import", 
            "loads import.png\nas selection", 
            "res/button_import.png", 
            tool_import_pe,
            NULL);
}

static void tool_selection_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(!button_toggled(&self->ro.rect, pointer))
        return;
    
    // only passed if button state toggled
    bool pressed = button_is_pressed(&self->ro.rect);
    if(pressed) {
        log_info("tool selection: start");
        selectionctrl_acquire(refs.selectionctrl);
    }else {
        log_info("tool selection: stop");
        selectionctrl_stop(refs.selectionctrl);
        canvas_reload(refs.canvas);
    }
    
}
static bool tool_selection_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.selectionctrl->mode != SELECTIONCTRL_NONE);
    // always active
    return true;
}      
Tool *tool_new_selection() {
    return tool_button_new("selection", 
            "toggle a\ncanvas selection", 
            "res/button_selection.png", 
            tool_selection_pe,
            tool_selection_is_a);
}

typedef struct {
    Tool super;
    RoSingle kernel;
    RoSingle minus, plus;
    int last_kernel_id;
    float long_press_time;
    int pressed;
} ToolKernel;


static void tool_kernel_kill(Tool **super_ptr) {
    ToolKernel *self = (ToolKernel*) *super_ptr;
    if(!self)
        return;
    ro_single_kill(&self->kernel);
    ro_single_kill(&self->minus);
    ro_single_kill(&self->plus);
    rhc_free(self);
    *super_ptr = NULL;
}
static void tool_kernel_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolKernel *self = (ToolKernel*) super;
    int id = refs.brush->RO.kernel_id;
    if(button_clicked(&self->minus.rect, pointer)
            && id>0) {
        
        log_info("tool kernel_minus: %i", id-1);
        brush_load_kernel(refs.brush, id-1);
    }
    if(button_clicked(&self->plus.rect, pointer)
            && id<refs.brush->RO.max_kernels-1) {
        
        log_info("tool kernel_plus: %i", id+1);
        brush_load_kernel(refs.brush, id+1);
    }
    
    // long press
    if(u_pose_aa_contains(self->minus.rect.pose, pointer.pos.xy)) {
        if(pointer.action == E_POINTER_DOWN) {
            self->pressed = 1;
            self->long_press_time = TOOL_LONG_PRESS_TIME;
        }
        if(self->pressed != 1)
            self->pressed = 0;
    } else if(u_pose_aa_contains(self->plus.rect.pose, pointer.pos.xy)){
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
static void tool_kernel_update(struct Tool *super, float dtime, ToolRefs refs) {
    ToolKernel *self = (ToolKernel*) super;
    
    int id = refs.brush->RO.kernel_id;
    if(self->last_kernel_id == 0 && id>0)
        button_set_pressed(&self->minus.rect, false);
    if(self->last_kernel_id == refs.brush->RO.max_kernels-1 && id<self->last_kernel_id)
        button_set_pressed(&self->plus.rect, false);
    self->last_kernel_id = id;
        
    if(id==0)
        button_set_pressed(&self->minus.rect, true);
    if(id==refs.brush->RO.max_kernels-1)
        button_set_pressed(&self->plus.rect, true);
    
    self->kernel.tex = refs.brush->RO.kernel_tex;
    
    float l[3];
    float t[3];
    if(camera_is_portrait_mode(refs.cam)) {
        for(int i=0; i<3; i++) {
            l[i] = 1 + i*17;
            t[i] = -1;
        }
        super->size = (vec2) {{16*3+4, 18}};
    } else {
        for(int i=0; i<3; i++) {
            l[i] = 1;
            t[i] = -1 - i*17;
        }
        super->size = (vec2) {{18, 16*3+4}};
    }
       
    int k_w = refs.brush->RO.kernel.cols;
    int k_h = refs.brush->RO.kernel.rows;
    k_w = isca_min(k_w, 8);
    k_h = isca_min(k_h, 8);
    self->kernel.rect.pose = u_pose_new(
            l[1] + 8 + super->in.pos.x,
            t[1] - 8 + super->in.pos.y,
            k_w*2, k_h*2);
    
    u_pose_aa_set_left(&self->minus.rect.pose, l[0] + super->in.pos.x);
    u_pose_aa_set_top(&self->minus.rect.pose, t[0] + super->in.pos.y);
            
    u_pose_aa_set_left(&self->plus.rect.pose, l[2] + super->in.pos.x);
    u_pose_aa_set_top(&self->plus.rect.pose, t[2] + super->in.pos.y);
    
    // check long pressed
    if(self->pressed && self->long_press_time>0) {
        self->long_press_time -= dtime;
        if(self->long_press_time <= 0) {
            if(self->pressed == 1) {
                log_info("tool kernel_minus long press");
                brush_load_kernel(refs.brush, 0);
                animation_longpress(refs.animation,
                        u_pose_get_xy(self->minus.rect.pose), 
                        R_COLOR_BLACK);
            } else if(self->pressed == 2) {
                log_info("tool kernel_plus long press");
                brush_load_kernel(refs.brush, refs.brush->RO.max_kernels-1);
                animation_longpress(refs.animation, 
                        u_pose_get_xy(self->plus.rect.pose), 
                        R_COLOR_WHITE);
            }
            self->pressed = 0;
        }
    }
}
static void tool_kernel_render(const struct Tool *super, const mat4 *cam_mat) {
    const ToolKernel *self = (const ToolKernel*) super;
    ro_single_render(&self->kernel, cam_mat);
    ro_single_render(&self->minus, cam_mat);
    ro_single_render(&self->plus, cam_mat);
}
Tool *tool_new_kernel() {
    ToolKernel *self = rhc_calloc(sizeof *self);

    self->kernel = ro_single_new(r_texture_new_invalid());
    self->kernel.owns_tex = false;
    self->minus = ro_single_new(r_texture_new_file(2, 1, "res/button_minus.png"));
    self->plus = ro_single_new(r_texture_new_file(2, 1, "res/button_plus.png"));
    self->minus.rect.pose = u_pose_new(0, 0, 16, 16);
    self->plus.rect.pose = u_pose_new(0, 0, 16, 16);
    
    snprintf(self->super.name, TOOL_NAME_LEN, "kernel");
    snprintf(self->super.tip, TOOL_TIP_LEN, "select a \nkernel / stamp");

    self->super.kill = tool_kernel_kill;
    self->super.update = tool_kernel_update;
    self->super.render = tool_kernel_render;
    self->super.pointer_event = tool_kernel_pe;

    return (Tool*) self;
}


typedef struct {
    Tool super;
    RoSingle bg;
    RoSingle color_drop;
    vec4 padding_lrbt; // left, right, bottom, top
    float long_press_time;
    bool pressed;
} ToolSecondaryColor;


static void tool_secondary_color_kill(Tool **super_ptr) {
    ToolSecondaryColor *self = (ToolSecondaryColor*) *super_ptr;
    if(!self)
        return;
    ro_single_kill(&self->bg);
    ro_single_kill(&self->color_drop);
    rhc_free(self);
    *super_ptr = NULL;
}
static void tool_secondary_color_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolSecondaryColor *self = (ToolSecondaryColor*) super;
    if(!u_pose_aa_contains(self->color_drop.rect.pose, pointer.pos.xy)) {
        self->pressed = false;
        return;
    }
    if(pointer.action == E_POINTER_DOWN) {
        self->long_press_time = TOOL_LONG_PRESS_TIME;
        self->pressed = true;
    } else if(pointer.action == E_POINTER_UP) {
        if(self->long_press_time>0 && self->pressed) {
            log_info("tool secondary_color: active");
            refs.brush->secondary_as_current = true;
        }
    }
}
static void tool_secondary_color_update(struct Tool *super, float dtime, ToolRefs refs) {
    ToolSecondaryColor *self = (ToolSecondaryColor*) super;
    self->color_drop.rect.color = u_color_to_vec4(refs.brush->secondary_color);

    u_pose_aa_set_left(&self->bg.rect.pose,super->in.pos.x + self->padding_lrbt.v0);
    u_pose_aa_set_top(&self->bg.rect.pose,super->in.pos.y - self->padding_lrbt.v3);
    self->color_drop.rect.pose = self->bg.rect.pose;

    super->size.x = self->bg.tex.sprite_size.x + self->padding_lrbt.v0 + self->padding_lrbt.v1;
    super->size.y = self->bg.tex.sprite_size.y + self->padding_lrbt.v2 + self->padding_lrbt.v3;

    // check tipped / secondary active
    if(refs.brush->secondary_as_current) {
        palette_set_custom_select(refs.palette, self->color_drop.rect.pose);
        refs.brush->current_color = refs.brush->secondary_color;
    }

    // long press
    if (self->pressed && self->long_press_time>0) {
        self->long_press_time -= dtime;
        if(self->long_press_time <= 0) {
            log_info("tool secondary_color: set");
            refs.brush->secondary_color = refs.brush->current_color;
            vec4 col = u_color_to_vec4(refs.brush->current_color);
            col.a = 1;
            animation_longpress(refs.animation,
                    u_pose_get_xy(self->color_drop.rect.pose), 
                    col);
        }
    }
}
static void tool_secondary_color_render(const struct Tool *super, const mat4 *cam_mat) {
    const ToolSecondaryColor *self = (const ToolSecondaryColor*) super;
    ro_single_render(&self->bg, cam_mat);
    ro_single_render(&self->color_drop, cam_mat);
}
Tool *tool_new_secondary_color() {
    ToolSecondaryColor *self = rhc_calloc(sizeof *self);

    self->bg = ro_single_new(r_texture_new_file(1, 1, "res/toolbar_color_bg.png"));
    self->color_drop = ro_single_new(r_texture_new_file(1, 1, "res/color_drop.png"));
    self->bg.rect.pose = u_pose_new(0, 0,
                                    self->bg.tex.sprite_size.x,
                                    self->bg.tex.sprite_size.y
    );
    self->color_drop.rect.pose = self->bg.rect.pose;

    snprintf(self->super.name, TOOL_NAME_LEN, "secondary color");
    snprintf(self->super.tip, TOOL_TIP_LEN, "tip to use\n\nhold to set");

    self->super.size = vec2_cast_from_int(self->bg.tex.sprite_size.v);

    self->super.kill = tool_secondary_color_kill;
    self->super.update = tool_secondary_color_update;
    self->super.render = tool_secondary_color_render;
    self->super.pointer_event = tool_secondary_color_pe;

    self->padding_lrbt = vec4_set(1);

    return (Tool*) self;
}

static void tool_shading_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(!button_toggled(&self->ro.rect, pointer))
        return;
    
    // only passed if button state toggled
    bool pressed = button_is_pressed(&self->ro.rect);
    log_info("tool shading: %i", pressed);
    refs.brush->shading_active = pressed;
}
static bool tool_shading_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.brush->shading_active);
    // always active
    return true;
}      
Tool *tool_new_shading() {
    return tool_button_new("shading", 
            "only paint above\nthe secondary color", 
            "res/button_shade.png", 
            tool_shading_pe,
            tool_shading_is_a);
}


static void tool_camera_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_clicked(&self->ro.rect, pointer)) {
        log_info("tool camera");
        cameractrl_set_home(refs.camctrl, 
                refs.canvas->RO.image.cols, 
                refs.canvas->RO.image.rows);
    }
}
Tool *tool_new_camera() {
    return tool_button_new("camera", 
            "resets the camera", 
            "res/button_camera.png", 
            tool_camera_pe,
            NULL);
}

static void tool_grid_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(!button_toggled(&self->ro.rect, pointer))
        return;
    
    // only passed if button state toggled
    bool pressed = button_is_pressed(&self->ro.rect);
    log_info("tool grid: %i", pressed);
    refs.canvas->show_grid = pressed;
}
static bool tool_grid_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.canvas->show_grid);
    // always active
    return true;
}      
Tool *tool_new_grid() {
    return tool_button_new("grid", 
            "enables\nand disables\na pixel grid", 
            "res/button_grid.png", 
            tool_grid_pe,
            tool_grid_is_a);
}

static void tool_preview_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(!button_toggled(&self->ro.rect, pointer))
        return;
    
    // only passed if button state toggled
    bool pressed = button_is_pressed(&self->ro.rect);
    log_info("tool preview: %i", pressed);
    refs.animation->show = pressed;
}
static bool tool_preview_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.animation->show);
    // always active
    return true;
}      
Tool *tool_new_preview() {
    return tool_button_new("preview", 
            "shows the\nanimated preview", 
            "res/button_play.png", 
            tool_preview_pe,
            tool_preview_is_a);
}





typedef struct {
    Tool super;
    RoText layer;
    RoSingle prev, next;
    int last_layer_id;
    float long_press_time;
    int pressed;
} ToolLayer;


static void tool_layer_kill(Tool **super_ptr) {
    ToolLayer *self = (ToolLayer*) *super_ptr;
    if(!self)
        return;
    ro_text_kill(&self->layer);
    ro_single_kill(&self->prev);
    ro_single_kill(&self->next);
    rhc_free(self);
    *super_ptr = NULL;
}
static void tool_layer_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolLayer *self = (ToolLayer*) super;
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
static void tool_layer_update(struct Tool *super, float dtime, ToolRefs refs) {
    ToolLayer *self = (ToolLayer*) super;
    
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
static void tool_layer_render(const struct Tool *super, const mat4 *cam_mat) {
    const ToolLayer *self = (const ToolLayer*) super;
    ro_text_render(&self->layer, cam_mat);
    ro_single_render(&self->prev, cam_mat);
    ro_single_render(&self->next, cam_mat);
}
Tool *tool_new_layer() {
    ToolLayer *self = rhc_calloc(sizeof *self);

    self->layer = ro_text_new_font55(2);
    self->prev = ro_single_new(r_texture_new_file(2, 1, "res/button_prev.png"));
    self->next = ro_single_new(r_texture_new_file(2, 1, "res/button_next.png"));
    self->prev.rect.pose = u_pose_new(0, 0, 16, 16);
    self->next.rect.pose = u_pose_new(0, 0, 16, 16);
    
    snprintf(self->super.name, TOOL_NAME_LEN, "layer");
    snprintf(self->super.tip, TOOL_TIP_LEN, "select a\ncanvas layer");

    self->super.kill = tool_layer_kill;
    self->super.update = tool_layer_update;
    self->super.render = tool_layer_render;
    self->super.pointer_event = tool_layer_pe;

    return (Tool*) self;
}
