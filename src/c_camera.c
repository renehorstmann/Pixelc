#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "e/input.h"
#include "c_camera.h"


mat4 c_camera_v;
mat4 c_camera_v_inv;
mat4 c_camera_p;
mat4 c_camera_p_inv;
mat4 c_camera_vp;
//mat4 c_camera_vp_inv;


void c_camera_init() {
    c_camera_v = mat4_eye();
    c_camera_v_inv = mat4_eye();
    c_camera_p = mat4_eye();
    c_camera_p_inv = mat4_eye();
    c_camera_vp = mat4_eye();
//    c_camera_vp_inv = mat4_eye();
}

void c_camera_update() {
    int wnd_width = e_window_size[0];
    int wnd_height = e_window_size[1];
    
    float width, height;
    if (wnd_width > wnd_height) {
        height = 200;
        width = 200 * wnd_width / wnd_height;
    } else {
        width = 200;
        height = 200 * wnd_height / wnd_width;
    }

    c_camera_v_inv = mat4_inv(c_camera_v);

    c_camera_p = mat4_camera_ortho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
    c_camera_p_inv = mat4_inv(c_camera_p);

    c_camera_vp = mat4_mul_mat(c_camera_p, c_camera_v_inv);
//    c_camera_vp_inv = mat4_inv(c_camera_vp);
}

void c_camera_set_pos(float x, float y) {
    u_pose_set_xy(&c_camera_v, x, y);
}

void c_camera_set_angle(float alpha) {
    u_pose_set_angle(&c_camera_v, alpha);
}
