#include "e/input.h"
#include "mathc/float.h"

#include "color.h"
#include "c_camera.h"
#include "io.h"
#include "canvas.h"
#include "brush.h"

static struct {
    Color_s current_color;
    enum brushmodes mode;
    bool drawing;
} L;

static void get_tex_coords(ePointer_s pointer, int *row, int *col) {
    mat4 pose_inv = mat4_inv(canvas_pose());
    vec4 pose_pos = mat4_mul_vec(pose_inv, pointer.pos);

    *row = (0.5 - pose_pos.y) * canvas_image()->rows;
    *col = (pose_pos.x + 0.5) * canvas_image()->cols;
}

static void dot_mode(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    if (c >= 0 && c < img->cols && r >= 0 && r < img->rows) {
        *image_pixel(img, layer, r, c) = L.current_color;
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

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    int r, c;
    get_tex_coords(pointer, &r, &c);

    if (c >= 0 && c < img->cols && r >= 0 && r < img->rows) {
        *image_pixel(img, layer, r, c) = L.current_color;
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
        io_save_image(canvas_image(), "sprite.png");
    }
}


void brush_init() {
    L.current_color = COLOR_TRANSPARENT;
    L.mode = BRUSH_MODE_FREE;
}

void brush_set_color(Color_s col) {
    L.current_color = col;
}


enum brushmodes brush_get_mode() {
    return L.mode;
}

void brush_set_mode(enum brushmodes mode) {
    L.mode = mode;
    L.drawing = false;
}
