#ifndef PIXELC_IMAGE_H
#define PIXELC_IMAGE_H

#include "color.h"

typedef struct {
	int rows, cols;
	int layers;
	Color_s data[];
} Image;

Image *image_new(int rows, int cols, int layers);

void image_delete(Image *self);

Image *image_clone(const Image *from);

void image_copy(Image *self, const Image *from);

static Color_s *image_pixel(Image *self, int row, int col, int layer) {
	return &self->data[
	    layer * self->rows * self->cols
	    + row * self->cols
	    + col];
}

#endif //PIXELC_IMAGE_H
