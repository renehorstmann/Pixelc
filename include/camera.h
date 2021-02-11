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

struct CameraGlobals_s {
    CameraMatrices_s matrices;
    const float *gl;
};
extern struct CameraGlobals_s camera;



void camera_init();

void camera_update();

float camera_real_pixel_per_pixel();

float camera_left();
float camera_right();
float camera_bottom();
float camera_top();

static float camera_width() {
    return -camera_left() + camera_right();
}

static float camera_height() {
    return -camera_top() + camera_bottom();
}

static bool camera_is_portrait_mode() {
    return camera_height() > camera_width();
}


#endif //PIXELC_CAMERA_H
