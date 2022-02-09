#include "r/ro_single.h"
#include "r/ro_batch.h"
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
    
    u_pose_aa_set_left(&self->ro.rect.pose,
            super->in.pos.x + self->padding_lrbt.v0);
    u_pose_aa_set_top(&self->ro.rect.pose,
            super->in.pos.y - self->padding_lrbt.v3);
            
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
        canvas_set_image(refs.canvas, img, true);
        canvas_save(refs.canvas);
    } 
}
Tool *tool_new_import() {
    return tool_button_new("import", 
            "loads import.png as selection", 
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
    if(pressed)
        selectionctrl_acquire(refs.selectionctrl);
    else 
        selectionctrl_stop(refs.selectionctrl);
    
}
static bool tool_selection_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.selectionctrl->mode != SELECTIONCTRL_NONE);
    // always active
    return true;
}      
Tool *tool_new_selection() {
    return tool_button_new("selection", 
            "toggle a canvas selection", 
            "res/button_selection.png", 
            tool_selection_pe,
            tool_selection_is_a);
}



// own tool
typedef struct {
    Tool super;
    RoBatch ro;
    bool active[8];
    bool prev_active[8];
} SelectionSetMove;
static void selection_set_move_kill(Tool **super_ptr) {
    SelectionSetMove *self = (SelectionSetMove*) *super_ptr;
    if(!self)
        return;
    ro_batch_kill(&self->ro);
    rhc_free(self);
    *super_ptr = NULL;
}

static void selection_set_move_update(Tool *super, float dtime, ToolRefs refs) {
    SelectionSetMove *self = (SelectionSetMove*) super;
    Selection *s = refs.selectionctrl->selection;
    if(!s)
        return;
    int img_cols = refs.canvas->RO.image.cols;
    int img_rows = refs.canvas->RO.image.rows;
    
    self->active[0] = s->left>0;
    self->active[1] = s->cols>1;
    self->active[2] = s->cols>1;
    self->active[3] = s->left+s->cols<img_cols;
    self->active[4] = s->top>0;
    self->active[5] = s->rows>1;
    self->active[6] = s->rows>1;
    self->active[7] = s->top+s->rows<img_rows;
    
    float l[8];
    float t[8];
    
    
    if(camera_is_portrait_mode(refs.cam)) {
        // left
        l[0] = 1;
        t[0] = -1;
        l[1] = 1;
        t[1] = -18;
        
        // top
        l[4] = 19;
        t[4] = -1;
        l[5] = 35;
        t[5] = -1;
        
        // bottom
        l[6] = 19;
        t[6] = -18;
        l[7] = 35;
        t[7] = -18;
        
        // right
        l[2] = 53;
        t[2] = -1;
        l[3] = 53;
        t[3] = -18;
        
        super->size.x = 70;
        super->size.y = 35;
    } else {
        
        // top
        l[4] = 2;
        t[4] = -1;
        l[5] = 18;
        t[5] = -1;
        
        // left
        l[0] = 1;
        t[0] = -19;
        l[1] = 1;
        t[1] = -36;
        
        // right
        l[2] = 20;
        t[2] = -19;
        l[3] = 20;
        t[3] = -36;
        
        // bottom
        l[6] = 2;
        t[6] = -54;
        l[7] = 18;
        t[7] = -54;
        
        super->size.x = 37;
        super->size.y = 71;
    }
    
    for(int i=0;i<8;i++) {
        if(self->active[i] && !self->prev_active[i])
            self->ro.rects[i].sprite.x = 0;
        if(!self->active[i])
            self->ro.rects[i].sprite.x = 1;
            
        u_pose_aa_set_left(&self->ro.rects[i].pose,
                l[i] + super->in.pos.x);
        u_pose_aa_set_top(&self->ro.rects[i].pose, 
                t[i] + super->in.pos.y);
    }
    
    memcpy(self->prev_active, self->active, sizeof self->active);
    
    
    
}

static void selection_set_move_render(const struct Tool *super, const mat4 *cam_mat) {
    SelectionSetMove *self = (SelectionSetMove*) super;
    ro_batch_render(&self->ro, cam_mat, true);
}
static void selection_set_move_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    SelectionSetMove *self = (SelectionSetMove*) super;
    Selection *s = refs.selectionctrl->selection;
    if(!s) {
        log_wtf("tool selection set move failed, selection nit availeble");
        return;
    }
    int img_cols = refs.canvas->RO.image.cols;
    int img_rows = refs.canvas->RO.image.rows;
    
    for(int i=0; i<8; i++) {
        if(self->active[i] && button_clicked(&self->ro.rects[i], pointer)) {
            if (i == 0 && s->left>0) {
                s->left--;
                s->cols++;
            } else if (i == 1 && s->cols>1) {
                s->left++;
                s->cols--;
            } else if (i == 2) {
                s->cols--;
            } else if (i == 3) {
                s->cols++;
            } else if (i == 4 && s->top > 0) {
                s->top--;
                s->rows++;
            } else if (i == 5 && s->rows > 1) {
                s->top++;
                s->rows--;
            } else if (i == 6) {
                s->rows--;
            } else if (i == 7) {
                s->rows++;
            }    
        }
    }
    s->left = isca_clamp(s->left, 0, img_cols - 1);
    s->top = isca_clamp(s->top, 0, img_rows - 1);
    s->cols = isca_clamp(s->cols, 1, img_cols - s->left);
    s->rows = isca_clamp(s->rows, 1, img_rows - s->top);
}
Tool *tool_new_selection_set_move() {
    SelectionSetMove *self = rhc_calloc(sizeof *self);
    self->ro = ro_batch_new(8, r_texture_new_file(2, 8, "res/button_selection_move.png"));
    
    for(int i=0;i<8;i++) {
        self->ro.rects[i].sprite.y = i;
        self->ro.rects[i].pose = u_pose_new(0, 0, 
                self->ro.tex.sprite_size.x,
                self->ro.tex.sprite_size.y
                );
    }
    
    snprintf(self->super.name, TOOL_NAME_LEN, "selection set move");
    snprintf(self->super.tip, TOOL_TIP_LEN, "move the selection borders");
    
    self->super.kill = selection_set_move_kill;
    self->super.update = selection_set_move_update;
    self->super.render = selection_set_move_render;
    self->super.pointer_event = selection_set_move_pe;
    
    return (Tool*) self;
}
