#include <assert.h>
#include "mathc/sca/int.h"
#include "toolbar.h"
#include "brushshape.h"
#include "brush.h"

//
// private
//


static void setup_selection(Brush *self, ePointer_s pointer) {
    uImage img = self->canvas_ref->RO.image;

    if (self->selection && pointer.action == E_POINTER_UP) {
        self->L.selection_set = true;
        return;
    }
    ivec2 cr = canvas_get_cr(self->canvas_ref, pointer.pos);
    if (self->L.selection_pos.x < 0 && !u_image_contains(img, cr.x, cr.y))
        return;

    cr.x = isca_clamp(cr.x, 0, img.cols - 1);
    cr.y = isca_clamp(cr.y, 0, img.rows - 1);

    if (self->L.selection_pos.x < 0) {
        if (pointer.action == E_POINTER_DOWN) {
            self->L.selection_pos = cr;
            assert(self->toolbar_ref);
            self->toolbar_ref->show_selection_copy_cut = true;
        }
    }

    if (self->L.selection_pos.x < 0)
        return;

    int left = cr.x < self->L.selection_pos.x ? cr.x : self->L.selection_pos.x;
    int top = cr.y < self->L.selection_pos.y ? cr.y : self->L.selection_pos.y;
    int cols = 1 + abs(cr.x - self->L.selection_pos.x);
    int rows = 1 + abs(cr.y - self->L.selection_pos.y);

    if (self->selection) {
        self->selection->left = left;
        self->selection->top = top;
        self->selection->cols = cols;
        self->selection->rows = rows;
    } else {
        self->selection = selection_new(left, top, cols, rows);
    }
}

static void move_selection(Brush *self, ePointer_s pointer) {
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;

    if (pointer.action == E_POINTER_UP) {
        self->L.selection_moving = false;
        return;
    }
    if (pointer.action == E_POINTER_DOWN) {
        self->L.selection_moving = true;
    }

    if (!self->L.selection_moving) {
        return;
    }

    ivec2 cr = canvas_get_cr(self->canvas_ref, pointer.pos);

    if (self->selection_mode != BRUSH_SELECTION_PASTE) {
        if (!u_image_contains(img, cr.x, cr.y))
            return;

        assert(self->selection_mode == BRUSH_SELECTION_COPY
               || self->selection_mode == BRUSH_SELECTION_CUT);

        if (self->selection_mode == BRUSH_SELECTION_COPY)
            selection_copy(self->selection, img, layer);
        else
            selection_cut(self->selection, img, layer, self->secondary_color);

        canvas_save(self->canvas_ref);
        self->selection_mode = BRUSH_SELECTION_PASTE;

        assert(self->toolbar_ref);
        self->toolbar_ref->show_selection_copy_cut = false;
        self->toolbar_ref->show_selection_ok = true;
    }

    self->selection->left = cr.x - self->selection->cols / 2;
    self->selection->top = cr.y - self->selection->rows / 2;

    canvas_redo_image(self->canvas_ref);
    selection_paste(self->selection, img, layer);
}



//
// public
//

Brush *brush_new(Canvas *canvas) {
    Brush *self = rhc_calloc_raising(sizeof *self);

    self->canvas_ref = canvas;
    self->canvas_ref->brush_ref = self;     // ...

    self->brushmode = brushmode_new(self, canvas);

    self->current_color = U_COLOR_TRANSPARENT;
    self->secondary_color = U_COLOR_TRANSPARENT;
    self->mode = BRUSH_MODE_FREE;
    self->shape = 0;
    self->shading_active = false;

    return self;
}

void brush_pointer_event(Brush *self, ePointer_s pointer) {
    if (pointer.id != 0)
        return;

    if (self->L.selection_active) {
        if (!self->L.selection_set) {
            setup_selection(self, pointer);
            return;
        }

        if (self->selection_mode != BRUSH_SELECTION_NONE) {
            move_selection(self, pointer);
            return;
        }
    }

    bool change = false;
    switch (self->mode) {
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER2:
            change = brushmode_free(self->brushmode, pointer);
            break;
        case BRUSH_MODE_DOT:
            change = brushmode_dot(self->brushmode, pointer);
            break;
        case BRUSH_MODE_FILL:
            change = brushmode_fill(self->brushmode, pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brushmode_fill(self->brushmode, pointer, true);
            break;
        case BRUSH_MODE_REPLACE:
            change = brushmode_replace(self->brushmode, pointer);
            break;
        default:
            log_wtf("brush unknown mode");
    }

    if (change)
        self->L.change = true;

    if (self->L.change && pointer.action == E_POINTER_UP) {
        self->L.change = false;
        canvas_save(self->canvas_ref);
    }

}

bool brush_draw_pixel(Brush *self, int c, int r) {
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    if (!u_image_contains(img, c, r))
        return false;

    if (self->selection && !selection_contains(self->selection, c, r))
        return false;

    uColor_s *pixel = u_image_pixel(img, c, r, layer);
    if (self->shading_active) {
        if (!u_color_equals(*pixel, self->secondary_color))
            return false;
    }

    *pixel = self->current_color;
    return true;
}


bool brush_draw(Brush *self, int c, int r) {
    if (self->mode == BRUSH_MODE_DITHER)
        return brushshape_draw_dither(self, c, r, true);
    if (self->mode == BRUSH_MODE_DITHER2)
        return brushshape_draw_dither(self, c, r, false);
    return brushshape_draw(self, c, r);
}

void brush_abort_current_draw(Brush *self) {
    log_info("brush: abort_current_draw");
    if (self->L.change) {
        canvas_redo_image(self->canvas_ref);
        brushmode_reset(self->brushmode); // sets drawing to false
        self->L.change = false;
    }
}

void brush_set_selection_active(Brush *self, bool active, bool reset) {
    log_info("brush: set_selection_active : %i %i", active, reset);
    self->L.selection_active = active;
    if (reset) {
        self->L.selection_set = false;
        self->L.selection_pos = (ivec2) {{-1, -1}};
        selection_kill(&self->selection);
        self->selection_mode = BRUSH_SELECTION_NONE;
    }
}
