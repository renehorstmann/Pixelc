#ifndef PIXELC_HUD_CAMERA_H
#define PIXELC_HUD_CAMERA_H

/*
 * PixelPerfect camera for hud elements (and background)
 */

#include <stdbool.h>
#include "mathc/types/float.h"


#define HUD_CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

typedef struct {
    mat4 p;
    mat4 p_inv;
} HudCameraMatrices_s;

extern HudCameraMatrices_s hud_camera_matrices;
extern const float *hud_camera_gl;



void hud_camera_init();

void hud_camera_update();

float hud_camera_left();
float hud_camera_right();
float hud_camera_bottom();
float hud_camera_top();

static float hud_camera_width() {
    return -hud_camera_left() + hud_camera_right();
}

static float hud_camera_height() {
    return -hud_camera_bottom() + hud_camera_top();
}

static bool hud_camera_is_portrait_mode() {
    return hud_camera_height() > hud_camera_width();
}


#endif //PIXELC_HUD_CAMERA_H
