#ifndef PIXELC_IMAGE_H
#define PIXELC_IMAGE_H

#include <stdbool.h>
#include "color.h"

typedef struct {
    int layers;
	int rows, cols;
	Color_s data[];
} Image;

Image *image_new_empty(int layers, int rows, int cols);

Image *image_new_zeros(int layers, int rows, int cols);

void image_delete(Image *self);

Image *image_clone(const Image *from);

bool image_copy(Image *self, const Image *from);

static Color_s *image_pixel(Image *self, int layer, int row, int col) {
	return &self->data[
	    layer * self->rows * self->cols
	    + row * self->cols
	    + col];
}

static Color_s *image_pixel_index(Image *self, int layer, int index) {
    return image_pixel(self, layer, 0, index);
}

static Color_s *image_layer(Image *self, int layer) {
    return image_pixel(self, layer, 0, 0);
}

#endif //PIXELC_IMAGE_H
