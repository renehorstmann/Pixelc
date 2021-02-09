#include "canvas.h"
#include "savestate.h"
#include "brush_mode.h"
#include "brush_shape.h"
#include "brush.h"

Color_s brush_current_color;
Color_s brush_secondary_color;
enum brushmodes brush_mode;
int brush_shape;
bool brush_shading_active;

static struct {
    bool drawing;
    bool change;
} L;


void brush_init() {
    brush_current_color = COLOR_TRANSPARENT;
    brush_secondary_color = COLOR_TRANSPARENT;
    brush_mode = BRUSH_MODE_FREE;
    brush_shape = 0;
    brush_shading_active = false;
}

void brush_pointer_event(ePointer_s pointer) {
    if(pointer.id!=0)
        return;
        
    bool change = false;
    switch (brush_mode) {
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER2:
            change = brush_mode_free(pointer, &L.drawing);
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

bool brush_draw_pixel(float x, float y) {
	Image *img = canvas_image();
	int layer = canvas_current_layer;
	if (!image_contains(img, x, y))
        return false;
        
    Color_s *pixel = image_pixel(img, layer, y, x);
    if (brush_shading_active) {
    	if(!color_equals(*pixel, brush_secondary_color))
    	    return false;
    }
    
    *pixel = brush_current_color;
    return true;
}


bool brush_draw(float x, float y) {
	if(brush_mode == BRUSH_MODE_DITHER)
	    return brush_shape_dither(x, y, true);
	if(brush_mode == BRUSH_MODE_DITHER2)
	    return brush_shape_dither(x, y, false);
	return brush_shape_dot(x, y);
}

void brush_abort_current_draw() {
	if(L.change) {
		canvas_redo_image();
		L.change = false;
		L.drawing = false;
	}
}
