#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "mathc/types/float.h"
#include "image.h"

extern int canvas_current_layer;

void canvas_init(int rows, int cols);

void canvas_update(float dtime);

void canvas_render();

mat4 canvas_pose();
Image *canvas_image();
int canvas_layers();

void canvas_redo_image();

#endif //PIXELC_CANVAS_H
