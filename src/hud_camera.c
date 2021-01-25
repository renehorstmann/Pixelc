#include "mathc/float.h"
#include "mathc/utils/camera.h"
#include "r/rect.h"
#include "u/pose.h"
#include "e/window.h"
#include "hud_camera.h"


mat4 hud_camera_p;
mat4 hud_camera_p_inv;


static struct {
    float width, height;
} L;


void hud_camera_init() {
    hud_camera_p = mat4_eye();
    hud_camera_p_inv = mat4_eye();
}

void hud_camera_update() {
    int wnd_width = e_window_size[0];
    int wnd_height = e_window_size[1];

    if (wnd_width > wnd_height) {
        L.height = 200;
        L.width = 200 * wnd_width / wnd_height;
    } else {
        L.width = 200;
        L.height = 200 * wnd_height / wnd_width;
    }

    hud_camera_p = mat4_camera_ortho(-L.width / 2, L.width / 2, -L.height / 2, L.height / 2, -1, 1);
    hud_camera_p_inv = mat4_inv(hud_camera_p);
}


float hud_camera_width() {
    return L.width;
}
float hud_camera_height() {
    return L.height;
}
