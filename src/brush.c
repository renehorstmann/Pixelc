#include "canvas.h"
#include "savestate.h"
#include "brush_dot_free.h"
#include "brush_fill.h"
#include "brush.h"

Color_s brush_current_color;
Color_s brush_secondary_color;

static struct {
    enum brushmodes mode;
    bool drawing;
    bool change;
} L;


void brush_pointer_event(ePointer_s pointer) {
    if(pointer.id!=0)
        return;
        
    bool change = false;
    switch (L.mode) {
        case BRUSH_MODE_DOT:
            change = brush_dot(pointer);
            break;
        case BRUSH_MODE_FREE:
            change = brush_free(pointer, &L.drawing);
            break;
        case BRUSH_MODE_FILL:
            change = brush_fill(pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brush_fill(pointer, true);
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


void brush_init() {
    brush_current_color = COLOR_TRANSPARENT;
    L.mode = BRUSH_MODE_FREE;
}

enum brushmodes brush_get_mode() {
    return L.mode;
}

void brush_set_mode(enum brushmodes mode) {
    L.mode = mode;
    L.drawing = false;
}

void brush_abort_current_draw() {
	if(L.change) {
		ePointer_s up = {0};
		up.action = E_POINTER_UP;
		brush_pointer_event(up);
		savestate_undo();
	}
}
