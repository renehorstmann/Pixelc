#ifndef PIXELC_BRUSH_SHAPE_H
#define PIXELC_BRUSH_SHAPE_H

#include <stdbool.h>
#include "color.h"

#define BRUSH_KERNEL_SIZE 7
#define BRUSH_NUM_SHAPES 16

extern const char brush_shape_kernels
        [BRUSH_NUM_SHAPES]
        [BRUSH_KERNEL_SIZE][BRUSH_KERNEL_SIZE];
        
Color_s *brush_shape_kernel_image_on_heap(Color_s bg, Color_s fg);

bool brush_shape_draw(int x, int y);

bool brush_shape_draw_dither(int x, int y, bool a);

#endif //PIXELC_BRUSH_SHAPE_H
