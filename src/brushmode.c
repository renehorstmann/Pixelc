#include "mathc/int.h"
#include "mathc/float.h"
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
            changed |= brush_draw(self->brush_ref, from.x + i * sign_x, sca_floor(0.5 + from.y + i * m * sign_y));
        return changed;
    }

    for (int i = 0; i <= dy; i++)
        changed |= brush_draw(self->brush_ref, sca_floor(0.5 + from.x + i / m * sign_x), from.y + i * sign_y);
    return changed;
}

static bool rectto(BrushMode *self, ivec2 from, ivec2 to) {
    int l = isca_min(from.x, to.x);
    int r = isca_max(from.x, to.x);
    int b = isca_min(from.y, to.y);
    int t = isca_max(from.y, to.y);
    
    bool changed = false;
    
    // top and bottom
    for(int i=l; i<=r; i++) {
        changed |= brush_draw(self->brush_ref, i, t);
        changed |= brush_draw(self->brush_ref, i, b);
    }
    
     // left and right (without the ends)
    for(int i=b+1; i<t; i++) {
        changed |= brush_draw(self->brush_ref, l, i);
        changed |= brush_draw(self->brush_ref, r, i);
    }
    
    return changed;
}

static bool circleto(BrushMode *self, ivec2 from, ivec2 to) {
    // horn circle rasterizing
    int r = ivec2_distance(from, to);
    printf("r=%i\n", r);
    int d = -r;
    int x = r;
    int y = 0;
    
    bool changed = false;
    
    do {
        changed |= brush_draw(self->brush_ref, from.x+x, from.y+y);
        changed |= brush_draw(self->brush_ref, from.x+y, from.y+x);
        changed |= brush_draw(self->brush_ref, from.x+x, from.y-y);
        changed |= brush_draw(self->brush_ref, from.x+y, from.y-x);
        changed |= brush_draw(self->brush_ref, from.x-x, from.y+y);
        changed |= brush_draw(self->brush_ref, from.x-y, from.y+x);
        changed |= brush_draw(self->brush_ref, from.x-x, from.y-y);
        changed |= brush_draw(self->brush_ref, from.x-y, from.y-x);
        
        d += 2*y + 1;
        y++;
        if(d>0) {
            d += -2*x + 2;
            x--;
        }
    } while(y<=x);
    
    return changed;
}


//
// public
//

BrushMode *brushmode_new(Brush *brush, Canvas *canvas) {
    BrushMode *self = rhc_calloc(sizeof *self);
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

    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};
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

    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};
    return brush_draw(self->brush_ref, cr.x, cr.y);
}

bool brushmode_func(BrushMode *self, ePointer_s pointer, enum brushmode_func func) {
    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};

    if (pointer.action == E_POINTER_DOWN) {
        self->L.is_drawing = true;
        self->L.start = cr;
    } else if (pointer.action != E_POINTER_MOVE) {
        self->L.is_drawing = false;
    }

    if (!self->L.is_drawing)
        return false;
        
    canvas_reload(self->canvas_ref);

    // just 1 pixel length
    if (ivec2_norm_inf(ivec2_sub_vec(cr, self->L.start)) <= 1)
        return brush_draw(self->brush_ref, cr.x, cr.y);

    switch (func) {
    case BRUSHMODE_FUNC_LINE: 
        return lineto(self, self->L.start, cr);
    case BRUSHMODE_FUNC_RECT:
        return rectto(self, self->L.start, cr);
    case BRUSHMODE_FUNC_CIRCLE:
        return circleto(self, self->L.start, cr);
    default:
        assume(0, "wtf");
        return false;
    }
}


void brushmode_pipette(BrushMode *self, ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return;

    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};
    uImage img = self->canvas_ref->RO.image;
    
    if(!u_image_contains(img, cr.x, cr.y))
        return;
        
    self->brush_ref->secondary_color = *u_image_pixel(img, cr.x, cr.y, self->canvas_ref->current_layer);
}
