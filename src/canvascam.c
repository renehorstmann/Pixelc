#include "rhc/alloc.h"
#include "u/pose.h"
#include "mathc/sca/float.h"
#include "mathc/utils/camera.h"
#include "canvascam.h"


//
// sets up an orthogonal canvascam for pixel perfect rendering.
// coord system has a minimum square of [-90 : +90].
// render objects can use canvascam.gl for the transformation matrix.
//


//
// public
//

CanvasCam_s *canvascam_new() {
    CanvasCam_s *self = rhc_calloc(sizeof *self);
    self->matrices.v = mat4_eye();

    self->matrices.v_inv = mat4_eye();
    self->matrices.p = mat4_eye();
    self->matrices.p_inv = mat4_eye();
    self->matrices.vp = mat4_eye();
    self->matrices.v_p_inv = mat4_eye();
    return self;
}

void canvascam_update(CanvasCam_s *self, ivec2 window_size) {
    int wnd_width = window_size.x;
    int wnd_height = window_size.y;
    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;

    self->RO.scale = smaller_size / CANVASCAM_SIZE;

    if(self->RO.scale > 1) {
        self->RO.scale = sca_floor(self->RO.scale);
    }

    float width_2 = wnd_width / (2 * self->RO.scale);
    float height_2 = wnd_height / (2 * self->RO.scale);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    self->RO.left = -floorf(width_2);
    self->RO.top = floorf(height_2);
    self->RO.right = width_2 + (width_2 - floorf(width_2));
    self->RO.bottom = -height_2 - (height_2 - floorf(height_2));

    self->matrices.p = mat4_camera_ortho(self->RO.left, self->RO.right, self->RO.bottom, self->RO.top, -1, 1);

    self->matrices.v_inv = mat4_inv(self->matrices.v);
    self->matrices.p_inv = mat4_inv(self->matrices.p);

    self->matrices.vp = mat4_mul_mat(self->matrices.p, self->matrices.v_inv);

    self->matrices.v_p_inv = mat4_mul_mat(self->matrices.v, self->matrices.p_inv);
}


void canvascam_set_pos(CanvasCam_s *self, float x, float y) {
    u_pose_set_xy(&self->matrices.v, x, y);
}

void canvascam_set_size(CanvasCam_s *self, float size) {
    u_pose_set_size(&self->matrices.v, size, size);
}

void canvascam_set_angle(CanvasCam_s *self, float alpha) {
    u_pose_set_angle(&self->matrices.v, alpha);
}
