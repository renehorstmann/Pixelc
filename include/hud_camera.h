#ifndef PIXELC_HUD_CAMERA_H
#define PIXELC_HUD_CAMERA_H


#include "mathc/types/float.h"

extern mat4 hud_camera_p;
extern mat4 hud_camera_p_inv;

void hud_camera_init();

void hud_camera_update();

float hud_camera_width();
float hud_camera_height();

#endif //PIXELC_HUD_CAMERA_H
