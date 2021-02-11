#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "canvas_camera.h"


struct CanvasCameraGlobals_s canvas_camera;

static struct {
    float real_pixel_per_pixel;
    float left, right, bottom, top;
} L;


void canvas_camera_init() {
    canvas_camera.gl = &canvas_camera.matrices.vp.m00;
    canvas_camera.matrices.v = mat4_eye();
    canvas_camera.matrices.v_inv = mat4_eye();
    canvas_camera.matrices.p = mat4_eye();
    canvas_camera.matrices.p_inv = mat4_eye();
    canvas_camera.matrices.vp = mat4_eye();
    canvas_camera.matrices.v_p_inv = mat4_eye();
}

void canvas_camera_update() {
    int wnd_width = e_window.size.x;
    int wnd_height = e_window.size.y;

    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    L.real_pixel_per_pixel = floorf(smaller_size / CANVAS_CAMERA_SIZE);

    float width_2 = wnd_width / (2 * L.real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * L.real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    L.left = -floorf(width_2);
    L.top = -floorf(height_2);
    L.right = width_2 + (width_2 - floorf(width_2));
    L.bottom = height_2 + (height_2 - floorf(height_2));

    canvas_camera.matrices.p = mat4_camera_ortho(L.left, L.right, L.bottom, L.top, -1, 1);

    canvas_camera.matrices.v_inv = mat4_inv(canvas_camera.matrices.v);
    canvas_camera.matrices.p_inv = mat4_inv(canvas_camera.matrices.p);

    canvas_camera.matrices.vp = mat4_mul_mat(canvas_camera.matrices.p, canvas_camera.matrices.v_inv);

    canvas_camera.matrices.v_p_inv = mat4_mul_mat(canvas_camera.matrices.v, canvas_camera.matrices.p_inv);
}

float canvas_camera_real_pixel_per_pixel() {
    return L.real_pixel_per_pixel;
}

float canvas_camera_left() {
    return L.left;
}
float canvas_camera_right() {
    return L.right;
}
float canvas_camera_bottom() {
    return L.bottom;
}
float canvas_camera_top() {
    return L.top;
}

void canvas_camera_set_pos(float x, float y) {
    u_pose_set_xy(&canvas_camera.matrices.v, x, y);
}

void canvas_camera_set_size(float size) {
	u_pose_set_size(&canvas_camera.matrices.v, size, size);
}

void canvas_camera_set_angle(float alpha) {
    u_pose_set_angle(&canvas_camera.matrices.v, alpha);
}
