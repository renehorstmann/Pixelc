#include "e/input.h"
#include "brush.h"
#include "mathc/float.h"

#include "color.h"
#include "c_camera.h"
#include "canvas.h"

static struct {
   color current_color;
} L;

static void get_tex_coords(ePointer_s pointer, int *row, int *col) {
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

    mat4 pose_inv = mat4_inv(canvas_pose());
    mat4 pose_inv_v = mat4_mul_mat(pose_inv, c_camera_v);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv_v, c_camera_p_inv);

    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);

    *row = (1 - rect_pos.y) / 2 * canvas_rows();
    *col = (rect_pos.x + 1) / 2 * canvas_cols();
}

void brush_pointer_event(ePointer_s pointer) {
    if(!(pointer.action == E_POINTER_DOWN || pointer.action == E_POINTER_MOVE))
        return;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    if(c>=0 && c<canvas_cols() && r>=0 && r < canvas_rows()) {
        *layer_pixel(canvas_current_layer(), r, c) = L.current_color;
    }
}


void brush_init() {
    L.current_color = COLOR_RED;
}

void brush_set_color(color col) {
    L.current_color = col;
}
