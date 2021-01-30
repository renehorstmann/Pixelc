#ifndef PIXELC_C_CAMERA_H
#define PIXELC_C_CAMERA_H

#include <stdbool.h>
#include "mathc/types/float.h"


typedef struct {
    mat4 v;
    mat4 v_inv;
    mat4 p;
    mat4 p_inv;
    mat4 vp;
    mat4 v_p_inv;   // v @ p_inv
} CanvasCameraMatrices_s;

extern CanvasCameraMatrices_s c_camera_matrices;
extern const float *c_camera_gl;


void c_camera_init();

void c_camera_update();

float c_camera_width();
float c_camera_height();

static bool c_camera_is_portrait_mode() {
    return c_camera_height() > c_camera_width();
}

static float c_camera_top() {
    return +c_camera_height() / 2;
}

static float c_camera_bottom() {
    return -c_camera_height() / 2;
}

static float c_camera_left() {
    return -c_camera_width() / 2;
}

static float c_camera_right() {
    return +c_camera_width() / 2;
}

void c_camera_set_pos(float x, float y);

void c_camera_set_angle(float alpha);

#endif //PIXELC_C_CAMERA_H
