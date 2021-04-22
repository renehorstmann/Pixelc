#include <float.h>  // FLT_MAX
#include <assert.h>
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "rhc/allocator.h"
#include "camera.h"
#include "brush.h"
#include "palette.h"

#define COLOR_DROP_SIZE 16.0f
#define MAX_ROWS 10

static struct {
    uColor_s palette[PALETTE_MAX];
    int palette_size;
    RoBatch palette_ro;
    RoSingle select_ro;
    RoBatch background_ro;
    int last_selected;
    float last_camera_width, last_camera_height;
} L;

static int palette_cols() {
    assert(camera_width() > 0 && camera_height() > 0 && "startup bug?");
    if (camera_is_portrait_mode())
        return (int) floorf(camera_width() / COLOR_DROP_SIZE);
    return (int) floorf(camera_height() / COLOR_DROP_SIZE);
}

static bool pos_in_palette(vec2 pos) {
    int cols = palette_cols();
    if (camera_is_portrait_mode()) {
        int rows = 1 + L.palette_size / cols;
        return pos.y <= camera_bottom() + rows * COLOR_DROP_SIZE;
    } else {
        int rows = 1 + L.palette_size / cols;
        return pos.x >= camera_right() - rows * COLOR_DROP_SIZE;
    }
}


static mat4 setup_palette_color_pose(int r, int c) {
    mat4 pose = mat4_eye();
    u_pose_set_size(&pose, COLOR_DROP_SIZE, COLOR_DROP_SIZE);
    if (camera_is_portrait_mode()) {
        u_pose_set_xy(&pose, camera_left() + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE,
                      camera_bottom() + COLOR_DROP_SIZE / 2 + r * COLOR_DROP_SIZE);
    } else {
        u_pose_set_xy(&pose, camera_right() - COLOR_DROP_SIZE / 2 - r * COLOR_DROP_SIZE,
                      camera_bottom() + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE);
        u_pose_set_angle(&pose, M_PI_2);
    }
    return pose;
}

void palette_init() {
    L.palette_ro = ro_batch_new(PALETTE_MAX, camera.gl, r_texture_new_file(1, 1, "res/color_drop.png"));

    L.background_ro = ro_batch_new(PALETTE_MAX + MAX_ROWS, camera.gl,
                    r_texture_new_file(2, 2, "res/palette_background.png"));

    L.select_ro = ro_single_new(camera.gl, r_texture_new_file(1, 1, "res/palette_select.png"));

    // default palette:
    {
        uColor_s palette[4] = {
                {0,   0,   0,   0},
                {0,   0,   0,   255},
                {128, 128, 128, 255},
                {255, 255, 255, 255}
        };
        palette_set_colors(palette, 4);
    }
}


void palette_update(float dtime) {
    int cols = palette_cols();
    int last_row = (L.palette_size - 1) / cols;
    for (int i = 0; i < PALETTE_MAX; i++) {
        int r = i / cols;
        int c = i % cols;

        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(r, c);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.palette_ro.rects[i].pose = pose;
        L.background_ro.rects[i].pose = pose;

        // color
        vec4 col;
        if (i < L.palette_size)
            col = u_color_to_vec4(L.palette[i]);
        else
            col = R_COLOR_TRANSPARENT;

        L.palette_ro.rects[i].color = col;


        // background sprite
        {
            float u = i < L.palette_size ? 0 : 1;
            float v = r < last_row ? 1 : 0;
            L.background_ro.rects[i].sprite = (vec2) {{u, v}};
        }
    }

    // background continuation
    for (int r = 0; r < MAX_ROWS; r++) {
        int idx = L.background_ro.num - r - 1;
        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(r, cols);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.background_ro.rects[idx].pose = pose;

        // background uv
        {
            float u = 1;
            float v = r < last_row ? 1 : 0;
            L.background_ro.rects[idx].sprite = (vec2) {{u, v}};
        }
    }

    L.select_ro.rect.pose = L.palette_ro.rects[L.last_selected].pose;

    ro_batch_update(&L.palette_ro);
    ro_batch_update(&L.background_ro);
}

void palette_render() {
    ro_batch_render(&L.background_ro);
    ro_batch_render(&L.palette_ro);
    ro_single_render(&L.select_ro);
}


bool palette_pointer_event(ePointer_s pointer) {
    if (!pos_in_palette(pointer.pos.xy))
        return false;

    if (pointer.action != E_POINTER_DOWN)
        return true;

    for (int i = 0; i < L.palette_size; i++) {
        if (u_pose_aa_contains(L.palette_ro.rects[i].pose, pointer.pos.xy)) {
            palette_set_color(i);
            return true;
        }
    }

    return true;
}

float palette_get_hud_size() {
    int cols = palette_cols();
    int rows = 1 + L.palette_size / cols;
    return rows * COLOR_DROP_SIZE;
}

void palette_set_colors(const uColor_s *palette, int size) {
    assert(size < PALETTE_MAX);
    memcpy(L.palette, palette, sizeof(uColor_s) * size);
    L.palette_size = size;
    palette_set_color(0);
}


int palette_get_color() {
    return L.last_selected;
}

void palette_set_color(int index) {
    brush.current_color = L.palette[index];
    L.select_ro.rect.pose = L.palette_ro.rects[index].pose;
    L.last_selected = index;
}
