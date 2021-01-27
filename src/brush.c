#include "e/input.h"
#include "brush.h"
#include "mathc/float.h"

#include "color.h"
#include "c_camera.h"
#include "io.h"
#include "canvas.h"

static struct {
    Color_s current_color;
    enum brushmodes mode;
    bool drawing;
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

static void dot_mode(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    if (c >= 0 && c < canvas_cols() && r >= 0 && r < canvas_rows()) {
        *layer_pixel(canvas_current_layer(), r, c) = L.current_color;
    }
}

static void free_mode(ePointer_s pointer) {
    if (pointer.action == E_POINTER_DOWN) {
        L.drawing = true;
    } else if (pointer.action != E_POINTER_MOVE) {
        L.drawing = false;
        return;
    }
    if (!L.drawing)
        return;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    if (c >= 0 && c < canvas_cols() && r >= 0 && r < canvas_rows()) {
        *layer_pixel(canvas_current_layer(), r, c) = L.current_color;
    }
}

void brush_pointer_event(ePointer_s pointer) {
    switch (L.mode) {
        case BRUSH_MODE_DOT:
            dot_mode(pointer);
            break;
        case BRUSH_MODE_FREE:
            free_mode(pointer);
            break;
    }

    if (pointer.action == E_POINTER_UP) {
        io_save_layer(*canvas_current_layer(), "sprite.png");
    }
}


void brush_init() {
    L.current_color = COLOR_TRANSPARENT;
    L.mode = BRUSH_MODE_FREE;
}

void brush_set_color(Color_s col) {
    L.current_color = col;
}

void brush_set_mode(enum brushmodes mode) {
    L.mode = mode;
    L.drawing = false;
}
