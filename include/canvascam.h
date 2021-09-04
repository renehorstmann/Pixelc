#ifndef PIXELC_CANVASCAM_H
#define PIXELC_CANVASCAM_H

/*
 * PixelPerfect canvas camera with view matrix.
 * To control the camera position and size
 */

#include <stdbool.h>
#include "mathc/types/float.h"


#define CANVASCAM_SIZE 180 // *4=720; *6=1080; *8=1440

typedef struct {
    mat4 v;         // view / pose of the canvascam in 3d space
    mat4 v_inv;     // inv(v)
    mat4 p;         // projection of the canvascam (perspective / orthogonal)
    mat4 p_inv;     // inv(p)
    mat4 vp;        // p @ v_inv   used for render objects (ro)
    mat4 v_p_inv;   // v @ p_inv   used for input
} CanvasCamMatrices_s;

typedef struct {
    CanvasCamMatrices_s matrices;

    struct {
        float real_pixel_per_pixel;
        float left, right, bottom, top;
    } RO;   // read only
} CanvasCam_s;

CanvasCam_s *canvascam_new();

void canvascam_update(CanvasCam_s *self, int wnd_width, int wnd_height);

void canvascam_set_pos(CanvasCam_s *self, float x, float y);

void canvascam_set_size(CanvasCam_s *self, float size);

void canvascam_set_angle(CanvasCam_s *self, float alpha);

static float canvascam_width(const CanvasCam_s *self) {
    return -self->RO.left + self->RO.right;
}

static float canvascam_height(const CanvasCam_s *self) {
    return -self->RO.bottom + self->RO.top;
}

static bool canvascam_is_portrait_mode(const CanvasCam_s *self) {
    return canvascam_height(self) > canvascam_width(self);
}

#endif //PIXELC_CANVASCAM_H
