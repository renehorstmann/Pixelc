#include "brush.h"
#include "canvas.h"
#include "brush_mode_dot_free.h"

bool brush_mode_dot(ePointer_s pointer) {	
    if (pointer.action != E_POINTER_DOWN)
        return false;
        
    ivec2 uv = canvas_get_uv(pointer.pos);
    return brush_draw(uv.x, uv.y);
}

bool brush_mode_free(ePointer_s pointer, bool *is_drawing) {
	if (pointer.action == E_POINTER_DOWN) {
        *is_drawing = true;
    } else if (pointer.action != E_POINTER_MOVE) {
        *is_drawing = false;
        return false;
    }
    if (!*is_drawing)
        return false;

    ivec2 uv = canvas_get_uv(pointer.pos);
    return brush_draw(uv.x, uv.y);
}
