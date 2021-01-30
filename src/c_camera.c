#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "c_camera.h"


CanvasCameraMatrices_s c_camera_matrices;
const float *c_camera_gl;

static struct {
    float width, height;
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
    
    if (wnd_width > wnd_height) {
        L.height = 200;
        L.width = 200 * wnd_width / wnd_height;
    } else {
        L.width = 200;
        L.height = 200 * wnd_height / wnd_width;
    }

    c_camera_matrices.v_inv = mat4_inv(c_camera_matrices.v);

    c_camera_matrices.p = mat4_camera_ortho(-L.width / 2, L.width / 2, -L.height / 2, L.height / 2, -1, 1);
    c_camera_matrices.p_inv = mat4_inv(c_camera_matrices.p);

    c_camera_matrices.vp = mat4_mul_mat(c_camera_matrices.p, c_camera_matrices.v_inv);
    
    c_camera_matrices.v_p_inv = mat4_mul_mat(c_camera_matrices.v, c_camera_matrices.p_inv);
}


float c_camera_width() {
    return L.width;
}
float c_camera_height() {
    return L.height;
}

void c_camera_set_pos(float x, float y) {
    u_pose_set_xy(&c_camera_matrices.v, x, y);
}

void c_camera_set_angle(float alpha) {
    u_pose_set_angle(&c_camera_matrices.v, alpha);
}
