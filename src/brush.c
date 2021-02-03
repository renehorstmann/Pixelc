#include "e/input.h"
#include "mathc/float.h"

#include "color.h"
#include "c_camera.h"
#include "io.h"
#include "canvas.h"
#include "savestate.h"
#include "brush.h"

static struct {
    Color_s current_color;
    enum brushmodes mode;
    bool drawing;
    bool change;
} L;

static void get_tex_coords(ePointer_s pointer, int *row, int *col) {
    mat4 pose_inv = mat4_inv(canvas_pose());
    vec4 pose_pos = mat4_mul_vec(pose_inv, pointer.pos);

    *row = (0.5 - pose_pos.y) * canvas_image()->rows;
    *col = (pose_pos.x + 0.5) * canvas_image()->cols;
}

static bool dot_mode(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    bool in_image = c >= 0 && c < img->cols && r >= 0 && r < img->rows;
    if(in_image) {
        *image_pixel(img, layer, r, c) = L.current_color;
    }
    return in_image;
}

static bool free_mode(ePointer_s pointer) {
    if (pointer.action == E_POINTER_DOWN) {
        L.drawing = true;
    } else if (pointer.action != E_POINTER_MOVE) {
        L.drawing = false;
        return false;
    }
    if (!L.drawing)
        return false;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    bool in_image = c >= 0 && c < img->cols && r >= 0 && r < img->rows; 
    if(in_image) {
        *image_pixel(img, layer, r, c) = L.current_color;
    }
    return in_image;
}

static void fill_r(int r, int c, Color_s replace) {
	Image *img = canvas_image();
    int layer = canvas_current_layer;
    
    bool in_image = c >= 0 && c < img->cols && r >= 0 && r < img->rows;
    if(in_image) {
    	Color_s *p = image_pixel(img, layer, r, c);
    	if(color_equals(*p, replace)) {
    		*p = L.current_color;
    		fill_r(r, c-1, replace);
    		fill_r(r, c+1, replace);
    		fill_r(r-1, c, replace);
    		fill_r(r+1, c, replace);
    	}
    }
}

static bool fill_mode(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    bool in_image = c >= 0 && c < img->cols && r >= 0 && r < img->rows;
    if(in_image) {
        Color_s replace = *image_pixel(img, layer, r, c);
        if(color_equals(L.current_color, replace))
            return false;
        
        fill_r(r, c, replace);
    }
    return in_image;
}


void brush_pointer_event(ePointer_s pointer) {
    bool change = false;
    switch (L.mode) {
        case BRUSH_MODE_DOT:
            change = dot_mode(pointer);
            break;
        case BRUSH_MODE_FREE:
            change = free_mode(pointer);
            break;
        case BRUSH_MODE_FILL:
            change = fill_mode(pointer);
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
    L.current_color = COLOR_TRANSPARENT;
    L.mode = BRUSH_MODE_FREE;
}

void brush_set_color(Color_s col) {
    L.current_color = col;
}


enum brushmodes brush_get_mode() {
    return L.mode;
}

void brush_set_mode(enum brushmodes mode) {
    L.mode = mode;
    L.drawing = false;
}
