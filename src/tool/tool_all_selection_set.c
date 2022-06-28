#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/sca/int.h"
#include "u/button.h"
#include "canvas.h"
#include "camera.h"
#include "selectionctrl.h"
#include "tool.h"


// own tool
typedef struct {
    Tool super;
    RoBatch ro;
    bool active[8];
    bool prev_active[8];
} SetMove;

static void move_kill(Tool **super_ptr) {
    SetMove *self = (SetMove *) *super_ptr;
    if (!self)
        return;
    ro_batch_kill(&self->ro);
    s_free(self);
    *super_ptr = NULL;
}

static void move_update(Tool *super, float dtime) {
    SetMove *self = (SetMove *) super;
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    int img_cols = canvas.RO.image.cols;
    int img_rows = canvas.RO.image.rows;

    self->active[0] = s->left > 0;
    self->active[1] = s->cols > 1;
    self->active[2] = s->cols > 1;
    self->active[3] = s->left + s->cols < img_cols;
    self->active[4] = s->top > 0;
    self->active[5] = s->rows > 1;
    self->active[6] = s->rows > 1;
    self->active[7] = s->top + s->rows < img_rows;

    float l[8];
    float t[8];
    if (camera_is_portrait_mode()) {
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

        super->size.x = 70 + 16;
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
        super->size.y = 70 + 16;
    }

    for (int i = 0; i < 8; i++) {
        if (self->active[i] && !self->prev_active[i])
            self->ro.rects[i].sprite.x = 0;
        if (!self->active[i])
            self->ro.rects[i].sprite.x = 1;

        u_pose_aa_set_left(&self->ro.rects[i].pose, l[i] + super->in.pos.x);
        u_pose_aa_set_top(&self->ro.rects[i].pose, t[i] + super->in.pos.y);
    }

    memcpy(self->prev_active, self->active, sizeof self->active);
}

static void move_render(const struct Tool *super, const mat4 *cam_mat) {
    SetMove *self = (SetMove *) super;
    ro_batch_render(&self->ro, cam_mat, true);
}

static void move_pe(struct Tool *super, ePointer_s pointer) {
    SetMove *self = (SetMove *) super;
    Selection *s = selectionctrl.selection;

    // may occur on pointer up
    if (!s)
        return;

    int img_cols = canvas.RO.image.cols;
    int img_rows = canvas.RO.image.rows;

    for (int i = 0; i < 8; i++) {
        if (self->active[i] && u_button_clicked(&self->ro.rects[i], pointer)) {
            s_log("tool selection set move: %i", i);
            if (i == 0 && s->left > 0) {
                s->left--;
                s->cols++;
            } else if (i == 1 && s->cols > 1) {
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
    SetMove *self = s_malloc0(sizeof *self);
    self->ro = ro_batch_new(8, r_texture_new_file(2, 8, "res/button_selection_move.png"));

    for (int i = 0; i < 8; i++) {
        self->ro.rects[i].sprite.y = i;
        self->ro.rects[i].pose = u_pose_new(0, 0,
                                            self->ro.tex.sprite_size.x,
                                            self->ro.tex.sprite_size.y

        );
    }

    snprintf(self->super.name, TOOL_NAME_LEN, "move");
    snprintf(self->super.tip, TOOL_TIP_LEN, "move the\nselection borders");

    self->super.kill = move_kill;
    self->super.update = move_update;
    self->super.render = move_render;
    self->super.pointer_event = move_pe;

    return (Tool *) self;
}

static void copy_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_toggled(&self->ro.rect, pointer)) {
        bool pressed = u_button_is_pressed(&self->ro.rect);
        if (pressed) {
            s_log("tool selection set copy: start");
            selectionctrl.mode = SELECTIONCTRL_COPY;
        } else {
            s_log("tool selection set copy: stop");
            selectionctrl.mode = SELECTIONCTRL_SET;
        }
    }
}

static bool copy_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, selectionctrl.mode == SELECTIONCTRL_COPY);
    // always active
    return true;
}

Tool *tool_new_selection_set_copy() {
    return tool_button_new("copy",
                           "copies\nthe selection",
                           "res/button_copy.png",
                           copy_pe,
                           copy_is_a);
}

static void cut_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_toggled(&self->ro.rect, pointer)) {
        bool pressed = u_button_is_pressed(&self->ro.rect);
        if (pressed) {
            s_log("tool selection set cut: start");
            selectionctrl.mode = SELECTIONCTRL_CUT;
        } else {
            s_log("tool selection set cut: stop");
            selectionctrl.mode = SELECTIONCTRL_SET;
        }
    }
}

static bool cut_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, selectionctrl.mode == SELECTIONCTRL_CUT);
    // always active
    return true;
}

Tool *tool_new_selection_set_cut() {
    return tool_button_new("cut",
                           "cuts\nthe selection",
                           "res/button_cut.png",
                           cut_pe,
                           cut_is_a);
}
