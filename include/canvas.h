#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "mathc/types/float.h"
#include "layer.h"

void canvas_init();

mat4 canvas_pose();

int canvas_cols();
int canvas_rows();

Layer *canvas_current_layer();

void canvas_update(float dtime);

void canvas_render();

#endif //PIXELC_CANVAS_H
