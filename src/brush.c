#include <assert.h>
#include "canvas.h"
#include "selection.h"
#include "savestate.h"
#include "toolbar.h"
#include "brushmode.h"
#include "brushshape.h"
#include "brush.h"

struct BrushGlobals_s brush;

static struct {
    bool change;
    bool selection_active;
    bool selection_set;
    bool selection_moving;
    ivec2 selection_pos;
} L;


static void setup_selection(ePointer_s pointer) {
    uImage img = canvas_image();

    if (selection_active() && pointer.action == E_POINTER_UP) {
        L.selection_set = true;
        return;
    }
    ivec2 cr = canvas_get_cr(pointer.pos);
    if (!u_image_contains(img, cr.x, cr.y))
        return;

    if (L.selection_pos.x < 0) {
        if (pointer.action == E_POINTER_DOWN) {
            L.selection_pos = cr;
            toolbar.show_selection_copy_cut = true;
        }
    }

    if (L.selection_pos.x < 0)
        return;

    int left = cr.x < L.selection_pos.x ? cr.x : L.selection_pos.x;
    int top = cr.y < L.selection_pos.y ? cr.y : L.selection_pos.y;
    int cols = 1 + abs(cr.x - L.selection_pos.x);
    int rows = 1 + abs(cr.y - L.selection_pos.y);

    selection_init(left, top, cols, rows);
}

static void move_selection(ePointer_s pointer) {
    uImage img = canvas_image();
    int layer = canvas.current_layer;

    if (pointer.action == E_POINTER_UP) {
        L.selection_moving = false;
        return;
    }
    if (pointer.action == E_POINTER_DOWN) {
        L.selection_moving = true;
    }

    if (!L.selection_moving) {
        return;
    }

    ivec2 cr = canvas_get_cr(pointer.pos);

    if (brush.selection_mode != BRUSH_SELECTION_PASTE) {
        if (!u_image_contains(img, cr.x, cr.y))
            return;

        assert(brush.selection_mode == BRUSH_SELECTION_COPY
               || brush.selection_mode == BRUSH_SELECTION_CUT);

        if (brush.selection_mode == BRUSH_SELECTION_COPY)
            selection_copy(img, layer);
        else
            selection_cut(img, layer, brush.secondary_color);

        canvas_save();
        brush.selection_mode = BRUSH_SELECTION_PASTE;
        toolbar.show_selection_copy_cut = false;
        toolbar.show_selection_ok = true;
    }

    selection_move(cr.x - selection_size().x / 2,
                   cr.y - selection_size().y / 2);

    canvas_redo_image();
    selection_paste(img, layer);
}

void brush_init() {
    brush.current_color = COLOR_TRANSPARENT;
    brush.secondary_color = COLOR_TRANSPARENT;
    brush.mode = BRUSH_MODE_FREE;
    brush.shape = 0;
    brush.shading_active = false;
}

void brush_pointer_event(ePointer_s pointer) {
    if (pointer.id != 0)
        return;

    if (L.selection_active) {
        if (!L.selection_set) {
            setup_selection(pointer);
            return;
        }

        if (brush.selection_mode != BRUSH_SELECTION_NONE) {
            move_selection(pointer);
            return;
        }
    }

    bool change = false;
    switch (brush.mode) {
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER2:
            change = brushmode_free(pointer);
            break;
        case BRUSH_MODE_DOT:
            change = brushmode_dot(pointer);
            break;
        case BRUSH_MODE_FILL:
            change = brushmode_fill(pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brushmode_fill(pointer, true);
            break;
        case BRUSH_MODE_REPLACE:
            change = brushmode_replace(pointer);
            break;
        default:
            log_wtf("brush unknown mode");
    }

    if (change)
        L.change = true;

    if (L.change && pointer.action == E_POINTER_UP) {
        L.change = false;
        canvas_save();
    }

}

bool brush_draw_pixel(int c, int r) {
    uImage img = canvas_image();
    int layer = canvas.current_layer;
    if (!u_image_contains(img, c, r))
        return false;

    if (!selection_contains(c, r))
        return false;

    uColor_s *pixel = u_image_pixel(img, c, r, layer);
    if (brush.shading_active) {
        if (!u_color_equals(*pixel, brush.secondary_color))
            return false;
    }

    *pixel = brush.current_color;
    return true;
}


bool brush_draw(int c, int r) {
    if (brush.mode == BRUSH_MODE_DITHER)
        return brushshape_draw_dither(c, r, true);
    if (brush.mode == BRUSH_MODE_DITHER2)
        return brushshape_draw_dither(c, r, false);
    return brushshape_draw(c, r);
}

void brush_abort_current_draw() {
    log_info("brush: abort_current_draw");
    if (L.change) {
        canvas_redo_image();
        brushmode_reset(); // sets drawing to false
        L.change = false;
    }
}

void brush_set_selection_active(bool active, bool reset) {
    log_info("brush: set_selection_active : %i %i", active, reset);
    L.selection_active = active;
    if (reset) {
        L.selection_set = false;
        L.selection_pos = (ivec2) {{-1, -1}};
        selection_kill();
        brush.selection_mode = BRUSH_SELECTION_NONE;
    }
}
