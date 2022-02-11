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

// own tool
typedef struct {
    Tool super;
    RoBatch ro;
    bool active[8];
    bool prev_active[8];
} SetMove;
static void set_move_kill(Tool **super_ptr) {
    SetMove *self = (SetMove*) *super_ptr;
    if(!self)
        return;
    ro_batch_kill(&self->ro);
    rhc_free(self);
    *super_ptr = NULL;
}

static void set_move_update(Tool *super, float dtime, ToolRefs refs) {
    SetMove *self = (SetMove*) super;
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
        t[0] = -3;
        l[1] = 1;
        t[1] = -19;

        // right
        l[2] = 53;
        t[2] = -19;
        l[3] = 53;
        t[3] = -3;

        // top
        l[4] = 19;
        t[4] = -1;
        l[5] = 35;
        t[5] = -1;

        // bottom
        l[6] = 35;
        t[6] = -21;
        l[7] = 19;
        t[7] = -21;

        super->size.x = 70+16;
        super->size.y = 38;
    } else {
        // left
        l[0] = 1;
        t[0] = -19;
        l[1] = 1;
        t[1] = -35;

        // right
        l[2] = 21;
        t[2] = -35;
        l[3] = 21;
        t[3] = -19;

        // top
        l[4] = 3;
        t[4] = -1;
        l[5] = 19;
        t[5] = -1;

        // bottom
        l[6] = 19;
        t[6] = -53;
        l[7] = 3;
        t[7] = -53;

        super->size.x = 38;
        super->size.y = 70+16;
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

static void set_move_render(const struct Tool *super, const mat4 *cam_mat) {
    SetMove *self = (SetMove*) super;
    ro_batch_render(&self->ro, cam_mat, true);
}
static void set_move_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    SetMove *self = (SetMove*) super;
    Selection *s = refs.selectionctrl->selection;

    // may occur on pointer up
    if(!s)
        return;

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
    SetMove *self = rhc_calloc(sizeof *self);
    self->ro = ro_batch_new(8, r_texture_new_file(2, 8, "res/button_selection_move.png"));

    for(int i=0;i<8;i++) {
        self->ro.rects[i].sprite.y = i;
        self->ro.rects[i].pose = u_pose_new(0, 0,
                                            self->ro.tex.sprite_size.x,
                                            self->ro.tex.sprite_size.y
        );
    }

    snprintf(self->super.name, TOOL_NAME_LEN, "selection move");
    snprintf(self->super.tip, TOOL_TIP_LEN, "move the selection borders");

    self->super.kill = set_move_kill;
    self->super.update = set_move_update;
    self->super.render = set_move_render;
    self->super.pointer_event = set_move_pe;

    return (Tool*) self;
}

static void set_copy_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_toggled(&self->ro.rect, pointer)) {
        bool pressed = button_is_pressed(&self->ro.rect);
        if (pressed) {
            refs.selectionctrl->mode = SELECTIONCTRL_COPY;
        } else {
            refs.selectionctrl->mode = SELECTIONCTRL_SET;
        }
    } 
}
static bool set_copy_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.selectionctrl->mode == SELECTIONCTRL_COPY);
    // always active
    return true;
}      
Tool *tool_new_selection_set_copy() {
    return tool_button_new("selection copy", 
            "copies the selection", 
            "res/button_copy.png", 
            set_copy_pe,
            set_copy_is_a);
}

static void set_cut_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_toggled(&self->ro.rect, pointer)) {
        bool pressed = button_is_pressed(&self->ro.rect);
        if (pressed) {
            refs.selectionctrl->mode = SELECTIONCTRL_CUT;
        } else {
            refs.selectionctrl->mode = SELECTIONCTRL_SET;
        }
    } 
}
static bool set_cut_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    button_set_pressed(&self->ro.rect, refs.selectionctrl->mode == SELECTIONCTRL_CUT);
    // always active
    return true;
}      
Tool *tool_new_selection_set_cut() {
    return tool_button_new("selection cut", 
            "cuts the selection", 
            "res/button_cut.png", 
            set_cut_pe,
            set_cut_is_a);
}

static void paste_copy_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_clicked(&self->ro.rect, pointer)) {
        canvas_save(refs.canvas);
    } 
}
Tool *tool_new_selection_paste_copy() {
    return tool_button_new("selection copy", 
            "copies the current selection paste", 
            "res/button_copy.png", 
            paste_copy_pe,
            NULL);
}

static void paste_ok_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_clicked(&self->ro.rect, pointer)) {
        canvas_save(refs.canvas);
        selectionctrl_stop(refs.selectionctrl);
    } 
}
Tool *tool_new_selection_paste_ok() {
    return tool_button_new("selection copy", 
            "copies the current selection paste and stops the selection mode", 
            "res/button_ok.png", 
            paste_ok_pe,
            NULL);
}
