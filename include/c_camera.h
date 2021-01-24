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

void c_camera_set_pos(float x, float y);

void c_camera_set_angle(float alpha);

#endif //PIXELC_C_CAMERA_H
