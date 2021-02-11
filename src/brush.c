#include "canvas.h"
#include "selection.h"
#include "savestate.h"
#include "brush_mode.h"
#include "brush_shape.h"
#include "brush.h"

struct BrushGlobals_s brush;

static struct {
    bool change;
} L;


void brush_init() {
    brush.current_color = COLOR_TRANSPARENT;
    brush.secondary_color = COLOR_TRANSPARENT;
    brush.mode = BRUSH_MODE_FREE;
    brush.shape = 0;
    brush.shading_active = false;
}

void brush_pointer_event(ePointer_s pointer) {
    if(pointer.id!=0)
        return;
        
    bool change = false;
    switch (brush.mode) {
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER2:
            change = brush_mode_free(pointer);
            break;
        case BRUSH_MODE_DOT:
            change = brush_mode_dot(pointer);
            break;
        case BRUSH_MODE_FILL:
            change = brush_mode_fill(pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brush_mode_fill(pointer, true);
            break;
            
        default:
            SDL_Log("brush unknown mode");
    }
    
    if(change)
        L.change = true;

    if (L.change && pointer.action == E_POINTER_UP) {
        L.change = false;
        canvas_save();
    }
    
}

bool brush_draw_pixel(int c, int r) {
	Image *img = canvas_image();
	int layer = canvas.current_layer;
	if (!image_contains(img, c, r))
        return false;
        
    if(!selection_contains(c, r))
        return false;
        
    Color_s *pixel = image_pixel(img, layer, c, r);
    if (brush.shading_active) {
    	if(!color_equals(*pixel, brush.secondary_color))
    	    return false;
    }
    
    *pixel = brush.current_color;
    return true;
}


bool brush_draw(int c, int r) {
	if(brush.mode == BRUSH_MODE_DITHER)
	    return brush_shape_draw_dither(c, r, true);
	if(brush.mode == BRUSH_MODE_DITHER2)
	    return brush_shape_draw_dither(c, r, false);
	return brush_shape_draw(c, r);
}

void brush_abort_current_draw() {
	if(L.change) {
		canvas_redo_image();
		brush_mode_reset(); // sets drawing to false
		L.change = false;
	}
}
