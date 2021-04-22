#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "canvascam.h"


struct CanvasCameraGlobals_s canvascam;

static struct {
    float real_pixel_per_pixel;
    float left, right, bottom, top;
} L;


void canvascam_init() {
    assert(CANVAS_CAMERA_SIZE % 2 == 0 && "CANVAS_CAMERA_SIZE must be even");
    canvascam.gl = &canvascam.matrices.vp.m00;
    canvascam.matrices.v = mat4_eye();
    canvascam.matrices.v_inv = mat4_eye();
    canvascam.matrices.p = mat4_eye();
    canvascam.matrices.p_inv = mat4_eye();
    canvascam.matrices.vp = mat4_eye();
    canvascam.matrices.v_p_inv = mat4_eye();

    canvascam_update();
}

void canvascam_update() {
    int wnd_width = e_window.size.x;
    int wnd_height = e_window.size.y;

    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    L.real_pixel_per_pixel = floorf(smaller_size / CANVAS_CAMERA_SIZE);

    float width_2 = wnd_width / (2 * L.real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * L.real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    L.left = -floorf(width_2);
    L.top = floorf(height_2);
    L.right = width_2 + (width_2 - floorf(width_2));
    L.bottom = -height_2 - (height_2 - floorf(height_2));

    canvascam.matrices.p = mat4_camera_ortho(L.left, L.right, L.bottom, L.top, -1, 1);

    canvascam.matrices.v_inv = mat4_inv(canvascam.matrices.v);
    canvascam.matrices.p_inv = mat4_inv(canvascam.matrices.p);

    canvascam.matrices.vp = mat4_mul_mat(canvascam.matrices.p, canvascam.matrices.v_inv);

    canvascam.matrices.v_p_inv = mat4_mul_mat(canvascam.matrices.v, canvascam.matrices.p_inv);
}

float canvascam_real_pixel_per_pixel() {
    return L.real_pixel_per_pixel;
}

float canvascam_left() {
    return L.left;
}

float canvascam_right() {
    return L.right;
}

float canvascam_bottom() {
    return L.bottom;
}

float canvascam_top() {
    return L.top;
}

void canvascam_set_pos(float x, float y) {
    u_pose_set_xy(&canvascam.matrices.v, x, y);
}

void canvascam_set_size(float size) {
    u_pose_set_size(&canvascam.matrices.v, size, size);
}

void canvascam_set_angle(float alpha) {
    u_pose_set_angle(&canvascam.matrices.v, alpha);
}
