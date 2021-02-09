#ifndef PIXELC_BRUSH_SHAPE_H
#define PIXELC_BRUSH_SHAPE_H

#include <stdbool.h>

#define BRUSH_KERNEL_SIZE 7
#define BRUSH_NUM_SHAPES 22

extern const char brush_shape_kernels
        [BRUSH_NUM_SHAPES]
        [BRUSH_KERNEL_SIZE][BRUSH_KERNEL_SIZE];

bool brush_shape_dot(float x, float y);

bool brush_shape_dither(float x, float y, bool a);

#endif //PIXELC_BRUSH_SHAPE_H
