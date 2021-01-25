#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "c_camera.h"
#include "canvas.h"


static color *data;
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

void canvas_set_color(int x, int y, color c) {
    ((color *) data)[x + y * cols] = c;
}

void canvas_init() {
    cols = 31;
    rows = 31;
    data = New0(color, cols * rows);  //rgba

    for(int i=0; i<31*31; i++)
        canvas_set_color(i, 0, (color) {128, 128, 0, 255});

    tex = r_texture_init(cols, rows, data);
    r_texture_filter_nearest(tex);


    r_ro_single_init(&render, &c_camera_vp.m00, tex);
    u_pose_set(&render.rect.pose, 0, 0, 80, 80, 0);
}

void canvas_update(float dtime) {
    r_texture_update(tex, cols, rows, data);
}

void canvas_render() {
    r_ro_single_render(&render);
}
