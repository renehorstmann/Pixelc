#include "e/window.h"
#include "e/gui.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/json.h"
#include "m/utils/camera.h"
#include "m/sca/float.h"
#include "m/io/int.h"
#include "camera.h"
#include "mod_palette_camera.h"



//
// public
//

struct ModPaletteCamera_Globals mod_palette_camera;

void mod_palette_camera_init() {
    mod_palette_camera.matrices.v = mat4_eye();
    mod_palette_camera.matrices.v_inv = mat4_eye();
    mod_palette_camera.matrices.p = mat4_eye();
    mod_palette_camera.matrices.p_inv = mat4_eye();
    mod_palette_camera.matrices.vp = mat4_eye();
//    mod_palette_camera.matrices.v_p_inv = mat4_eye();
    mod_palette_camera.size = 200;
}

void mod_palette_camera_update(ivec2 window_size) {
    int wnd_width = window_size.x;
    int wnd_height = window_size.y;

    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    mod_palette_camera.RO.scale = smaller_size / mod_palette_camera.size;

#ifdef PIXEL_PERFECT
    if (mod_palette_camera.RO.scale > 1) {
        mod_palette_camera.RO.scale = sca_floor(mod_palette_camera.RO.scale);
    }
#endif

    float width_2 = (float) wnd_width / (2 * mod_palette_camera.RO.scale);
    float height_2 = (float) wnd_height / (2 * mod_palette_camera.RO.scale);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    mod_palette_camera.RO.screen_left = -floorf(width_2);
    mod_palette_camera.RO.screen_top = -height_2 - (height_2 - floorf(height_2));
    mod_palette_camera.RO.screen_right = width_2 + (width_2 - floorf(width_2));
    mod_palette_camera.RO.screen_bottom = floorf(height_2);

    mod_palette_camera.matrices.p = mat4_camera_ortho(mod_palette_camera.RO.screen_left, mod_palette_camera.RO.screen_right, mod_palette_camera.RO.screen_bottom,
                                          mod_palette_camera.RO.screen_top, -1, 1);

    mod_palette_camera.matrices.v_inv = mat4_inv(mod_palette_camera.matrices.v);
    mod_palette_camera.matrices.p_inv = mat4_inv(mod_palette_camera.matrices.p);

    mod_palette_camera.matrices.vp = mat4_mul_mat(mod_palette_camera.matrices.p, mod_palette_camera.matrices.v_inv);

    mod_palette_camera.matrices.v_p_inv = mat4_mul_mat(mod_palette_camera.matrices.v, mod_palette_camera.matrices.p_inv);

    mod_palette_camera.RO.left = sca_floor(mod_palette_camera.RO.screen_left);
    mod_palette_camera.RO.right = sca_ceil(mod_palette_camera.RO.screen_right);
    mod_palette_camera.RO.bottom = sca_floor(mod_palette_camera.RO.screen_bottom);
    mod_palette_camera.RO.top = sca_ceil(mod_palette_camera.RO.screen_top);
}


void mod_palette_camera_set_pos(float x, float y) {
    u_pose_set_xy(&mod_palette_camera.matrices.v, x, y);
}

void mod_palette_camera_set_zoom(float size) {
    u_pose_set_size(&mod_palette_camera.matrices.v, size, size);
}

void mod_palette_camera_set_angle(float alpha) {
    u_pose_set_angle(&mod_palette_camera.matrices.v, alpha);
}
