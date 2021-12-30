#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "u/color.h"
#include "camera.h"
#include "background.h"


//
// private
//

struct Background {
    struct {
        RoSingle ro;
    } L;
};


//
// public
//

Background *background_new(uColor_s a, uColor_s b) {
    Background *self = rhc_calloc(sizeof *self);
    uColor_s buf[4];
    buf[0] = buf[3] = a;
    buf[1] = buf[2] = b;

    self->L.ro = ro_single_new(r_texture_new(2, 2, 1, 1, buf));
    return self;
}

void background_update(Background *self, const Camera_s *camera, float dtime) {
    float cam_w = camera_width(camera);
    float cam_h = camera_height(camera);
    self->L.ro.rect.pose = u_pose_new_aa(camera->RO.left, camera->RO.top, cam_w, cam_h);
    u_pose_set_size(&self->L.ro.rect.uv, cam_w / 2, cam_h / 2);
}

void background_render(const Background *self, const mat4 *camera_mat) {
    ro_single_render(&self->L.ro, camera_mat);
}
