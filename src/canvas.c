#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"

#include "c_camera.h"
#include "canvas.h"


static uint8_t *canvas_data;
static int canvas_w, canvas_h;
static GLuint canvas_tex;
static rSingle draw_rect;



void canvas_set_color(int x, int y, uint32_t color) {
    ((uint32_t *) canvas_data)[x + y * canvas_w] = color;
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
    canvas_w = 32;
    canvas_h = 32;
    canvas_data = New0(uint8_t, canvas_w * canvas_h * 4);  //rgba

    for(int i=0; i<32*32; i++)
        canvas_set_color_rgba(i, 0, 128, 128, 0, 255);

    canvas_tex = r_texture_init_empty(false);


    r_single_init(&draw_rect, &camera_vp.m00, canvas_tex);
    u_pose_set(&draw_rect.rect.pose, 0, 0, 80, 80, 0);
}

void canvas_update(float dtime) {
    r_texture_update(canvas_tex, canvas_w, canvas_h, canvas_data);
}

void canvas_render() {
    r_single_render(&draw_rect);
}
