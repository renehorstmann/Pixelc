#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "mathc/int.h"
#include "selectionctrl.h"

//
// private
//

static mat4 pixel_pose(int x, int y) {
    return u_pose_new_aa(x, -y, 1, 1);
}


static void setup_border(SelectionCtrl *self) {
    int x = 0, y = 0, w = 0, h = 0;
    if (self->selection) {
        x = self->selection->left;
        y = self->selection->top;
        w = self->selection->cols;
        h = self->selection->rows;
    }

    int max = self->L.border.num;

    int idx = 0;
    for (int i = 0; i < h; i++) {
        self->L.border.rects[idx].pose = pixel_pose(x - 1, y + i);
        self->L.border.rects[idx].sprite = (vec2) {0, 0};
        idx++;
        if (idx >= max) goto UPDATE;

        self->L.border.rects[idx].pose = pixel_pose(x + w, y + i);
        self->L.border.rects[idx].sprite = (vec2) {0, 1};
        idx++;
        if (idx >= max) goto UPDATE;
    }
    for (int i = 0; i < w; i++) {
        self->L.border.rects[idx].pose = pixel_pose(x + i, y - 1);
        self->L.border.rects[idx].sprite = (vec2) {1, 0};
        idx++;
        if (idx >= max) goto UPDATE;

        self->L.border.rects[idx].pose = pixel_pose(x + i, y + h);
        self->L.border.rects[idx].sprite = (vec2) {1, 1};
        idx++;
        if (idx >= max) goto UPDATE;
    }

    for (; idx < self->L.border.num; idx++) {
        u_pose_set(&self->L.border.rects[idx].pose, FLT_MAX, FLT_MAX, 0, 0, 0);
    }

    UPDATE:
    ro_batch_update(&self->L.border);
}

static void setup_selection(SelectionCtrl *self, ePointer_s pointer) {
    uImage img = self->canvas_ref->RO.image;

    if (self->selection && pointer.action == E_POINTER_UP) {
        self->mode = SELECTIONCTRL_SET;
        return;
    }
    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};
    if (self->L.pos.x < 0 && !u_image_contains(img, cr.x, cr.y))
        return;

    cr.x = isca_clamp(cr.x, 0, img.cols - 1);
    cr.y = isca_clamp(cr.y, 0, img.rows - 1);

    if (self->L.pos.x < 0) {
        if (pointer.action == E_POINTER_DOWN) {
            self->L.pos = cr;
            self->out.show_copy_cut = true;
        }
    }

    if (self->L.pos.x < 0)
        return;

    int left = cr.x < self->L.pos.x ? cr.x : self->L.pos.x;
    int top = cr.y < self->L.pos.y ? cr.y : self->L.pos.y;
    int cols = 1 + abs(cr.x - self->L.pos.x);
    int rows = 1 + abs(cr.y - self->L.pos.y);

    if (self->selection) {
        self->selection->left = left;
        self->selection->top = top;
        self->selection->cols = cols;
        self->selection->rows = rows;
    } else {
        self->selection = selection_new(left, top, cols, rows);
    }
}

static void move_selection(SelectionCtrl *self, ePointer_s pointer) {
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;

    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};

    if (pointer.action == E_POINTER_UP) {
        self->L.moving = false;
        return;
    }
    if (pointer.action == E_POINTER_DOWN) {
        self->L.moving = true;
        if(!selection_contains(self->selection, cr.x, cr.y)) {
            // touched outside the selection, so pushing the selection center into that position
            self->selection->left = cr.x - self->selection->cols / 2;
            self->selection->top = cr.y - self->selection->rows / 2;
        }
        self->L.move_start_selection_lt = (ivec2) {{self->selection->left, self->selection->top}};
        self->L.move_start_position = cr;
    }

    if (!self->L.moving) {
        return;
    }


    if (self->mode == SELECTIONCTRL_COPY
            || self->mode == SELECTIONCTRL_CUT) {
        if (!u_image_contains(img, cr.x, cr.y))
            return;

        if (self->mode == SELECTIONCTRL_COPY)
            selection_copy(self->selection, img, layer);
        else
            selection_cut(self->selection, img, layer, U_COLOR_TRANSPARENT);

        canvas_save(self->canvas_ref);
        self->mode = SELECTIONCTRL_PASTE;

        self->out.show_ok = true;
    }

    ivec2 grab_diff = ivec2_sub_vec(cr, self->L.move_start_position);
    self->selection->left = self->L.move_start_selection_lt.x + grab_diff.x;
    self->selection->top = self->L.move_start_selection_lt.y + grab_diff.y;

    canvas_reload(self->canvas_ref);
    selection_paste(self->selection, img, layer);
}


//
// public
//

SelectionCtrl *selectionctrl_new(Canvas *canvas) {
    SelectionCtrl *self = rhc_calloc(sizeof *self);
    
    self->canvas_ref = canvas;
    
    self->L.border = ro_batch_new(1024,
                                            r_texture_new_file(2, 2, "res/selection_border.png"));
    for (int i = 0; i < self->L.border.num; i++) {
        self->L.border.rects[i].color = u_color_to_vec4(u_color_from_hex("#357985"));
    }

    return self;
}

void selectionctrl_kill(SelectionCtrl **self_ptr) {
    SelectionCtrl *self = *self_ptr;
    if(!self)
        return;
    selection_kill(&self->selection);
    ro_batch_kill(&self->L.border);
    rhc_free(self);
    *self_ptr = NULL;
}

void selectionctrl_update(SelectionCtrl *self, float dtime) {
    setup_border(self);
}

void selectionctrl_render(const SelectionCtrl *self, const mat4 *cam_mat) {
    if(self->selection)
        ro_batch_render(&self->L.border, cam_mat, false);
}

bool selectionctrl_pointer_event(SelectionCtrl *self, ePointer_s pointer) {
    if (self->mode == SELECTIONCTRL_NONE
            || self->mode == SELECTIONCTRL_SET)
        return false;
        
    if (self->mode == SELECTIONCTRL_ACQUIRE)
        setup_selection(self, pointer);
    else
        move_selection(self, pointer);
    return true;
}

void selectionctrl_stop(SelectionCtrl *self) {
    log_info("selectionctrl stop");
    self->L.pos = (ivec2) {{-1, -1}};
    selection_kill(&self->selection);
    self->mode = SELECTIONCTRL_NONE;
}

void selectionctrl_acquire(SelectionCtrl *self) {
    log_info("selectionctrl acquire");
    self->L.pos = (ivec2) {{-1, -1}};
    selection_kill(&self->selection);
    self->mode = SELECTIONCTRL_ACQUIRE;
}

void selectionctrl_paste_image(SelectionCtrl *self, uImage img) {
    log_info("selectionctrl paste_image");
    self->L.pos = (ivec2) {{-1, -1}};
    selection_kill(&self->selection);
    self->selection = selection_new(0, 0, img.cols, img.rows);
    selection_copy(self->selection, img, 0);
    canvas_reload(self->canvas_ref);
    selection_paste(self->selection, self->canvas_ref->RO.image, self->canvas_ref->current_layer);
    self->mode = SELECTIONCTRL_PASTE;
}


