#ifndef PIXELC_IMAGE_H
#define PIXELC_IMAGE_H

#include "color.h"

typedef struct {
	Color_s *data;
	int rows, cols;
	int layers;
} Image;

void image_init(Image *self, int rows, int cols, int layers);

void image_kill(Image *self);

void image_clone(Image *self, Image from);

static Color_s *image_pixel(Image self, int row, int col, int layer) {
	return &self.data[
	    layer * self.rows * self.cols
	    + row * self.cols
	    + col];
}

#endif //PIXELC_IMAGE_H
