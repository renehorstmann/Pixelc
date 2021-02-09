#include "utilc/alloc.h"
#include "r/texture.h"
#include "u/pose.h"
#include "brush.h"
#include "brush_shape.h"

#define TEX_SIZE 4
#define TEX_ROWS (BRUSH_KERNEL_TEXTURE_SIZE * TEX_SIZE)
#define TEX_COLS (BRUSH_KERNEL_TEXTURE_SIZE * TEX_SIZE)
_Static_assert(TEX_SIZE * TEX_SIZE >= BRUSH_NUM_SHAPES, "wrong texture size");

static int pixel_idx(int k, int y, int x) {
    int row = (k / TEX_SIZE) * BRUSH_KERNEL_TEXTURE_SIZE + y;
    int col = (k % TEX_SIZE) * BRUSH_KERNEL_TEXTURE_SIZE + x;
    return row * TEX_COLS + col;
}

GLuint brush_shape_create_kernel_texture(Color_s bg, Color_s fg) {
    int size = TEX_COLS * TEX_ROWS;
    Color_s *img = New(Color_s, size);
    for(int i=0; i<size; i++)
        img[i] = bg;

    for (int k = 0; k < BRUSH_NUM_SHAPES; k++) {
        for (int x = 0; x < BRUSH_KERNEL_SIZE; x++) {
            for (int y = 0; y < BRUSH_KERNEL_SIZE; y++) {
                if (brush_shape_kernels[k][y][x])
                    img[pixel_idx(k, y, x)] = fg;
                else
                    img[pixel_idx(k, y, x)] = bg;
            }
        }
    }
    GLuint tex = r_texture_init(TEX_COLS, TEX_ROWS, img);
    free(img);
    return tex;
}

mat4 brush_shape_kernel_texture_uv(int kernel) {
    int row = kernel / TEX_SIZE;
    int col = kernel % TEX_SIZE;
    float step = 1.0 / TEX_SIZE;
    mat4 uv = mat4_eye();
    u_pose_set(&uv, col * step, row * step, step, step, 0);
    return uv;
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

