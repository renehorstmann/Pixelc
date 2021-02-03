#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "image.h"

extern int canvas_current_layer;
extern bool canvas_show_grid;

void canvas_init(int rows, int cols);

void canvas_update(float dtime);

void canvas_render();

mat4 canvas_pose();
Image *canvas_image();
int canvas_layers();

ivec2 canvas_get_uv(vec4 pointer_pos);

void canvas_clear();

void canvas_save();

void canvas_redo_image();

#endif //PIXELC_CANVAS_H
