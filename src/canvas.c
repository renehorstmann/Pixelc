#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "c_camera.h"
#include "canvas.h"


static uint8_t *data;
static int cols, rows;
static GLuint tex;
static rRoSingle render;


mat4 canvas_get_pose() {
    return render.rect.pose;
}

int canvas_get_rows() {
    return rows;
}
int canvas_get_cols() {
    return cols;
}

void canvas_set_color(int x, int y, uint32_t color) {
    ((uint32_t *) data)[x + y * cols] = color;
}

void canvas_set_color_rgba(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
    uint32_t color;
    uint8_t *buf = (uint8_t *) &color;
    buf[0] = r;
    buf[1] = g;
    buf[2] = b;
    buf[3] = alpha;
    canvas_set_color(x, y, color);
}

void canvas_init() {
    cols = 31;
    rows = 31;
    data = New0(uint8_t, cols * rows * 4);  //rgba

    for(int i=0; i<31*31; i++)
        canvas_set_color_rgba(i, 0, 128, 128, 0, 255);

    canvas_set_color_rgba(15, 15, 0, 0, 0, 255);

    tex = r_texture_init_empty(false);


    r_ro_single_init(&render, &c_camera_vp.m00, tex);
    u_pose_set(&render.rect.pose, 0, 0, 80, 80, 0);
}

void canvas_update(float dtime) {
    r_texture_update(tex, cols, rows, data);
}

void canvas_render() {
    r_ro_single_render(&render);
}
