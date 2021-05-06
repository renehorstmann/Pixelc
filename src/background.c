#include "r/ro_single.h"
#include "r/texture.h"
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

    L.ro = ro_single_new(camera.gl, r_texture_new(2, 2, 1, 1, buf));
}

void background_update(float dtime) {
    L.ro.rect.pose = u_pose_new_aa(camera_left(), camera_top(), camera_width(), camera_height());
    u_pose_set_size(&L.ro.rect.uv, camera_width() / 2, camera_height() / 2);
}

void background_render() {
    ro_single_render(&L.ro);
}
