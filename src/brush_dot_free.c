#include "brush.h"
#include "canvas.h"
#include "brush_dot_free.h"

bool brush_dot(ePointer_s pointer) {	
    if (pointer.action != E_POINTER_DOWN)
        return false;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    ivec2 uv = canvas_get_uv(pointer.pos);

    if(image_contains_uv(img, uv)) {
        *image_pixel_uv(img, layer, uv) = brush_current_color;
        return true;
    }
    return false;
}

bool brush_free(ePointer_s pointer, bool *is_drawing) {
	if (pointer.action == E_POINTER_DOWN) {
        *is_drawing = true;
    } else if (pointer.action != E_POINTER_MOVE) {
        *is_drawing = false;
        return false;
    }
    if (!*is_drawing)
        return false;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    ivec2 uv = canvas_get_uv(pointer.pos);

    if(image_contains_uv(img, uv)) {
        *image_pixel_uv(img, layer, uv) = brush_current_color;
        return true;
    }
    return false;
}
