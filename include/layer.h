#ifndef PIXELC_LAYER_H
#define PIXELC_LAYER_H

#include "color.h"

typedef struct {
    color *data;
    int rows, cols;
    uint8_t alpha;
} Layer;

void layer_init(Layer *self, int rows, int cols);

void layer_kill(Layer *self);

color *layer_pixel(Layer *self, int row, int col);


#endif //PIXELC_LAYER_H
