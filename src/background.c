#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "color.h"
#include "background.h"

static struct {
   rRoSingle ro;
} L;

void background_init(Color_s a, Color_s b) {
    Color_s buf[4];
    buf[0] = buf[3] = a;
    buf[1] = buf[2] = b;

    r_ro_single_init(&L.ro, camera.gl, r_texture_init(2, 2, buf));
}

void background_update(float dtime) {
    u_pose_set_size(&L.ro.rect.pose, camera_width(), camera_height());
    u_pose_set_size(&L.ro.rect.uv, camera_width() / 2, camera_height() / 2);

    float ux = -(camera_right() + camera_left()) / 4;
    float uy = (camera_bottom() + camera_top()) / 4;
    
    u_pose_set_xy(&L.ro.rect.uv, ux, uy);
}

void background_render() {
    r_ro_single_render(&L.ro);
}
