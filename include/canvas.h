#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "image.h"

struct CanvasGlobals_s {
    int current_layer;
    bool show_grid;
    float alpha;
};
extern struct CanvasGlobals_s canvas;

void canvas_init(int cols, int rows, int layers, int grid_cols, int grid_rows);

void canvas_update(float dtime);

void canvas_render();

mat4 canvas_pose();
Image *canvas_image();

ivec2 canvas_get_cr(vec4 pointer_pos);

void canvas_clear();

void canvas_save();

void canvas_redo_image();

#endif //PIXELC_CANVAS_H
