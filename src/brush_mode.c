#include "mathc/int.h"
#include "brush.h"
#include "canvas.h"
#include "brush_mode.h"

static struct {
    bool is_drawing;
    ivec2 last;
} L;

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
        for(int i=0; i<=dy; i++)
            changed |= brush_draw(from.x, from.y + i * sign_y);
        return changed;
    }

    float m = (float) dy / dx;
    if (m <= 1) {
        for (int i = 0; i <= dx; i++)
            changed |= brush_draw(from.x + i * sign_x, (from.y + i * m * sign_y));
        return changed;
    }

    for (int i = 0; i <= dy; i++)
        changed |= brush_draw((from.x + i * m * sign_x), from.y + i * sign_y);
    return changed;
}


void brush_mode_reset() {
    L.is_drawing = false;
}

bool brush_mode_dot(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    ivec2 uv = canvas_get_uv(pointer.pos);
    return brush_draw(uv.x, uv.y);
}

bool brush_mode_free(ePointer_s pointer) {
    ivec2 uv = canvas_get_uv(pointer.pos);

    if (pointer.action == E_POINTER_DOWN) {
        L.is_drawing = true;
        L.last = uv;
    } else if (pointer.action != E_POINTER_MOVE) {
        L.is_drawing = false;
    }

    if (!L.is_drawing)
        return false;

    // just 1 pixel length
    if(ivec2_norm_inf(ivec2_sub_vec(uv, L.last)) <= 1)
        return brush_draw(uv.x, uv.y);

    bool changed = lineto(L.last, uv);
    L.last = uv;
    return changed;
}
