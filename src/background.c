#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "color.h"
#include "background.h"

static struct {
    RoSingle ro;
} L;

void background_init(Color_s a, Color_s b) {
    Color_s buf[4];
    buf[0] = buf[3] = a;
    buf[1] = buf[2] = b;

    ro_single_init(&L.ro, camera.gl, r_texture_new(2, 2, buf));
}

void background_update(float dtime) {
    L.ro.rect.pose = u_pose_new_aa(camera_left(), camera_top(), camera_width(), camera_height());
    u_pose_set_size(&L.ro.rect.uv, camera_width() / 2, camera_height() / 2);
}

void background_render() {
    ro_single_render(&L.ro);
}
