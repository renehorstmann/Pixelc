#include "m/bool.h"
#include "m/float.h"
#include "camera.h"
#include "palette.h"
#include "mod_palette_camera.h"
#include "mod_palette_cameractrl.h"

#define HOME_SIZE 0.9
#define WHEEL_ZOOM_FACTOR 1.1
#define SMOOTH_ALPHA 0.5

#define DISTANCE_ALPHA 0.25

struct ModPaletteCameraCtrl_Globals mod_palette_cameractrl;

//
// private
//

static struct {
    vec2 pos;
    float zoom;

    vec2 pos0;
    vec2 move0;

    float zoom0;
    vec2 touch[2];
    bvec2 touching;
    float distance0;
    float distance;
    bool touched;

    int set_home_cnt;

    struct {
        vec2 pointer_pos;
        bool moving;
    } cursor;

} L;

static void move_camera(vec2 current_pos) {
    vec2 diff = vec2_sub_vec(current_pos, L.move0);
    diff = vec2_scale(diff, 2);
    L.pos = vec2_sub_vec(L.pos0, diff);
    mod_palette_camera_set_pos(L.pos.x, L.pos.y);
}

static void zoom_camera(float new_distance) {
    float factor = new_distance / L.distance0;
    factor = sca_clamp(factor, 0.3, 3);
    L.zoom = L.zoom0 / factor;
    mod_palette_camera_set_zoom(L.zoom);
}

static void set_home() {
    // protected 
    vec2 mod_palette_tiles_size();
    
    vec2 size = mod_palette_tiles_size();
    
    mod_palette_camera_set_pos(size.x/2, -size.y/2);
    mod_palette_camera_set_zoom(size.y/mod_palette_camera.size);
}

static void wheel_event(vec4 pos, bool up, void *user_data) {
    // protected
    vec4 mod_palette_pointer_pos(vec4 hud_pointer_pos);
    // protected
    vec2 mod_palette_tiles_size();

    vec4 hud_pos = mat4_mul_vec(camera.matrices.p_inv, pos);
    if(!palette_contains_pos(hud_pos.xy))
        return;
    vec4 t_pos = mod_palette_pointer_pos(hud_pos);

    vec2 tile_size = mod_palette_tiles_size();
    if (t_pos.x < 0 || t_pos.x > tile_size.x || t_pos.y < -tile_size.y || t_pos.y > 0)
        return;

    if (up)
        L.zoom /= WHEEL_ZOOM_FACTOR;
    else
        L.zoom *= WHEEL_ZOOM_FACTOR;
    mod_palette_camera_set_zoom(L.zoom);
}

static bool event_cursor(ePointer_s pointer) {
    // if move_mode is true, the normal pointer (0) can move the camera
    int max_id = mod_palette_cameractrl.move_mode ? 0 : -1;

    L.cursor.pointer_pos = vec2_mix(L.cursor.pointer_pos, pointer.pos.xy,
                                    SMOOTH_ALPHA);
    if (L.cursor.moving) {
        move_camera(L.cursor.pointer_pos);
        if (pointer.id <= max_id && pointer.action == E_POINTER_UP) {
            L.cursor.moving = false;
        }
    } else if (pointer.id <= max_id && pointer.action == E_POINTER_DOWN) {
        L.cursor.pointer_pos = pointer.pos.xy;
        L.pos0 = L.pos;
        L.move0 = pointer.pos.xy;
        L.cursor.moving = true;
    }

    return L.cursor.moving;
}

static bool event_touch(ePointer_s pointer) {
    if (!e_input.is_touch || pointer.id < 0 || pointer.id > 1)
        return false;

    L.touch[pointer.id] = vec2_mix(L.touch[pointer.id], pointer.pos.xy, SMOOTH_ALPHA);

    if (pointer.action == E_POINTER_DOWN) {
        L.touching.v[pointer.id] = true;
        L.touch[pointer.id] = pointer.pos.xy;
    }

    if (pointer.action == E_POINTER_UP) {
        L.touching.v[pointer.id] = false;
    }

    if (bvec2_all(L.touching)) {
        if (!L.touched) {
            L.touched = true;
        }

        vec2 mean = vec2_div(vec2_add_vec(L.touch[0], L.touch[1]), 2);
        float distance = vec2_norm(vec2_sub_vec(L.touch[0], L.touch[1]));

        if (pointer.action == E_POINTER_DOWN) {
            L.zoom0 = L.zoom;
            L.pos0 = L.pos;
            L.move0 = mean;
            L.distance0 = distance;
            L.distance = distance;
        } else {
            L.distance = sca_mix(L.distance, distance, DISTANCE_ALPHA);
            move_camera(mean);
            zoom_camera(L.distance);
        }
    }

    if (L.touched && !bvec2_any(L.touching))
        L.touched = false;

    return L.touched;
}

//
// public
//


void mod_palette_cameractrl_init() {
    L.zoom = 1;
    e_input_register_wheel_event(wheel_event, NULL);
}

void mod_palette_cameractrl_update(float dtime) {
    if(L.set_home_cnt>0) {
        L.set_home_cnt--;
        if(L.set_home_cnt<=0)
            set_home();
    }
}

void mod_palette_cameractrl_set_home() {
    L.set_home_cnt = 3;
}

bool mod_palette_cameractrl_pointer_event(ePointer_s pointer) {
    return event_cursor(pointer) || event_touch(pointer);
}

