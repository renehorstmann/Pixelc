#include "brush.h"
#include "canvas.h"
#include "brush_mode.h"


static struct {
    bool is_drawing;	
	ivec2 last;
} L;

static bool lineto(ivec2 from, ivec2 to) {
	
	return brush_draw(to.x, to.y);
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
        return false;
    } else if (pointer.action != E_POINTER_MOVE) {
        L.is_drawing = false;
    }

    bool changed = lineto(L.last, uv);
    L.last = uv;
    return changed;
}
