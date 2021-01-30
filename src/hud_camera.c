#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "hud_camera.h"


HudCameraMatrices_s hud_camera_matrices;
const float *hud_camera_gl;

static struct {
    float left, right, bottom, top;
} L;


void hud_camera_init() {
    assert(HUD_CAMERA_SIZE % 2 == 0 && "HUD_CAMERA_SIZE must be even");
    hud_camera_gl = &hud_camera_matrices.p.m00;
    hud_camera_matrices.p = mat4_eye();
    hud_camera_matrices.p_inv = mat4_eye();
}

void hud_camera_update() {
    int wnd_width = e_window_size[0];
    int wnd_height = e_window_size[1];


    int smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    float real_pixel_per_pixel = floorf((float) smaller_size / HUD_CAMERA_SIZE);

    float width_2 = wnd_width / (2 * real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    L.left = -floorf(width_2);
    L.top = floorf(height_2);
    L.right = width_2 + (width_2 - floorf(width_2));
    L.bottom = -height_2 - (height_2 - floorf(height_2));

    hud_camera_matrices.p = mat4_camera_ortho(L.left, L.right, L.bottom, L.top, -1, 1);
    hud_camera_matrices.p_inv = mat4_inv(hud_camera_matrices.p);
}


float hud_camera_left() {
    return L.left;
}
float hud_camera_right() {
    return L.right;
}
float hud_camera_bottom() {
    return L.bottom;
}
float hud_camera_top() {
    return L.top;
}
