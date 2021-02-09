#ifndef PIXELC_CANVAS_CAMERA_H
#define PIXELC_CANVAS_CAMERA_H

/*
 * PixelPerfect canvas camera with view matrix.
 * To control the camera position and size
 */

#include <stdbool.h>
#include "mathc/types/float.h"


#define CANVAS_CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440

typedef struct {
    mat4 v;
    mat4 v_inv;
    mat4 p;
    mat4 p_inv;
    mat4 vp;
    mat4 v_p_inv;   // v @ p_inv
} CanvasCameraMatrices_s;

extern CanvasCameraMatrices_s canvas_camera_matrices;
extern const float *canvas_camera_gl;


void canvas_camera_init();

void canvas_camera_update();


float canvas_camera_left();
float canvas_camera_right();
float canvas_camera_bottom();
float canvas_camera_top();

static float canvas_camera_width() {
    return -canvas_camera_left() + canvas_camera_right();
}

static float canvas_camera_height() {
    return -canvas_camera_bottom() + canvas_camera_top();
}

static bool canvas_camera_is_portrait_mode() {
    return canvas_camera_height() > canvas_camera_width();
}

void canvas_camera_set_pos(float x, float y);

void canvas_camera_set_size(float size);

void canvas_camera_set_angle(float alpha);

#endif //PIXELC_CANVAS_CAMERA_H
