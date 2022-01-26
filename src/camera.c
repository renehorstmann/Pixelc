#include "u/pose.h"
#include "mathc/utils/camera.h"
#include "mathc/sca/float.h"
#include "camera.h"


// comment out to not use a pixel perfect camera
#define PIXEL_PERFECT


//
// public
//

Camera_s camera_new() {
    Camera_s self = {0};
    self.matrices.v = mat4_eye();
    self.matrices.v_inv = mat4_eye();
    self.matrices.p = mat4_eye();
    self.matrices.p_inv = mat4_eye();
    self.matrices.vp = mat4_eye();
    self.matrices.v_p_inv = mat4_eye();
    return self;
}

void camera_update(Camera_s *self, ivec2 window_size) {
    int wnd_width = window_size.x;
    int wnd_height = window_size.y;

    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    self->RO.scale = smaller_size / CAMERA_SIZE;
    
#ifdef PIXEL_PERFECT
    if(self->RO.scale>1) {
        self->RO.scale = sca_floor(self->RO.scale);
    }
#endif

    float width_2 = wnd_width / (2 * self->RO.scale);
    float height_2 = wnd_height / (2 * self->RO.scale);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    self->RO.screen_left = -floorf(width_2);
    self->RO.screen_top = floorf(height_2);
    self->RO.screen_right = width_2 + (width_2 - floorf(width_2));
    self->RO.screen_bottom = -height_2 - (height_2 - floorf(height_2));

    self->matrices.p = mat4_camera_ortho(self->RO.screen_left, self->RO.screen_right, self->RO.screen_bottom, self->RO.screen_top, -1, 1);

    self->matrices.v_inv = mat4_inv(self->matrices.v);
    self->matrices.p_inv = mat4_inv(self->matrices.p);

    self->matrices.vp = mat4_mul_mat(self->matrices.p, self->matrices.v_inv);

    self->matrices.v_p_inv = mat4_mul_mat(self->matrices.v, self->matrices.p_inv);
    
    self->RO.left = sca_floor(self->RO.screen_left);
    self->RO.right = sca_ceil(self->RO.screen_right);
    self->RO.bottom = sca_floor(self->RO.screen_bottom);
    self->RO.top = sca_ceil(self->RO.screen_top);
}


void camera_set_pos(Camera_s *self, float x, float y) {
    u_pose_set_xy(&self->matrices.v, x, y);
}

void camera_set_size(Camera_s *self, float size) {
    u_pose_set_size(&self->matrices.v, size, size);
}

void camera_set_angle(Camera_s *self, float alpha) {
    u_pose_set_angle(&self->matrices.v, alpha);
}
