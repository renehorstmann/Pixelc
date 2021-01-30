#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "c_camera.h"


CanvasCameraMatrices_s c_camera_matrices;
const float *c_camera_gl;

static struct {
    float left, right, bottom, top;
} L;


void c_camera_init() {
    c_camera_gl = &c_camera_matrices.vp.m00;
    c_camera_matrices.v = mat4_eye();
    c_camera_matrices.v_inv = mat4_eye();
    c_camera_matrices.p = mat4_eye();
    c_camera_matrices.p_inv = mat4_eye();
    c_camera_matrices.vp = mat4_eye();
    c_camera_matrices.v_p_inv = mat4_eye();
}

void c_camera_update() {
    int wnd_width = e_window_size[0];
    int wnd_height = e_window_size[1];

    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    float real_pixel_per_pixel = floorf(smaller_size / C_CAMERA_SIZE);

    float width_2 = wnd_width / (2 * real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    L.left = -floorf(width_2);
    L.top = floorf(height_2);
    L.right = width_2 + (width_2 - floorf(width_2));
    L.bottom = -height_2 - (height_2 - floorf(height_2));

    c_camera_matrices.p = mat4_camera_ortho(L.left, L.right, L.bottom, L.top, -1, 1);

    c_camera_matrices.v_inv = mat4_inv(c_camera_matrices.v);
    c_camera_matrices.p_inv = mat4_inv(c_camera_matrices.p);

    c_camera_matrices.vp = mat4_mul_mat(c_camera_matrices.p, c_camera_matrices.v_inv);
    
    c_camera_matrices.v_p_inv = mat4_mul_mat(c_camera_matrices.v, c_camera_matrices.p_inv);
}



float c_camera_left() {
    return L.left;
}
float c_camera_right() {
    return L.right;
}
float c_camera_bottom() {
    return L.bottom;
}
float c_camera_top() {
    return L.top;
}

void c_camera_set_pos(float x, float y) {
    u_pose_set_xy(&c_camera_matrices.v, x, y);
}

void c_camera_set_angle(float alpha) {
    u_pose_set_angle(&c_camera_matrices.v, alpha);
}
