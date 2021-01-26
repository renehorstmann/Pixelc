#ifndef PIXELC_HUD_CAMERA_H
#define PIXELC_HUD_CAMERA_H


#include "mathc/types/float.h"

extern mat4 hud_camera_p;
extern mat4 hud_camera_p_inv;

void hud_camera_init();

void hud_camera_update();

float hud_camera_width();

float hud_camera_height();

static bool hud_camera_is_portrait_mode() {
    return hud_camera_height() > hud_camera_width();
}

static float hud_camera_top() {
    return +hud_camera_height() / 2;
}

static float hud_camera_bottom() {
    return -hud_camera_height() / 2;
}

static float hud_camera_left() {
    return -hud_camera_width() / 2;
}

static float hud_camera_right() {
    return +hud_camera_width() / 2;
}


#endif //PIXELC_HUD_CAMERA_H
