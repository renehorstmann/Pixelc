#include <assert.h>
#include "mathc/sca/int.h"
#include "brushshape.h"
#include "brush.h"




//
// public
//

Brush *brush_new(Canvas *canvas, const SelectionCtrl *selectionctrl) {
    Brush *self = rhc_calloc(sizeof *self);

    self->canvas_ref = canvas;
    self->selectionctrl_ref = selectionctrl;
    
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

    Selection *selection = self->selectionctrl_ref->selection;
    if (selection && !selection_contains(selection, c, r))
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

void brush_clear(Brush *self) {
    log_info("brush: clear");
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    Selection *selection = self->selectionctrl_ref->selection;
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            if (selection && !selection_contains(selection, c, r))
                continue;

            *u_image_pixel(img, c, r, layer) = U_COLOR_TRANSPARENT;
        }
    }
    canvas_save(self->canvas_ref);
}
