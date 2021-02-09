#include "utilc/alloc.h"
#include "brush.h"
#include "brush_shape.h"

static int pixel_idx(int kernel, int row, int col) {
	return row * BRUSH_NUM_SHAPES * BRUSH_KERNEL_SIZE
	        + kernel * BRUSH_KERNEL_SIZE
	        + col;
}

Color_s *brush_shape_kernel_image_on_heap(Color_s bg, Color_s fg) {
    Color_s *img = New(Color_s, 
        BRUSH_NUM_SHAPES
        *BRUSH_KERNEL_SIZE
        *BRUSH_KERNEL_SIZE); 
	
	for(int k=0; k<BRUSH_NUM_SHAPES; k++) {
		for(int r=0; r<BRUSH_KERNEL_SIZE; r++) {
			for(int c=0; c<BRUSH_KERNEL_SIZE; c++) {
				if(brush_shape_kernels[k][r][c])
					img[pixel_idx(k, r, c)] = fg;
				else
					img[pixel_idx(k, r, c)] = bg;
			}
		}
	}
	return img;
}

// old:

bool brush_shape_dot(float x, float y) {
	bool changed = false;
	for(int dy=y-brush_size; dy<=y+brush_size; dy++) {
		for(int dx=x-brush_size; dx<=x+brush_size; dx++) {
			changed |= brush_draw_pixel(dx, dy);
		}
	}
	return changed;
}

bool brush_shape_dither(float x, float y, bool a) {
	bool changed = false;
	for(int dy=y-brush_size; dy<=y+brush_size; dy++) {
		for(int dx=x-brush_size; dx<=x+brush_size; dx++) {
			if((dx%2 + dy%2)%2 == a? 0 : 1)
			    changed |= brush_draw_pixel(dx, dy);
		}
	}
	return changed;
}

