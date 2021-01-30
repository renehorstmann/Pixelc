#ifndef PIXELC_HUD_CAMERA_H
#define PIXELC_HUD_CAMERA_H

#include <stdbool.h>
#include "mathc/types/float.h"


typedef struct {
    mat4 p;
    mat4 p_inv;
} HudCameraMatrices_s;

extern HudCameraMatrices_s hud_camera_matrices;
extern const float *hud_camera_gl;



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
