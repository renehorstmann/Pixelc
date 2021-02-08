#include "brush.h"
#include "brush_shape.h"

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

