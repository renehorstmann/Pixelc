#include "e/input.h"
#include "c_input.h"
#include "mathc/float.h"

#include "color.h"
#include "c_camera.h"
#include "canvas.h"

void pointer_event(ePointer_s pointer, void *user_data) {
    if(!(pointer.action == E_POINTER_DOWN || pointer.action == E_POINTER_MOVE))
        return;
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

//    printf("screen_pos: ");
//    vec4_println(screen_pos);
//
//    vec4 coords_pos = mat4_mul_vec(c_camera_p_inv, screen_pos);
//    printf("coords_pos: ");
//    vec4_println(coords_pos);
//
//    vec4 view_pos = mat4_mul_vec(c_camera_v, coords_pos);
//    printf("view_pos: ");
//    vec4_println(view_pos);
//
//    vec4 tex_pos = mat4_mul_vec(mat4_inv(canvas_get_pose()), view_pos);
//    printf("tex_pos: ");
//    vec4_println(tex_pos);

    // screen_to_rect = inv(pose) @ v @ inv(p) @ screen_pos
    mat4 pose_inv = mat4_inv(canvas_get_pose());
    mat4 pose_inv_v = mat4_mul_mat(pose_inv, c_camera_v);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv_v, c_camera_p_inv);
    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);
    printf("rect_pos: ");
    vec4_println(rect_pos);

    int x = (rect_pos.x + 1) / 2 * canvas_get_cols();
    int y = (1 - rect_pos.y) / 2 * canvas_get_rows();

    if(x>=0 && x<canvas_get_cols() && y>=0 && y<canvas_get_rows()) {
        canvas_set_color(x, y, (color) {0, 255, 0, 255});
    }
}


void c_input_init() {
    e_input_register_pointer_event(pointer_event, NULL);
}
