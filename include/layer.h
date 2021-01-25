#ifndef PIXELC_LAYER_H
#define PIXELC_LAYER_H

#include "color.h"

typedef struct {
    color *data;
    uint8_t alpha;
} Layer;

void layer_init(Layer *self);

void layer_kill(Layer *self);

color *layer_pixel(Layer *self, int row, int col);

color *layer_pixel_index(Layer *self, int index);


#endif //PIXELC_LAYER_H
