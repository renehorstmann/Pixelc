#include "mathc/bool.h"
#include "mathc/float.h"
#include "camera.h"
#include "brush.h"
#include "cameractrl.h"


#define HOME_SIZE 140
#define HOME_PORTRAIT_X 0
#define HOME_PORTRAIT_Y -20
#define HOME_LANDSCAPE_X 20
#define HOME_LANDSCAPE_Y 0

#define WHEEL_ZOOM_FACTOR 1.1
#define SMOOTH_ALPHA 0.5

#define DISTANCE_ALPHA 0.25

struct CameraCtrl_Globals cameractrl;

//
// private
//

static struct {
    vec2 pos;
    float size;

    vec2 pos0;
    vec2 move0;

    float size0;
    vec2 touch[2];
    bvec2 touching;
    float distance0;
    float distance;
    bool touched;

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
    L.size = L.size0 / factor;
    camera_set_zoom(L.size);
}

static void wheel_event(bool up, void *user_data) {
    if (up)
        L.size /= WHEEL_ZOOM_FACTOR;
    else
        L.size *= WHEEL_ZOOM_FACTOR;
    camera_set_zoom(L.size);
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
            L.size0 = L.size;
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
    L.size = 1;
    e_input_register_wheel_event(wheel_event, NULL);
}

void cameractrl_set_home(int canvas_cols, int canvas_rows) {
    memset(&L, 0, sizeof(L));


    float size = canvas_cols > canvas_rows ? canvas_cols : canvas_rows;
    L.size = size / HOME_SIZE;

    L.pos.x = canvas_cols / 2;
    L.pos.y = -canvas_rows / 2;

    if (camera_is_portrait_mode()) {
        L.pos.x += L.size * HOME_PORTRAIT_X;
        L.pos.y += L.size * HOME_PORTRAIT_Y;
    } else {
        L.pos.x += L.size * HOME_LANDSCAPE_X;
        L.pos.y += L.size * HOME_LANDSCAPE_Y;
    }

    camera_set_pos(L.pos.x, L.pos.y);
    camera_set_zoom(L.size);
}

bool cameractrl_pointer_event(ePointer_s pointer) {
    return event_cursor(pointer) || event_touch(pointer);
}

