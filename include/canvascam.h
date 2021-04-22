#ifndef PIXELC_CANVASCAM_H
#define PIXELC_CANVASCAM_H

/*
 * PixelPerfect canvas camera with view matrix.
 * To control the camera position and size
 */

#include <stdbool.h>
#include "mathc/types/float.h"


#define CANVAS_CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

struct CanvasCameraMatrices_s {
    mat4 v;
    mat4 v_inv;
    mat4 p;
    mat4 p_inv;
    mat4 vp;
    mat4 v_p_inv;   // v @ p_inv
};

struct CanvasCameraGlobals_s {
    struct CanvasCameraMatrices_s matrices;
    const float *gl;
};
extern struct CanvasCameraGlobals_s canvascam;


void canvascam_init();

void canvascam_update();

float canvascam_real_pixel_per_pixel();

float canvascam_left();

float canvascam_right();

float canvascam_bottom();

float canvascam_top();

static float canvascam_width() {
    return -canvascam_left() + canvascam_right();
}

static float canvascam_height() {
    return -canvascam_bottom() + canvascam_top();
}

static bool canvascam_is_portrait_mode() {
    return canvascam_height() > canvascam_width();
}

void canvascam_set_pos(float x, float y);

void canvascam_set_size(float size);

void canvascam_set_angle(float alpha);

#endif //PIXELC_CANVASCAM_H
