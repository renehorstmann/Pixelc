#include "r/texture.h"
#include "u/pose.h"
#include "u/image.h"
#include "rhc/error.h"
#include "rhc/allocator.h"
#include "brush.h"
#include "brushshape.h"

rTexture brushshape_create_kernel_texture(uColor_s bg, uColor_s fg) {
    uImage *img = u_image_new_empty(BRUSH_KERNEL_TEXTURE_SIZE, BRUSH_KERNEL_TEXTURE_SIZE, BRUSH_NUM_SHAPES);

    for(int l=0; l<img->layers; l++) {
        for(int i=0; i<img->rows*img->cols; i++) {
            *u_image_pixel_index(img, i, l) = bg;
        }
    }

    for (int k = 0; k < BRUSH_NUM_SHAPES; k++) {
        for (int r = 0; r < BRUSH_KERNEL_SIZE; r++) {
            for (int c = 0; c < BRUSH_KERNEL_SIZE; c++) {
                if (brushshape.kernels[k][r][c])
                    *u_image_pixel(img, c, r, k) = fg;
                else
                    *u_image_pixel(img, c, r, k) = bg;
            }
        }
    }
    rTexture tex = r_texture_new(BRUSH_KERNEL_TEXTURE_SIZE,
                                 BRUSH_KERNEL_TEXTURE_SIZE * BRUSH_NUM_SHAPES,
                                 1, BRUSH_NUM_SHAPES, img->data);
    u_image_delete(img);
    return tex;
}

bool brushshape_draw(int c, int r) {
    bool changed = false;
    for (int kr = 0; kr < BRUSH_KERNEL_SIZE; kr++) {
        int dr = r + kr - BRUSH_KERNEL_SIZE / 2;

        for (int kc = 0; kc < BRUSH_KERNEL_SIZE; kc++) {
            int dc = c + kc - BRUSH_KERNEL_SIZE / 2;

            if (brushshape.kernels[brush.shape]
            [kr][kc]) {

                changed |= brush_draw_pixel(dc, dr);
            }
        }
    }
    return changed;
}

bool brushshape_draw_dither(int c, int r, bool a) {
    bool changed = false;
    for (int kr = 0; kr < BRUSH_KERNEL_SIZE; kr++) {
        int dr = r + kr - BRUSH_KERNEL_SIZE / 2;

        for (int kc = 0; kc < BRUSH_KERNEL_SIZE; kc++) {
            int dc = c + kc - BRUSH_KERNEL_SIZE / 2;

            if (brushshape.kernels[brush.shape]
            [kr][kc]) {

                if ((dc % 2 + dr % 2) % 2 == a ? 0 : 1)
                    changed |= brush_draw_pixel(dc, dr);
            }
        }
    }
    return changed;
}

