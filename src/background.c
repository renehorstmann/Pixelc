#include "r/r.h"
#include "u/pose.h"
#include "u/color.h"
#include "camera.h"
#include "background.h"


//
// private
//

static struct {
    RoSingle ro;
} L;


//
// public
//

void background_init(uColor_s a, uColor_s b) {
    uColor_s buf[4];
    buf[0] = buf[3] = a;
    buf[1] = buf[2] = b;

    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    L.ro = ro_single_new(tex);
}

void background_update(float dtime) {
    float cam_w = camera_width();
    float cam_h = camera_height();
    L.ro.rect.pose = u_pose_new_aa(camera.RO.left, camera.RO.top, cam_w, cam_h);
    u_pose_set_size(&L.ro.rect.uv, cam_w / 2, cam_h / 2);
}

void background_render(const mat4 *camera_mat) {
    ro_single_render(&L.ro, camera_mat);
}
