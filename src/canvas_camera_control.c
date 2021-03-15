#include "mathc/bool.h"
#include "mathc/float.h"
#include "canvas_camera.h"
#include "brush.h"
#include "canvas_camera_control.h"


static struct {
    vec2 pos;
    float size;

    vec2 pos0;

    vec2 move0;

#if USING_TOUCH
    float size0;
    vec2 touch[2];
    bvec2 touching;
    float distance0;
    bool touched;
#else
    vec2 pointer_pos;
    bool moving;
#endif

} L;


static void move_camera(vec2 current_pos) {
    vec2 diff = vec2_sub_vec(current_pos, L.move0);
    L.pos = vec2_sub_vec(L.pos0, diff);
    canvas_camera_set_pos(L.pos.x, L.pos.y);
}

static float clampf(float f, float min, float max) {
	return f < min ? min : f > max ? max : f;
}

#if USING_TOUCH
static void zoom_camera(float new_distance) {
    float factor = new_distance / L.distance0;
    factor = clampf(factor, 0.3, 3);
    L.size = L.size0 / factor;
    canvas_camera_set_size(L.size);
}
#endif

static void wheel_event(bool up, void *user_data) {
    if (up)
        L.size /= CANVAS_CAMERA_CONTROL_WHEEL_ZOOM_FACTOR;
    else
        L.size *= CANVAS_CAMERA_CONTROL_WHEEL_ZOOM_FACTOR;
    canvas_camera_set_size(L.size);
}

void canvas_camera_control_init() {
    L.size = 1;
    e_input_register_wheel_event(wheel_event, NULL);
}

void canvas_camera_control_set_home() {
	memset(&L, 0, sizeof(L));
	L.size = 1;
    canvas_camera_set_pos(L.pos.x, L.pos.y);
    canvas_camera_set_size(L.size);
}

bool canvas_camera_control_pointer_event(ePointer_s pointer) {
#ifdef USING_TOUCH
    if (pointer.id < 0 || pointer.id > 1)
        return false;

    L.touch[pointer.id] = vec2_mix(L.touch[pointer.id], pointer.pos.xy, CANVAS_CAMERA_CONTROL_SMOOTH_ALPHA);

    if (pointer.action == E_POINTER_DOWN) {
        L.touching.v[pointer.id] = true;
        L.touch[pointer.id] = pointer.pos.xy;
    }

    if (pointer.action == E_POINTER_UP) {
        L.touching.v[pointer.id] = false;
    }

    if (bvec2_all(L.touching)) {
        if(!L.touched) {
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
        } else {
            move_camera(mean);
            zoom_camera(distance);
        }
    }
    
    if (L.touched && !bvec2_any(L.touching))
        L.touched = false;
    
    return L.touched;
#else
    L.pointer_pos = vec2_mix(L.pointer_pos, pointer.pos.xy, CANVAS_CAMERA_CONTROL_SMOOTH_ALPHA);
    if(L.moving) {
        move_camera(L.pointer_pos);
        if(pointer.action == E_POINTER_DOWN) {
            L.moving = false;
            return true;
        }
    } else if(pointer.action == E_POINTER_DOWN
        && pointer.id <0) { // middle + right
        L.pointer_pos = pointer.pos.xy;
        L.pos0 = L.pos;
        L.move0 = pointer.pos.xy;
        L.moving = true;
        
        brush_abort_current_draw();
    }
    
    return L.moving;
#endif
}

