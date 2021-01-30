#ifndef PIXELC_C_CAMERA_H
#define PIXELC_C_CAMERA_H

/*
 * PixelPerfect canvas camera with view matrix.
 * To control the camera position and size
 */

#include <stdbool.h>
#include "mathc/types/float.h"


#define C_CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

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


float c_camera_left();
float c_camera_right();
float c_camera_bottom();
float c_camera_top();

static float c_camera_width() {
    return -c_camera_left() + c_camera_right();
}

static float c_camera_height() {
    return -c_camera_bottom() + c_camera_top();
}

static bool c_camera_is_portrait_mode() {
    return c_camera_height() > c_camera_width();
}

void c_camera_set_pos(float x, float y);

void c_camera_set_angle(float alpha);

#endif //PIXELC_C_CAMERA_H
