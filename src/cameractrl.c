#include "mathc/bool.h"
#include "mathc/float.h"
#include "camera.h"
#include "brush.h"
#include "cameractrl.h"


//
// private
//




static void move_camera(CameraCtrl *self, vec2 current_pos) {
    vec2 diff = vec2_sub_vec(current_pos, self->L.move0);
    self->L.pos = vec2_sub_vec(self->L.pos0, diff);
    camera_set_pos(self->camera_ref, self->L.pos.x, self->L.pos.y);
}

static float clampf(float f, float min, float max) {
    return f < min ? min : f > max ? max : f;
}

#if OPTION_TOUCH
static void zoom_camera(CameraCtrl *self, float new_distance) {
    float factor = new_distance / self->L.distance0;
    factor = clampf(factor, 0.3, 3);
    self->L.size = self->L.size0 / factor;
    canvascam_set_size(self->camera_ref, self->L.size);
}
#endif

static void wheel_event(bool up, void *user_data) {
    CameraCtrl *self = user_data;
    if (up)
        self->L.size /= CAMERA_CONTROL_WHEEL_ZOOM_FACTOR;
    else
        self->L.size *= CAMERA_CONTROL_WHEEL_ZOOM_FACTOR;
    camera_set_size(self->camera_ref, self->L.size);
}


//
// public
//


CameraCtrl *cameractrl_new(eInput *input, Camera_s *camera, Brush *brush_ref) {
    CameraCtrl *self = rhc_calloc(sizeof *self);

    self->camera_ref = camera;
    self->brush_ref = brush_ref;

    self->L.size = 1;
    e_input_register_wheel_event(input, wheel_event, self);

    return self;
}

void cameractrl_set_home(CameraCtrl *self) {
    memset(&self->L, 0, sizeof(self->L));
    self->L.size = 1;
    camera_set_pos(self->camera_ref, self->L.pos.x, self->L.pos.y);
    camera_set_size(self->camera_ref, self->L.size);
}

bool cameractrl_pointer_event(CameraCtrl *self, ePointer_s pointer) {
#ifdef OPTION_TOUCH
    if (pointer.id < 0 || pointer.id > 1)
        return false;

    self->L.touch[pointer.id] = vec2_mix(self->L.touch[pointer.id], pointer.pos.xy, CAMERA_CONTROL_SMOOTH_ALPHA);

    if (pointer.action == E_POINTER_DOWN) {
        self->L.touching.v[pointer.id] = true;
        self->L.touch[pointer.id] = pointer.pos.xy;
    }

    if (pointer.action == E_POINTER_UP) {
        self->L.touching.v[pointer.id] = false;
    }

    if (bvec2_all(self->L.touching)) {
        if(!self->L.touched) {
            self->L.touched = true;
            brush_abort_current_draw(self->brush_ref);
        }
        
        vec2 mean = vec2_div(vec2_add_vec(self->L.touch[0], self->L.touch[1]), 2);
        float distance = vec2_norm(vec2_sub_vec(self->L.touch[0], self->L.touch[1]));

        if (pointer.action == E_POINTER_DOWN) {
            self->L.size0 = self->L.size;
            self->L.pos0 = self->L.pos;
            self->L.move0 = mean;
            self->L.distance0 = distance;
        } else {
            move_camera(self, mean);
            zoom_camera(self, distance);
        }
    }
    
    if (self->L.touched && !bvec2_any(self->L.touching))
        self->L.touched = false;
    
    return self->L.touched;
#else
    self->L.pointer_pos = vec2_mix(self->L.pointer_pos, pointer.pos.xy, CAMERA_CONTROL_SMOOTH_ALPHA);
    if (self->L.moving) {
        move_camera(self, self->L.pointer_pos);
        if (pointer.action == E_POINTER_DOWN) {
            self->L.moving = false;
            return true;
        }
    } else if (pointer.action == E_POINTER_DOWN
               && pointer.id < 0) { // middle + right
        self->L.pointer_pos = pointer.pos.xy;
        self->L.pos0 = self->L.pos;
        self->L.move0 = pointer.pos.xy;
        self->L.moving = true;

        brush_abort_current_draw(self->brush_ref);
    }

    return self->L.moving;
#endif
}

