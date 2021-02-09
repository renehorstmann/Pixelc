#ifndef PIXELC_CAMERA_H
#define PIXELC_CAMERA_H

/*
 * PixelPerfect camera for hud elements (and background)
 */

#include <stdbool.h>
#include "mathc/types/float.h"


#define CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

typedef struct {
    mat4 p;
    mat4 p_inv;
} CameraMatrices_s;

extern CameraMatrices_s camera_matrices;
extern const float *camera_gl;



void camera_init();

void camera_update();

float camera_left();
float camera_right();
float camera_bottom();
float camera_top();

static float camera_width() {
    return -camera_left() + camera_right();
}

static float camera_height() {
    return -camera_bottom() + camera_top();
}

static bool camera_is_portrait_mode() {
    return camera_height() > camera_width();
}


#endif //PIXELC_CAMERA_H
