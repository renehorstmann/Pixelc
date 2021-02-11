#include "utilc/alloc.h"
#include "r/texture.h"
#include "u/pose.h"
#include "brush.h"
#include "brush_shape.h"

#define TEX_SIZE 4
#define TEX_ROWS (BRUSH_KERNEL_TEXTURE_SIZE * TEX_SIZE)
#define TEX_COLS (BRUSH_KERNEL_TEXTURE_SIZE * TEX_SIZE)
_Static_assert(TEX_SIZE * TEX_SIZE >= BRUSH_NUM_SHAPES, "wrong texture size");

static int pixel_idx(int k, int c, int r) {
    int row = (k / TEX_SIZE) * BRUSH_KERNEL_TEXTURE_SIZE + r;
    int col = (k % TEX_SIZE) * BRUSH_KERNEL_TEXTURE_SIZE + c;
    return row * TEX_COLS + col;
}

GLuint brush_shape_create_kernel_texture(Color_s bg, Color_s fg) {
    int size = TEX_COLS * TEX_ROWS;
    Color_s *img = New(Color_s, size);
    for(int i=0; i<size; i++)
        img[i] = bg;

    for (int k = 0; k < BRUSH_NUM_SHAPES; k++) {
        for (int r = 0; r < BRUSH_KERNEL_SIZE; r++) {
            for (int c = 0; c < BRUSH_KERNEL_SIZE; c++) {
                if (brush_shape.kernels[k][r][c])
                    img[pixel_idx(k, c, r)] = fg;
                else
                    img[pixel_idx(k, c, r)] = bg;
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

bool brush_shape_draw(int c, int r) {
    bool changed = false;
    for (int kr = 0; kr < BRUSH_KERNEL_SIZE; kr++) {
        int dr = r + kr - BRUSH_KERNEL_SIZE / 2;

        for (int kc = 0; kc < BRUSH_KERNEL_SIZE; kc++) {
            int dc = c + kc - BRUSH_KERNEL_SIZE / 2;

            if (brush_shape.kernels[brush.shape]
            [kr][kc]) {

                changed |= brush_draw_pixel(dc, dr);
            }
        }
    }
    return changed;
}

bool brush_shape_draw_dither(int c, int r, bool a) {
    bool changed = false;
    for (int kr = 0; kr < BRUSH_KERNEL_SIZE; kr++) {
        int dr = r + kr - BRUSH_KERNEL_SIZE / 2;

        for (int kc = 0; kc < BRUSH_KERNEL_SIZE; kc++) {
            int dc = c + kc - BRUSH_KERNEL_SIZE / 2;

            if (brush_shape.kernels[brush.shape]
            [kr][kc]) {

                if ((dc % 2 + dr % 2) % 2 == a ? 0 : 1)
                    changed |= brush_draw_pixel(dc, dr);
            }
        }
    }
    return changed;
}

