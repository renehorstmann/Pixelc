#include "r/r.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "mathc/float.h"
#include "multitouchcursor.h"


#define INNER_RADIUS 16
#define STROKE_RADIUS 1.0
#define START_DISTANCE 32
#define CURSOR_DISTANCE 64


//
// private
//

static const vec4 COLOR_NORMAL = {{0.75, 0.75, 0.75, 0.5}};
static const vec4 COLOR_PRESSED = {{1, 1, 1, 0.75}};


static void set_out_pointer(const MultiTouchCursor *self, ePointer_s *out_pointer, enum ePointerAction action) {
    ePointer_s pointer = {
            .pos = self->pos,
            .action = action,
            .id = 0
    };

    // transform into the camera view
    pointer.pos = mat4_mul_vec(self->cam_ref->matrices.v, pointer.pos);

    // call the pointer event of brush
//    brush_pointer_event(self->brush_ref, pointer);
}

static void activate(MultiTouchCursor *self) {
    self->active = true;
    palette_set_info(self->palette_ref, "Multitouch Mode");
}

//
// public
//

MultiTouchCursor *multitouchcursor_new(const Camera_s *cam, Palette *palette) {
    MultiTouchCursor *self = rhc_calloc(sizeof *self);

    self->cam_ref = cam;
    self->palette_ref = palette;

    self->L.cursor = ro_batch_new(4, r_texture_new_white_pixel());
    

    return self;
}

void multitouchcursor_kill(MultiTouchCursor **self_ptr) {
    MultiTouchCursor *self = *self_ptr;
    if (!self)
        return;

    ro_batch_kill(&self->L.cursor);

    rhc_free(self);
    *self_ptr = NULL;
}

void multitouchcursor_update(MultiTouchCursor *self, float dtime) {
    const Camera_s *cam = self->cam_ref;

    float x = self->pos.x;
    float y = self->pos.y;
    float xl = x - STROKE_RADIUS;
    float xr = x + STROKE_RADIUS;
    float yb = y - STROKE_RADIUS;
    float yt = y + STROKE_RADIUS;
    float l = x - INNER_RADIUS;
    float r = x + INNER_RADIUS;
    float b = y - INNER_RADIUS;
    float t = y + INNER_RADIUS;

    self->L.cursor.rects[0].pose = u_pose_new_aa_lrbt(cam->RO.left, l, yb, yt);
    self->L.cursor.rects[1].pose = u_pose_new_aa_lrbt(r, cam->RO.right, yb, yt);
    self->L.cursor.rects[2].pose = u_pose_new_aa_lrbt(xl, xr, cam->RO.bottom, b);
    self->L.cursor.rects[3].pose = u_pose_new_aa_lrbt(xl, xr, t, cam->RO.top);
    
    for (int i = 0; i < 4; i++) {
        self->L.cursor.rects[i].color = self->L.pressed ? COLOR_PRESSED : COLOR_NORMAL;
    }
}

void multitouchcursor_render(const MultiTouchCursor *self, const mat4 *cam_mat) {
    if(!self->active)
        return;
    ro_batch_render(&self->L.cursor, cam_mat, true);
}

bool multitouchcursor_pointer_event(MultiTouchCursor *self, ePointer_s *in_out_pointer) {
    ePointer_s pointer = *in_out_pointer;

    if (pointer.id == 0 && pointer.action == E_POINTER_UP) {
        if(self->active && self->L.pressed) {
            // end multitouch mode and reset the pointer to up
            *in_out_pointer = (ePointer_s) {
                    .pos = self->pos,
                    .action = E_POINTER_UP,
                    .id = 0
            };
        }
        self->active = false;
        self->L.start = false;
        self->L.pressed = false;
        return false;
    }

    // start phase
    if (!self->active && pointer.id == 0) {
        if (pointer.action == E_POINTER_DOWN) {

            if (palette_contains_pos(self->palette_ref, pointer.pos.xy)) {

                self->L.start_pos = pointer.pos.xy;
                self->L.start = true;
            } else {
                self->L.start = false;
            }
        }

        if (self->L.start && pointer.action == E_POINTER_MOVE) {
            if (camera_is_portrait_mode(self->cam_ref)) {
                if (pointer.pos.y - self->L.start_pos.y >= START_DISTANCE) {
                    activate(self);
                }
            } else {
                if (pointer.pos.x - self->L.start_pos.x <= -START_DISTANCE) {
                    activate(self);
                }
            }
        }
    }

    // active phase
    if (self->active) {
        if (pointer.id == 0 && pointer.action == E_POINTER_MOVE) {
            self->pos = pointer.pos;
            if (camera_is_portrait_mode(self->cam_ref))
                self->pos.y += CURSOR_DISTANCE;
            else
                self->pos.x -= CURSOR_DISTANCE;

            // send MOVE always, like a real cursor
            *in_out_pointer = (ePointer_s) {
                    .pos = self->pos,
                    .action = E_POINTER_MOVE,
                    .id = 0
            };
        }

        if (pointer.id != 0) {
            if(pointer.action == E_POINTER_DOWN) {
                self->L.pressed = true;
                *in_out_pointer = (ePointer_s) {
                        .pos = self->pos,
                        .action = E_POINTER_DOWN,
                        .id = 0
                };
            }
            if(pointer.action == E_POINTER_UP) {
                self->L.pressed = false;
                *in_out_pointer = (ePointer_s) {
                        .pos = self->pos,
                        .action = E_POINTER_UP,
                        .id = 0
                };
            }
        }
    }
    
    if(self->active && in_out_pointer->id !=0)
        return true;
    return false;
}
