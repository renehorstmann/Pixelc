#include <assert.h>
#include "mathc/sca/int.h"
#include "brushshape.h"
#include "brush.h"


//
// private
//

static uColor_s blend_color(uColor_s prev, uColor_s kernel, uColor_s color) {
    vec4 p = vec4_cast_from_uchar_1(prev.v);
    vec4 k = vec4_cast_from_uchar_1(kernel.v);
    vec4 c = vec4_cast_from_uchar_1(color.v);
      
    // kernel * color for each channel
    vec4 kc = vec4_scale_vec(k, c);
    
    // kernel sets the resulting opacity
    vec4 b = vec4_mix(p, kc, k.a);
    
    return ucvec4_cast_from_float_1(b.v);
}

static bool draw_pixel(Brush *self, int c, int r, uColor_s kernel_color) {
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    if (!u_image_contains(img, c, r))
        return false;

    const Selection *selection = self->in.selection_ref;
    if (selection && !selection_contains(selection, c, r))
        return false;

    uColor_s *pixel = u_image_pixel(img, c, r, layer);
    if (self->shading_active) {
        if (!u_color_equals(*pixel, self->secondary_color))
            return false;
    }
    
    *pixel = blend_color(*pixel, kernel_color, self->current_color);
    return true;
}

static void draw_kernel(Brush *self, int c, int r) {
   for(int kr=0; kr<self->kernel.rows; kr++) {
       // 'd'estination
       int dr = r - self->kernel.rows/2 + kr;
       for(int kc=0; kc<self->kernel.cols; kc++) {
           int dc = c - self->kernel.cols/2 + kc;
           
           uColor_s kernel_color = *u_image_pixel(self->kernel, kc, kr, 0);
           
           draw_pixel(self, dc, dr, kernel_color);
       } 
   } 
}

static void draw_kernel_dither(Brush *self, int c, int r, bool a) {
   for(int kr=0; kr<self->kernel.rows; kr++) {
       // 'd'estination
       int dr = r - self->kernel.rows/2 + kr;
       for(int kc=0; kc<self->kernel.cols; kc++) {
           int dc = c - self->kernel.cols/2 + kc;
           
           if ((dc % 2 + dr % 2) % 2 == a ? 0 : 1)
               continue;
           
           uColor_s kernel_color = *u_image_pixel(self->kernel, kc, kr, 0);
           
           draw_pixel(self, dc, dr, kernel_color);
       } 
   } 
}


//
// public
//

Brush *brush_new(Canvas *canvas) {
    Brush *self = rhc_calloc(sizeof *self);

    self->canvas_ref = canvas;
    
    self->brushmode = brushmode_new(self, canvas);

    self->current_color = U_COLOR_TRANSPARENT;
    self->secondary_color = U_COLOR_TRANSPARENT;
    self->mode = BRUSH_MODE_FREE;
    self->shape = 0;
    self->shading_active = false;
    
    self->kernel = u_image_new_empty(5, 5, 1);
    for(int i=0; i<25; i++)
        *u_image_pixel_index(self->kernel, i, 0) = (uColor_s) {{255, 255, 255, 255*i/25}};
    
    return self;
}

void brush_pointer_event(Brush *self, ePointer_s pointer) {
    if (pointer.id != 0)
        return;

    bool change = false;
    switch (self->mode) {
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER2:
            change = brushmode_free(self->brushmode, pointer);
            break;
        case BRUSH_MODE_DOT:
            change = brushmode_dot(self->brushmode, pointer);
            break;
        case BRUSH_MODE_FILL:
            change = brushmode_fill(self->brushmode, pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brushmode_fill(self->brushmode, pointer, true);
            break;
        case BRUSH_MODE_REPLACE:
            change = brushmode_replace(self->brushmode, pointer);
            break;
        default:
            log_wtf("brush unknown mode");
    }

    if (change)
        self->L.change = true;

    if (self->L.change && pointer.action == E_POINTER_UP) {
        self->L.change = false;
        canvas_save(self->canvas_ref);
    }

}

bool brush_draw_pixel(Brush *self, int c, int r) {
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    if (!u_image_contains(img, c, r))
        return false;

    const Selection *selection = self->in.selection_ref;
    if (selection && !selection_contains(selection, c, r))
        return false;

    uColor_s *pixel = u_image_pixel(img, c, r, layer);
    if (self->shading_active) {
        if (!u_color_equals(*pixel, self->secondary_color))
            return false;
    }

    *pixel = self->current_color;
    return true;
}


bool brush_draw(Brush *self, int c, int r) {
    
    /*
    if (self->mode == BRUSH_MODE_DITHER) {
        draw_kernel_dither(self, c, r, true);
        return true;
    }
    if (self->mode == BRUSH_MODE_DITHER2) {
        draw_kernel_dither(self, c, r, false);
        return true;
    }
    draw_kernel(self, c, r);
    return true;
    //*/
    
    //*
    if (self->mode == BRUSH_MODE_DITHER)
        return brushshape_draw_dither(self, c, r, true);
    if (self->mode == BRUSH_MODE_DITHER2)
        return brushshape_draw_dither(self, c, r, false);
    return brushshape_draw(self, c, r);
    //*/
}

void brush_abort_current_draw(Brush *self) {
    log_info("brush: abort_current_draw");
    if (self->L.change) {
        canvas_reload(self->canvas_ref);
        brushmode_reset(self->brushmode); // sets drawing to false
        self->L.change = false;
    }
}

void brush_clear(Brush *self) {
    log_info("brush: clear");
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    const Selection *selection = self->in.selection_ref;
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            if (selection && !selection_contains(selection, c, r))
                continue;

            *u_image_pixel(img, c, r, layer) = U_COLOR_TRANSPARENT;
        }
    }
    canvas_save(self->canvas_ref);
}

void brush_reset_kernel_files(Brush *self) {
    
}
