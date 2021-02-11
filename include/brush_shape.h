#ifndef PIXELC_BRUSH_SHAPE_H
#define PIXELC_BRUSH_SHAPE_H

#include <stdbool.h>
#include "r/core.h"
#include "color.h"

#define BRUSH_KERNEL_SIZE 7
#define BRUSH_NUM_SHAPES 16

#define BRUSH_KERNEL_TEXTURE_SIZE 8

struct BrushShapeGlobals_s {
    const char kernels
            [BRUSH_NUM_SHAPES]
            [BRUSH_KERNEL_SIZE][BRUSH_KERNEL_SIZE];
};
extern struct BrushShapeGlobals_s brush_shape;
        
GLuint brush_shape_create_kernel_texture(Color_s bg, Color_s fg);
mat4 brush_shape_kernel_texture_uv(int kernel);

bool brush_shape_draw(int r, int c);

bool brush_shape_draw_dither(int r, int c, bool a);

#endif //PIXELC_BRUSH_SHAPE_H
