#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>
#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "u/image.h"

#define CANVAS_MAX_LAYERS 16

struct CanvasGlobals_s {
    int current_layer;
    bool show_grid;
    float alpha;
    const char *default_image_file;
    const char *default_import_file;
};
extern struct CanvasGlobals_s canvas;

void canvas_init(int cols, int rows, int layers, int grid_cols, int grid_rows);

void canvas_update(float dtime);

void canvas_render();

mat4 canvas_pose();

uImage *canvas_image();

ivec2 canvas_get_cr(vec4 pointer_pos);

void canvas_clear();

void canvas_save();

void canvas_redo_image();

#endif //PIXELC_CANVAS_H
