#include "utilc/alloc.h"
#include "brush.h"
#include "brush_shape.h"

static int pixel_idx(int kernel, int row, int col) {
    return row * BRUSH_NUM_SHAPES * BRUSH_KERNEL_SIZE
           + kernel * BRUSH_KERNEL_SIZE
           + col;
}

Color_s *brush_shape_kernel_image_on_heap(Color_s bg, Color_s fg) {
    Color_s *img = New(Color_s, BRUSH_NUM_SHAPES * BRUSH_KERNEL_SIZE * BRUSH_KERNEL_SIZE);

    for (int k = 0; k < BRUSH_NUM_SHAPES; k++) {
        for (int r = 0; r < BRUSH_KERNEL_SIZE; r++) {
            for (int c = 0; c < BRUSH_KERNEL_SIZE; c++) {
                if (brush_shape_kernels[k][r][c])
                    img[pixel_idx(k, r, c)] = fg;
                else
                    img[pixel_idx(k, r, c)] = bg;
            }
        }
    }
    return img;
}

bool brush_shape_draw(int x, int y) {
    bool changed = false;
    for (int ky = 0; ky < BRUSH_KERNEL_SIZE; ky++) {
        int dy = y + ky - BRUSH_KERNEL_SIZE / 2;

        for (int kx = 0; kx < BRUSH_KERNEL_SIZE; kx++) {
            int dx = x + kx - BRUSH_KERNEL_SIZE / 2;

            if (brush_shape_kernels[brush_shape]
            [ky][kx]) {

                changed |= brush_draw_pixel(dx, dy);
            }
        }
    }
    return changed;
}

bool brush_shape_draw_dither(int x, int y, bool a) {
    bool changed = false;
    for (int ky = 0; ky < BRUSH_KERNEL_SIZE; ky++) {
        int dy = y + ky - BRUSH_KERNEL_SIZE / 2;

        for (int kx = 0; kx < BRUSH_KERNEL_SIZE; kx++) {
            int dx = x + kx - BRUSH_KERNEL_SIZE / 2;

            if (brush_shape_kernels[brush_shape]
            [ky][kx]) {

                if ((dx % 2 + dy % 2) % 2 == a ? 0 : 1)
                    changed |= brush_draw_pixel(dx, dy);
            }
        }
    }
    return changed;
}

