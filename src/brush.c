#include <assert.h>
#include "canvas.h"
#include "selection.h"
#include "savestate.h"
#include "toolbar.h"
#include "brush_mode.h"
#include "brush_shape.h"
#include "brush.h"

struct BrushGlobals_s brush;

static struct {
    bool change;
    bool selection_active;
    bool selection_set;
    ivec2 selection_pos;
} L;


static void setup_selection(ePointer_s pointer) {
	ivec2 cr = canvas_get_cr(pointer.pos);
	if(!image_contains(canvas_image(), cr.x, cr.y))
	    return;
	    
	if(L.selection_pos.x < 0) {
	    if(pointer.action == E_POINTER_DOWN)
	        L.selection_pos = cr;
	    return;
	}
    int left = cr.x < L.selection_pos.x ? cr.x : L.selection_pos.x;
    int top = cr.y < L.selection_pos.y ? cr.y : L.selection_pos.y;
    int cols = 1+abs(cr.x - L.selection_pos.x);
    int rows = 1+abs(cr.y - L.selection_pos.y);
    selection_init(left, top, cols, rows);
    if(pointer.action == E_POINTER_UP) {
    	L.selection_set = true;
    	toolbar.show_selection_copy_cut = true;
    }
}

static void move_selection(ePointer_s pointer) {
	if(pointer.action == E_POINTER_UP)
	    return;
	    
	ivec2 cr = canvas_get_cr(pointer.pos);
	    
	if(brush.selection_mode != BRUSH_SELECTION_PASTE && pointer.action == E_POINTER_DOWN) {
	    assert(brush.selection_mode == BRUSH_SELECTION_COPY 
	            || brush.selection_mode == BRUSH_SELECTION_CUT);
	    if(brush.selection_mode == BRUSH_SELECTION_COPY)
	        selection_copy(canvas_image(), canvas.current_layer);
	    else
	        selection_cut(canvas_image(), canvas.current_layer, brush.secondary_color);
	    
	    canvas_save();
	    brush.selection_mode = BRUSH_SELECTION_PASTE;
	    toolbar.show_selection_copy_cut = false;
	    toolbar.show_selection_ok = true;
	}
	
	selection_move(cr.x-selection_size().x/2, 
	        cr.y-selection_size().y/2);
	
	canvas_redo_image();
    selection_paste(canvas_image(), canvas.current_layer);
}

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
        
    if(L.selection_active && !L.selection_set) {
        setup_selection(pointer);
        return;
    }
    
    if(L.selection_set && brush.selection_mode != BRUSH_SELECTION_NONE) {
        move_selection(pointer);
        return;
    }
        
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

void brush_set_selection_active(bool active) {
	L.selection_active = active;
	L.selection_set = false;
	L.selection_pos = (ivec2) {{-1, -1}};
	selection_kill();
	brush.selection_mode = BRUSH_SELECTION_NONE;
}
