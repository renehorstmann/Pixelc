#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "mathc/types/float.h"
#include "layer.h"

void canvas_init(int rows, int cols);

mat4 canvas_pose();

int canvas_cols();
int canvas_rows();

Layer *canvas_layers();
int canvas_size();
int canvas_current();
Layer *canvas_current_layer();

void canvas_set_layer(Layer layer, int index);
void canvas_set_layers(const Layer *layer, int size);
void canvas_set_current(int current);

void canvas_update(float dtime);

void canvas_render();

#endif //PIXELC_CANVAS_H
