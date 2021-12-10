#ifndef PIXELC_CAMERA_H
#define PIXELC_CAMERA_H

/*
 * PixelPerfect camera with view matrix.
 * To control the camera position and size
 */

#include <stdbool.h>
#include "mathc/types/float.h"
#include "mathc/types/int.h"


#define CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

typedef struct {
    mat4 p;         // projection of the camera (perspective / orthogonal)
    mat4 p_inv;     // inv(p)
} CameraMatrices_s;

typedef struct {
    CameraMatrices_s matrices;

    struct {
        float scale;    // units per pixel
        float left, right, bottom, top;
    } RO;   // read only
} Camera_s;

Camera_s *camera_new();

void camera_update(Camera_s *self, ivec2 window_size);

static float camera_width(const Camera_s *self) {
    return -self->RO.left + self->RO.right;
}

static float camera_height(const Camera_s *self) {
    return -self->RO.bottom + self->RO.top;
}

static bool camera_is_portrait_mode(const Camera_s *self) {
    return camera_height(self) > camera_width(self);
}

#endif //PIXELC_CAMERA_H
