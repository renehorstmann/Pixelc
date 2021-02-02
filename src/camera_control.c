#include "mathc/bool.h"
#include "mathc/float.h"
#include "c_camera.h"
#include "camera_control.h"


static struct {
    vec2 pos;
    float size;

    vec2 touch[2];
    bvec2 touching;

    float distance0;
    float size0;
    vec2 move0;
    bool moving;
} L;


static void move_camera(vec2 current_pos) {
    vec2 diff = vec2_sub_vec(current_pos, L.move0);
    L.pos = vec2_sub_vec(L.pos, diff);
    c_camera_set_pos(L.pos.x, L.pos.y);
}

static void zoom_camera(float new_distance) {
    float factor = new_distance / L.distance0;
    L.size = L.size0 * factor;
    c_camera_set_size(L.size);
}

static void wheel_event(bool up, void *user_data) {
    if (up)
        L.size /= CAMERA_CONTROL_WHEEL_ZOOM_FACTOR;
    else
        L.size *= CAMERA_CONTROL_WHEEL_ZOOM_FACTOR;
    c_camera_set_size(L.size);
}

void camera_control_init() {
    L.size = 1;
    e_input_register_wheel_event(wheel_event, NULL);
}

void camera_control_pointer_event(ePointer_s pointer) {
#ifdef GLES
    if (pointer.id < 0 || pointer.id > 1)
        return;

    float alpha = 0.5;
    L.touch[pointer.id].x = L.touch[pointer.id].x *(1-alpha) + pointer.pos.x * alpha;
    L.touch[pointer.id].y = L.touch[pointer.id].y *(1-alpha) + pointer.pos.y * alpha;

    if (pointer.action == E_POINTER_DOWN) {
        L.touching.v[pointer.id] = true;
        L.touch[pointer.id] = pointer.pos.xy;
    }

    if (pointer.action == E_POINTER_UP) {
        L.touching.v[pointer.id] = false;
    }

    if (bvec2_all(L.touching)) {
        vec2 mean = vec2_div(vec2_add_vec(L.touch[0], L.touch[1]), 2);
        float distance = vec2_norm(vec2_sub_vec(L.touch[0], L.touch[1]));

        if (pointer.action == E_POINTER_DOWN) {
            L.move0 = mean;
            L.distance0 = distance;
            L.size0 = L.size;
        } else {
            //move_camera(mean);
            zoom_camera(distance);
        }
    }
#else
    if(L.moving) {
        move_camera(pointer.pos.xy);
        if(pointer.action == E_POINTER_DOWN) {
            L.moving = false;
        }
    } else if(pointer.action == E_POINTER_MIDDLE_DOWN || pointer.action == E_POINTER_RIGHT_DOWN) {
        L.move0 = pointer.pos.xy;
        L.moving = true;
    }
#endif
}


