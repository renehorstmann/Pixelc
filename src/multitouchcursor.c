#include "r/r.h"
#include "u/pose.h"
#include "m/float.h"
#include "camera.h"
#include "palette.h"
#include "multitouchcursor.h"


#define INNER_RADIUS 16
#define STROKE_RADIUS 1.0
#define START_DISTANCE 32
#define CURSOR_REL_DISTANCE 0.33

struct MultiTouchCursor_Globals multitouchcursor;

//
// private
//

static struct {
    RoBatch cursor;
    vec2 start_pos;
    bool start;
    bool pressed;
} L;

static const vec4 COLOR_NORMAL = {{0.75, 0.75, 0.75, 0.5}};
static const vec4 COLOR_PRESSED = {{1, 1, 1, 0.75}};


static void set_out_pointer(ePointer_s *out_pointer, enum ePointerAction action) {
    ePointer_s pointer = {
            .pos = multitouchcursor.pos,
            .action = action,
            .id = 0
    };

    // transform into the camera view
    pointer.pos = mat4_mul_vec(camera.matrices.v, pointer.pos);

    // call the pointer event of brush
//    brush_pointer_event(multitouchcursor.brush_ref, pointer);
}

static void activate() {
    multitouchcursor.active = true;
    palette_set_info("Multitouch Mode");
}

//
// public
//

void multitouchcursor_init() {
    L.cursor = ro_batch_new(4, r_texture_new_white_pixel());
}


void multitouchcursor_update(float dtime) {
    float x = multitouchcursor.pos.x;
    float y = multitouchcursor.pos.y;

    float left = camera.RO.left;
    float right = camera.RO.right;
    float bottom = camera.RO.bottom;
    float top = camera.RO.top;

    // so it looks like the multitouchcursor is rendered behind the palette
    if(camera_is_portrait_mode()) {
        bottom += palette_get_hud_size();
        y = sca_max(y, bottom);
    } else {
        right -= palette_get_hud_size();
        x = sca_min(x, right);
    }
    
    float xl = x - STROKE_RADIUS;
    float xr = x + STROKE_RADIUS;
    float yb = y - STROKE_RADIUS;
    float yt = y + STROKE_RADIUS;
    float l = x - INNER_RADIUS;
    float r = x + INNER_RADIUS;
    float b = y - INNER_RADIUS;
    float t = y + INNER_RADIUS;

    L.cursor.rects[0].pose = u_pose_new_aa_lrbt(left, l, yb, yt);
    L.cursor.rects[1].pose = u_pose_new_aa_lrbt(r, right, yb, yt);
    L.cursor.rects[2].pose = u_pose_new_aa_lrbt(xl, xr, bottom, b);
    L.cursor.rects[3].pose = u_pose_new_aa_lrbt(xl, xr, t,  top);

    for (int i = 0; i < 4; i++) {
        L.cursor.rects[i].color = L.pressed ? COLOR_PRESSED : COLOR_NORMAL;
    }
}

void multitouchcursor_render(const mat4 *cam_mat) {
    if (!multitouchcursor.active)
        return;
    ro_batch_render(&L.cursor, cam_mat, true);
}

bool multitouchcursor_pointer_event(ePointer_s *in_out_pointer) {
    ePointer_s pointer = *in_out_pointer;

    if (pointer.id == 0 && pointer.action == E_POINTER_UP) {
        if (multitouchcursor.active && L.pressed) {
            // end multitouch mode and reset the pointer to up
            *in_out_pointer = (ePointer_s) {
                    .pos = multitouchcursor.pos,
                    .action = E_POINTER_UP,
                    .id = 0
            };
        }
        multitouchcursor.active = false;
        L.start = false;
        L.pressed = false;
        return false;
    }

    // start phase
    if (!multitouchcursor.active && pointer.id == 0) {
        if (pointer.action == E_POINTER_DOWN) {

            if (palette_contains_pos(pointer.pos.xy)) {

                L.start_pos = pointer.pos.xy;
                L.start = true;
            } else {
                L.start = false;
            }
        }

        if (L.start && pointer.action == E_POINTER_MOVE) {
            if (camera_is_portrait_mode()) {
                if (pointer.pos.y - L.start_pos.y >= START_DISTANCE) {
                    activate();
                }
            } else {
                if (pointer.pos.x - L.start_pos.x <= -START_DISTANCE) {
                    activate();
                }
            }
        }
    }

    // active phase
    if (multitouchcursor.active) {
        if (pointer.id == 0 && pointer.action == E_POINTER_MOVE) {
            multitouchcursor.pos = pointer.pos;
            float cursor_distance = camera.size * CURSOR_REL_DISTANCE;
            if (camera_is_portrait_mode())
                multitouchcursor.pos.y += cursor_distance;
            else
                multitouchcursor.pos.x -= cursor_distance;

            // send MOVE or HOVER, like a real cursor
            *in_out_pointer = (ePointer_s) {
                    .pos = multitouchcursor.pos,
                    .action = L.pressed? E_POINTER_MOVE : E_POINTER_HOVER,
                    .id = 0
            };
        }

        if (pointer.id != 0) {
            if (pointer.action == E_POINTER_DOWN) {
                L.pressed = true;
                *in_out_pointer = (ePointer_s) {
                        .pos = multitouchcursor.pos,
                        .action = E_POINTER_DOWN,
                        .id = 0
                };
            }
            if (pointer.action == E_POINTER_UP) {
                L.pressed = false;
                *in_out_pointer = (ePointer_s) {
                        .pos = multitouchcursor.pos,
                        .action = E_POINTER_UP,
                        .id = 0
                };
            }
        }
    }

    if (multitouchcursor.active && in_out_pointer->id != 0)
        return true;
    return false;
}
