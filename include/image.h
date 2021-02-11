#ifndef PIXELC_IMAGE_H
#define PIXELC_IMAGE_H

#include <stdbool.h>
#include "color.h"

typedef struct {
    int layers;
	int rows, cols;
	Color_s data[];
} Image;

Image *image_new_empty(int layers, int cols, int rows);

Image *image_new_zeros(int layers, int cols, int rows);

Image *image_new_clone(const Image *from);

void image_delete(Image *self);

bool image_copy(Image *self, const Image *from);

bool image_equals(const Image *self, const Image *from);

static size_t image_data_size(const Image *self) {
	return sizeof(Color_s) * self->layers * self->rows * self->cols;
}

static size_t image_full_size(const Image *self) {
	return sizeof(Image) + image_data_size(self);
}

static Color_s *image_pixel(Image *self, int layer, int c, int r) {
	return &self->data[
	    layer * self->rows * self->cols
	    + r * self->cols
	    + c];
}

static Color_s *image_pixel_index(Image *self, int layer, int index) {
    return image_pixel(self, layer, 0, index);
}

static Color_s *image_layer(Image *self, int layer) {
    return image_pixel(self, layer, 0, 0);
}

static bool image_contains(const Image *img, int c, int r) {
	return c >= 0 && c < img->cols 
	    && r >= 0 && r < img->rows;
}

#endif //PIXELC_IMAGE_H
