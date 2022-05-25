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

//
// private
//

static void move_camera(CameraCtrl *self, vec2 current_pos) {
    vec2 diff = vec2_sub_vec(current_pos, self->L.move0);
    diff = vec2_scale(diff, 2);
    self->L.pos = vec2_sub_vec(self->L.pos0, diff);
    camera_set_pos(self->camera_ref, self->L.pos.x, self->L.pos.y);
}

static void zoom_camera(CameraCtrl *self, float new_distance) {
    float factor = new_distance / self->L.distance0;
    factor = sca_clamp(factor, 0.3, 3);
    self->L.size = self->L.size0 / factor;
    camera_set_zoom(self->camera_ref, self->L.size);
}

static void wheel_event(bool up, void *user_data) {
    CameraCtrl *self = user_data;
    if (up)
        self->L.size /= WHEEL_ZOOM_FACTOR;
    else
        self->L.size *= WHEEL_ZOOM_FACTOR;
    camera_set_zoom(self->camera_ref, self->L.size);
}

static bool event_cursor(CameraCtrl *self, ePointer_s pointer) {
    // if move_mode is true, the normal pointer (0) can move the camera
    int max_id = self->move_mode? 0 : -1;

    self->L.cursor.pointer_pos = vec2_mix(self->L.cursor.pointer_pos, pointer.pos.xy,
                                          SMOOTH_ALPHA);
    if (self->L.cursor.moving) {
        move_camera(self, self->L.cursor.pointer_pos);
        if (pointer.id <= max_id && pointer.action == E_POINTER_UP) {
            self->L.cursor.moving = false;
        }
    } else if (pointer.id <= max_id && pointer.action == E_POINTER_DOWN) {
        self->L.cursor.pointer_pos = pointer.pos.xy;
        self->L.pos0 = self->L.pos;
        self->L.move0 = pointer.pos.xy;
        self->L.cursor.moving = true;

        brush_abort_current_draw(self->brush_ref);
    }

    return self->L.cursor.moving;
}

static bool event_touch(CameraCtrl *self, ePointer_s pointer) {
    if (!e_input_is_touch(self->input_ref) || pointer.id < 0 || pointer.id > 1)
        return false;

    self->L.touch[pointer.id] = vec2_mix(self->L.touch[pointer.id], pointer.pos.xy, SMOOTH_ALPHA);

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
            self->L.distance = distance;
        } else {
            self->L.distance = sca_mix(self->L.distance, distance, DISTANCE_ALPHA);
            move_camera(self, mean);
            zoom_camera(self, self->L.distance);
        }
    }

    if (self->L.touched && !bvec2_any(self->L.touching))
        self->L.touched = false;

    return self->L.touched;
}

//
// public
//


CameraCtrl *cameractrl_new(eInput *input, Camera_s *camera, Brush *brush_ref) {
    CameraCtrl *self = rhc_calloc(sizeof *self);

    self->input_ref = input;
    self->camera_ref = camera;
    self->brush_ref = brush_ref;

    self->L.size = 1;
    e_input_register_wheel_event(input, wheel_event, self);

    return self;
}

void cameractrl_set_home(CameraCtrl *self, int canvas_cols, int canvas_rows) {
    memset(&self->L, 0, sizeof(self->L));
    
    
    float size = canvas_cols>canvas_rows? canvas_cols : canvas_rows;
    self->L.size = size / HOME_SIZE;
    
    self->L.pos.x = canvas_cols/2;
    self->L.pos.y = -canvas_rows/2;
    
    if(camera_is_portrait_mode(self->camera_ref)) {
        self->L.pos.x += self->L.size * HOME_PORTRAIT_X;
        self->L.pos.y += self->L.size * HOME_PORTRAIT_Y;
    } else {
        self->L.pos.x += self->L.size * HOME_LANDSCAPE_X;
        self->L.pos.y += self->L.size * HOME_LANDSCAPE_Y;
    }
    
    camera_set_pos(self->camera_ref, self->L.pos.x, self->L.pos.y);
    camera_set_zoom(self->camera_ref, self->L.size);
}

bool cameractrl_pointer_event(CameraCtrl *self, ePointer_s pointer) {
    return event_cursor(self, pointer) || event_touch(self, pointer);
}

