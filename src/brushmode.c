#include "mathc/int.h"
#include "brush.h"
#include "brushmode.h"


//
// private
//

static bool lineto(BrushMode *self, ivec2 from, ivec2 to) {

    int sign_x = 1, sign_y = 1;
    if (from.x > to.x)
        sign_x = -1;
    if (from.y > to.y)
        sign_y = -1;

    int dy = abs(to.y - from.y);
    int dx = abs(to.x - from.x);

    bool changed = false;
    if (dx == 0) {
        for (int i = 0; i <= dy; i++)
            changed |= brush_draw(self->brush_ref, from.x, from.y + i * sign_y);
        return changed;
    }

    float m = (float) dy / dx;
    if (m <= 1) {
        for (int i = 0; i <= dx; i++)
            changed |= brush_draw(self->brush_ref, from.x + i * sign_x, (from.y + i * m * sign_y));
        return changed;
    }

    for (int i = 0; i <= dy; i++)
        changed |= brush_draw(self->brush_ref, (from.x + i * m * sign_x), from.y + i * sign_y);
    return changed;
}



//
// public
//

BrushMode *brushmode_new(Brush *brush, const Canvas *canvas) {
    BrushMode *self = rhc_calloc_raising(sizeof *self);
    self->brush_ref = brush;
    self->canvas_ref = canvas;
    return self;
}

void brushmode_reset(BrushMode *self) {
    self->L.is_drawing = false;
}

bool brushmode_dot(BrushMode *self, ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    ivec2 cr = canvas_get_cr(self->canvas_ref, pointer.pos);
    return brush_draw(self->brush_ref, cr.x, cr.y);
}

bool brushmode_free(BrushMode *self, ePointer_s pointer) {
    if (pointer.action == E_POINTER_DOWN) {
        self->L.is_drawing = true;
    } else if (pointer.action != E_POINTER_MOVE) {
        self->L.is_drawing = false;
    }

    if (!self->L.is_drawing)
        return false;

    ivec2 cr = canvas_get_cr(self->canvas_ref, pointer.pos);
    return brush_draw(self->brush_ref, cr.x, cr.y);
}

bool brushmode_free_line(BrushMode *self, ePointer_s pointer) {
    ivec2 cr = canvas_get_cr(self->canvas_ref, pointer.pos);

    if (pointer.action == E_POINTER_DOWN) {
        self->L.is_drawing = true;
        self->L.last = cr;
    } else if (pointer.action != E_POINTER_MOVE) {
        self->L.is_drawing = false;
    }

    if (!self->L.is_drawing)
        return false;

    // just 1 pixel length
    if (ivec2_norm_inf(ivec2_sub_vec(cr, self->L.last)) <= 1)
        return brush_draw(self->brush_ref, cr.x, cr.y);

    bool changed = lineto(self, self->L.last, cr);
    self->L.last = cr;
    return changed;
}
