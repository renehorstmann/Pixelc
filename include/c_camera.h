#ifndef PIXELC_C_CAMERA_H
#define PIXELC_C_CAMERA_H

#include "mathc/types/float.h"

extern mat4 c_camera_v;
extern mat4 c_camera_v_inv;
extern mat4 c_camera_p;
extern mat4 c_camera_p_inv;
extern mat4 c_camera_vp;
//extern mat4 c_camera_vp_inv;

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
