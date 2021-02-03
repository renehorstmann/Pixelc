#ifndef PIXELC_IMAGE_H
#define PIXELC_IMAGE_H

#include <stdbool.h>
#include <mathc/types/int.h>
#include "color.h"

typedef struct {
    int layers;
	int rows, cols;
	Color_s data[];
} Image;

Image *image_new_empty(int layers, int rows, int cols);

Image *image_new_zeros(int layers, int rows, int cols);

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

static Color_s *image_pixel(Image *self, int layer, int row, int col) {
	return &self->data[
	    layer * self->rows * self->cols
	    + row * self->cols
	    + col];
}

static Color_s *image_pixel_uv(Image *self, int layer, ivec2 uv) {
	return image_pixel(self, layer, uv.y, uv.x);
}

static Color_s *image_pixel_index(Image *self, int layer, int index) {
    return image_pixel(self, layer, 0, index);
}

static Color_s *image_layer(Image *self, int layer) {
    return image_pixel(self, layer, 0, 0);
}

static bool image_contains_uv(const Image *img, ivec2 uv) {
	return uv.x >= 0 && uv.x < img->cols 
	    && uv.y >= 0 && uv.y < img->rows;
}

#endif //PIXELC_IMAGE_H
