#include "m/int.h"
#include "m/float.h"
#include "feedback.h"
#include "canvas.h"
#include "tooltip.h"
#include "brush.h"
#include "brushmode.h"

struct BrushMode_Globals brushmode;

//
// private
//

static bool lineto(ivec2 from, ivec2 to) {

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
            changed |= brush_draw(from.x, from.y + i * sign_y);
        return changed;
    }

    float m = (float) dy / dx;
    if (m <= 1) {
        for (int i = 0; i <= dx; i++)
            changed |= brush_draw(from.x + i * sign_x, sca_floor(0.5 + from.y + i * m * sign_y));
        return changed;
    }

    for (int i = 0; i <= dy; i++)
        changed |= brush_draw(sca_floor(0.5 + from.x + i / m * sign_x), from.y + i * sign_y);
    return changed;
}

static bool rectto(ivec2 from, ivec2 to) {
    int l = isca_min(from.x, to.x);
    int r = isca_max(from.x, to.x);
    int b = isca_min(from.y, to.y);
    int t = isca_max(from.y, to.y);

    bool changed = false;

    // top and bottom
    for (int i = l; i <= r; i++) {
        changed |= brush_draw(i, t);
        changed |= brush_draw(i, b);
    }

    // left and right (without the ends)
    for (int i = b + 1; i < t; i++) {
        changed |= brush_draw(l, i);
        changed |= brush_draw(r, i);
    }

    return changed;
}

static bool circleto(ivec2 from, ivec2 to) {
    // horn circle rasterizing
    int r = ivec2_distance(from, to);
    int d = -r;
    int x = r;
    int y = 0;

    bool changed = false;

    do {
        changed |= brush_draw(from.x + x, from.y + y);
        changed |= brush_draw(from.x + y, from.y + x);
        changed |= brush_draw(from.x + x, from.y - y);
        changed |= brush_draw(from.x + y, from.y - x);
        changed |= brush_draw(from.x - x, from.y + y);
        changed |= brush_draw(from.x - y, from.y + x);
        changed |= brush_draw(from.x - x, from.y - y);
        changed |= brush_draw(from.x - y, from.y - x);

        d += 2 * y + 1;
        y++;
        if (d > 0) {
            d += -2 * x + 2;
            x--;
        }
    } while (y <= x);

    return changed;
}


//
// public
//

void brushmode_init() {
}

void brushmode_reset() {
    brushmode.L.is_drawing = false;
}

bool brushmode_dot(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    ivec2 cr = canvas_get_cr(pointer.pos.xy);
    return brush_draw(cr.x, cr.y);
}

bool brushmode_free(ePointer_s pointer) {
    ivec2 cr = canvas_get_cr(pointer.pos.xy);

    if (pointer.action == E_POINTER_DOWN) {
        brushmode.L.is_drawing = true;
        brushmode.L.start = cr;
    } else if (pointer.action != E_POINTER_MOVE) {
        brushmode.L.is_drawing = false;
    }

    if (!brushmode.L.is_drawing)
        return false;

    bool ret = lineto(brushmode.L.start, cr);
    brushmode.L.start = cr;
    return ret;
}

bool brushmode_func(ePointer_s pointer, enum brushmode_func func) {
    ivec2 cr = canvas_get_cr(pointer.pos.xy);

    if (pointer.action == E_POINTER_DOWN) {
        brushmode.L.is_drawing = true;
        brushmode.L.start = cr;
    } else if (pointer.action != E_POINTER_MOVE) {
        brushmode.L.is_drawing = false;
    }

    if (!brushmode.L.is_drawing)
        return false;

    canvas_reload();

    // just 1 pixel length
    if (ivec2_norm_inf(ivec2_sub_vec(cr, brushmode.L.start)) < 1)
        return brush_draw(cr.x, cr.y);

    switch (func) {
        case BRUSHMODE_FUNC_LINE:
            return lineto(brushmode.L.start, cr);
        case BRUSHMODE_FUNC_RECT:
            return rectto(brushmode.L.start, cr);
        case BRUSHMODE_FUNC_CIRCLE:
            return circleto(brushmode.L.start, cr);
        default:
            s_assume(0, "wtf");
            return false;
    }
}


void brushmode_pipette(ePointer_s pointer, bool single) {
    if (pointer.action != E_POINTER_DOWN)
        return;

    ivec2 cr = canvas_get_cr(pointer.pos.xy);
    uImage img = canvas.RO.image;
    int layer = canvas.RO.current_image_layer;

    if (!u_image_contains(img, cr.x, cr.y))
        return;

    brush.secondary_color = *u_image_pixel(img, cr.x, cr.y, layer);
    brush.secondary_as_current = true;
    
    vec4 flash_color = u_color_to_vec4(brush.secondary_color);
    flash_color.a = 1;
    feedback_flash(flash_color, 0.5);
    tooltip_set("Pipette", "active");
    
    if(single) {
        brush.mode = brush.pipette_last_mode;
        brush.pipette_last_mode = BRUSH_MODE_NONE;
    }
}
