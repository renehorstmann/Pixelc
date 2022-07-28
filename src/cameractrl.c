#include "m/bool.h"
#include "m/float.h"
#include "camera.h"
#include "brush.h"
#include "canvas.h"
#include "palette.h"
#include "toolbar.h"
#include "cameractrl.h"

#define HOME_SIZE 0.9
#define WHEEL_ZOOM_FACTOR 1.1
#define SMOOTH_ALPHA 0.5

#define DISTANCE_ALPHA 0.25

struct CameraCtrl_Globals cameractrl;

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
    camera_set_pos(L.pos.x, L.pos.y);
}

static void zoom_camera(float new_distance) {
    float factor = new_distance / L.distance0;
    factor = sca_clamp(factor, 0.3, 3);
    L.zoom = L.zoom0 / factor;
    camera_set_zoom(L.zoom);
}

static void set_home() {
    memset(&L, 0, sizeof(L));

    ivec2 csize = canvas_get_size();
    
    int left = camera.RO.left;
    int right = camera.RO.right;
    int top = camera.RO.top;
    int bottom = camera.RO.bottom;
    
    if (camera_is_portrait_mode()) {
        top -= toolbar_size();
        bottom += palette_get_hud_size();
    } else {
        left += toolbar_size();
        right -= palette_get_hud_size();
    }
    
    float w = right - left;
    float h = top - bottom;

    bool adjust_by_height = false;
    if(w>h && (w/h >= csize.x/csize.y))
        adjust_by_height = true;
    if(w<h && (h/w <= csize.y/csize.x))
        adjust_by_height = true;
        
    if(adjust_by_height) {
        L.zoom = csize.y / (h*HOME_SIZE);
    } else {
        L.zoom = csize.x / (w*HOME_SIZE);
    }
    
    float cx = (left + right) / 2.0f;
    float cy = (bottom + top) / 2.0f;
    
    L.pos.x = csize.x/2.0f;
    L.pos.y = -csize.y/2.0f;
    
    L.pos.x -= cx * L.zoom;
    L.pos.y -= cy * L.zoom;
   
    camera_set_pos(L.pos.x, L.pos.y);
    camera_set_zoom(L.zoom);
}


static void wheel_event(bool up, void *user_data) {
    if (up)
        L.zoom /= WHEEL_ZOOM_FACTOR;
    else
        L.zoom *= WHEEL_ZOOM_FACTOR;
    camera_set_zoom(L.zoom);
}

static bool event_cursor(ePointer_s pointer) {
    // if move_mode is true, the normal pointer (0) can move the camera
    int max_id = cameractrl.move_mode ? 0 : -1;

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

        brush_abort_current_draw();
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
            brush_abort_current_draw();
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


void cameractrl_init() {
    L.zoom = 1;
    e_input_register_wheel_event(wheel_event, NULL);
}

void cameractrl_update(float dtime) {
    if(L.set_home_cnt>0) {
        L.set_home_cnt--;
        if(L.set_home_cnt<=0)
            set_home();
    }
}

void cameractrl_set_home() {
    L.set_home_cnt = 3;
}

bool cameractrl_pointer_event(ePointer_s pointer) {
    return event_cursor(pointer) || event_touch(pointer);
}

