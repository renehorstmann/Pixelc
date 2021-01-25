#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "color.h"
#include "mathc/types/float.h"

void canvas_init();

mat4 canvas_get_pose();

int canvas_get_rows();
int canvas_get_cols();

void canvas_set_color(int x, int y, color c);

void canvas_update(float dtime);

void canvas_render();

#endif //PIXELC_CANVAS_H
