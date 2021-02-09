#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "camera.h"


CameraMatrices_s camera_matrices;
const float *camera_gl;

static struct {
    float real_pixel_per_pixel;
    float left, right, bottom, top;
} L;


void camera_init() {
    assert(CAMERA_SIZE % 2 == 0 && "CAMERA_SIZE must be even");
    camera_gl = &camera_matrices.p.m00;
    camera_matrices.p = mat4_eye();
    camera_matrices.p_inv = mat4_eye();

    camera_update();
}

void camera_update() {
    int wnd_width = e_window_size.x;
    int wnd_height = e_window_size.y;


    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    L.real_pixel_per_pixel = floorf(smaller_size / CAMERA_SIZE);

    float width_2 = wnd_width / (2 * L.real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * L.real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    L.left = -floorf(width_2);
    L.top = floorf(height_2);
    L.right = width_2 + (width_2 - floorf(width_2));
    L.bottom = -height_2 - (height_2 - floorf(height_2));

    camera_matrices.p = mat4_camera_ortho(L.left, L.right, L.bottom, L.top, -1, 1);
    camera_matrices.p_inv = mat4_inv(camera_matrices.p);
}

float camera_real_pixel_per_pixel() {
    return L.real_pixel_per_pixel;
}

float camera_left() {
    return L.left;
}
float camera_right() {
    return L.right;
}
float camera_bottom() {
    return L.bottom;
}
float camera_top() {
    return L.top;
}
