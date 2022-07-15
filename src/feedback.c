#include "r/r.h"
#include "u/pose.h"
#include "m/float.h"
#include "feedback.h"


#define LONGPRESS_TIME 0.5

#define FLASH_ALPHA 0.5


struct {

    struct {
        RoSingle ro;
        vec4 color;
        float time;
    } longpress;

    struct {
        RoSingle ro;
        mat4 cam;
        vec4 color;
        float time;
        float set_time;
    } flash;
    
} L;




//
// public
//


void feedback_init() {
    L.longpress.ro = ro_single_new(r_texture_new_file(1, 1, "res/longpress.png"));
    u_pose_set_size(&L.longpress.ro.rect.pose, 64, 64);
    
    L.flash.ro = ro_single_new(r_texture_new_white_pixel());
    
    // fullscreen (gl coordination system goes from -1:1, so size=2)
    u_pose_set_size(&L.flash.ro.rect.pose, 2, 2);
    L.flash.cam = mat4_eye();
}

void feedback_update(float dtime) {
    if (L.longpress.time > 0) {
        L.longpress.ro.rect.color = vec4_mix(
                R_COLOR_TRANSPARENT,
                L.longpress.color,
                L.longpress.time / LONGPRESS_TIME);
        L.longpress.time -= dtime;
    }
    
    
    if (L.flash.time > 0) {
        L.flash.ro.rect.color = vec4_mix(
                R_COLOR_TRANSPARENT,
                L.flash.color,
                L.flash.time / L.flash.set_time);
        L.flash.time -= dtime;
    }
}

void feedback_render(const mat4 *cam_mat) {
    if (L.longpress.time > 0) {
        ro_single_render(&L.longpress.ro, cam_mat);
    }
    if(L.flash.time > 0) {
        ro_single_render(&L.flash.ro, &L.flash.cam);
    }
    
}

void feedback_longpress(vec2 pos, vec4 color) {
    u_pose_set_xy(&L.longpress.ro.rect.pose, pos.x, pos.y);
    L.longpress.color = color;
    L.longpress.time = LONGPRESS_TIME;
}

void feedback_flash(vec4 color, float time) {
    L.flash.color = color;
    L.flash.color.a *= FLASH_ALPHA;
    L.flash.time = time;
    L.flash.set_time = time;
}
