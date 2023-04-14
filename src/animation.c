#include "r/r.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/json.h"
#include "canvas.h"
#include "camera.h"
#include "palette.h"
#include "io.h"
#include "animation.h"


struct Animation_Globals animation;

static struct {
    RoSingle ro;

    float time;
} L;


//
// public
//


void animation_init() {
    animation.size = 1.0;
    animation.auto_show = true;

    L.ro = ro_single_new(r_texture_new_invalid());
    L.ro.owns_tex = false;
}

void animation_update(float dtime) {
    if(!animation.show)
        return;
    
    float phs = palette_get_hud_size();

    rTexture tex = canvas.RO.tex;
    ivec2 size = canvas_get_size();

    float w = animation.size * size.x;
    float h = animation.size * size.y;
    
    float left, top;
    if(camera_is_portrait_mode()) {
        left = camera.RO.left;
        top = camera.RO.bottom + phs + h;
    } else {
        left = camera.RO.right - phs - w;
        top = camera.RO.bottom + h;
    }
    
    L.time -= dtime;
    if(L.time<=0) {
        int sprite = sca_mod(L.ro.rect.sprite.x+1, tex.sprites.x);
        L.ro.rect.sprite.x = sprite;
        
        L.time += canvas.frame_times[sprite];
    }
    
    switch(animation.mode) {
    case ANIMATION_MODE_SINGLE:
        L.ro.rect.pose = u_pose_new_aa(
                left, top, w, h);
        L.ro.rect.uv = u_pose_new(0, 0, 1, 1);
        break;
    case ANIMATION_MODE_REPEAT_H:
        L.ro.rect.pose = u_pose_new_aa(
                camera.RO.left,
                top,
                camera_width(), 
                h);
        L.ro.rect.uv = u_pose_new(0, 0, 
                camera_width()/w, 
                1);
        break;
    case ANIMATION_MODE_REPEAT_V:
        L.ro.rect.pose = u_pose_new_aa(
                left, 
                camera.RO.top,
                w, 
                camera_height());
        L.ro.rect.uv = u_pose_new(0, 0, 
                1, 
                camera_height()/h);
        break;
    case ANIMATION_MODE_REPEAT_HV:
        L.ro.rect.pose = u_pose_new_aa(
                camera.RO.left, 
                camera.RO.top,
                camera_width(), 
                camera_height());
        L.ro.rect.uv = u_pose_new(0, 0, 
                camera_width()/w, 
                camera_height()/h);
        break;
    default:
        s_assume(false, "invalid mode");
    }
}

void animation_render(const mat4 *cam_mat) {
    if (!animation.show)
        return;

    rTexture tex = canvas.RO.tex;
    r_texture_wrap_repeat(tex);
    ro_single_set_texture(&L.ro, tex);
    for(int i=0; i<=canvas.RO.current_layer; i++) {
        L.ro.rect.sprite.y = i;
        ro_single_render(&L.ro, cam_mat);
    }
}

void animation_save_config() {
    s_log("save");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "animation");

    u_json_append_float(member, "size", animation.size);
    u_json_append_int(member, "mode", animation.mode);
    u_json_append_bool(member, "auto_show", animation.auto_show);

    u_json_save_file(config, io_config_file(), NULL);
    e_io_savestate_save();

    u_json_kill(&config);
}

void animation_load_config() {
    s_log("load");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_get_object(config, "animation");

    float size;
    if(u_json_get_object_float(member, "size", &size)) {
        if(size > ANIMATION_SIZE_MIN && size <= ANIMATION_SIZE_MAX) {
            animation.size = size;
        }
    }

    int mode;
    if(u_json_get_object_int(member, "mode", &mode)) {
        if(mode >= ANIMATION_MODE_SINGLE && mode < ANIMATION_NUM_MODES) {
            animation.mode = mode;
        }
    }

    const bool *autoshow = u_json_get_object_bool(member, "auto_show");
    if(autoshow) {
        animation.auto_show = *autoshow;
    }

    u_json_kill(&config);
}
