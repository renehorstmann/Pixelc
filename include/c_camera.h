#ifndef PIXELC_C_CAMERA_H
#define PIXELC_C_CAMERA_H

#include "mathc/types/float.h"

extern mat4 camera_v;
extern mat4 camera_v_inv;
extern mat4 camera_p;
extern mat4 camera_p_inv;
extern mat4 camera_vp;
//extern mat4 camera_vp_inv;

void camera_init();

void camera_update();

void camera_set_pos(float x, float y);

void camera_set_angle(float alpha);

#endif //PIXELC_C_CAMERA_H
