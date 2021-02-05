#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "color.h"
#include "background.h"

static struct {
   rRoSingle ro;
} L;

void background_init() {
    Color_s buf[4];
    buf[0] = buf[3] = color_from_hex("#000000");
    buf[1] = buf[2] = color_from_hex("#222222");

    GLuint tex = r_texture_init(2, 2, buf);
    r_texture_filter_nearest(tex);

    r_ro_single_init(&L.ro, hud_camera_gl, tex);
}

void background_update(float dtime) {
    u_pose_set_size(&L.ro.rect.pose, hud_camera_width(), hud_camera_height());
    u_pose_set_size(&L.ro.rect.uv, hud_camera_width()/2, hud_camera_height()/2);
}

void background_render() {
    r_ro_single_render(&L.ro);
}
