#include <stdbool.h>
#include <float.h>  // FLT_MAX
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "hud_camera.h"
#include "brush.h"
#include "palette.h"


static struct {
    Color_s palette[PALETTE_MAX];
    int palette_size;
    rRoBatch palette_ro;
    rRoSingle select_ro;
    rRoBatch background_ro;
    int last_selected;
    float last_screen_ratio_for_updates;
} L;

static bool pos_in_palette(vec2 pos) {
	int rows = 1 + L.palette_size / PALETTE_COLS;
	if(hud_camera_is_portrait_mode()) {
        return pos.y <= hud_camera_bottom() + rows * 18;		
	}
	return pos.x >= hud_camera_right() - rows * 18;
}


static mat4 setup_palette_color_pose(int r, int c) {
    mat4 pose = mat4_eye();
    u_pose_set_size(&pose, 18, 18);
    if (hud_camera_is_portrait_mode()) {
        u_pose_set_xy(&pose, -81 + c * 18, hud_camera_bottom() + 9 + r * 18);
    } else {
        u_pose_set_xy(&pose, hud_camera_right() - 9 - r * 18, -81 + c * 18);
        u_pose_set_angle(&pose, M_PI_2);
    }
    return pose;
}

static void setup_ro() {
    int last_row = (L.palette_size - 1) / PALETTE_COLS;
    for (int i = 0; i < PALETTE_MAX; i++) {
        int r = i / PALETTE_COLS;
        int c = i % PALETTE_COLS;


        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(r, c);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.palette_ro.rects[i].pose = pose;
        L.background_ro.rects[i].pose = pose;

        vec4 col;
        if (i < L.palette_size)
            col = color_to_vec4(L.palette[i]);
        else
            col = R_COLOR_TRANSPARENT;

        L.palette_ro.rects[i].color = col;


        // background uv
        {
            float u = 0, v = 0;
            if (r < last_row) {
                v = 0.5;
            } else if (i >= L.palette_size) {
                u = 0.5;
            }
            u_pose_set(&L.background_ro.rects[i].uv, u, v, 0.5, 0.5, 0);
        }
    }
    L.select_ro.rect.pose = L.palette_ro.rects[L.last_selected].pose;

    r_ro_batch_update(&L.palette_ro, 0, PALETTE_MAX);
    r_ro_batch_update(&L.background_ro, 0, PALETTE_MAX);
}


void palette_init() {
    GLuint drop_tex = r_texture_init_file("res/palette_color_drop.png", NULL);
    r_texture_filter_nearest(drop_tex);

    r_ro_batch_init(&L.palette_ro, PALETTE_MAX, hud_camera_gl, drop_tex);


    GLuint bg_tex = r_texture_init_file("res/palette_background.png", NULL);
    r_texture_filter_nearest(bg_tex);

    r_ro_batch_init(&L.background_ro, PALETTE_MAX, hud_camera_gl, bg_tex);


    GLuint select_tex = r_texture_init_file("res/palette_select.png", NULL);
    r_texture_filter_nearest(select_tex);
    r_ro_single_init(&L.select_ro, hud_camera_gl, select_tex);

    // default palette:
    {
        Color_s palette[4] = {
                {0,   0,   0,   0},
                {0,   0,   0,   255},
                {128, 128, 128, 255},
                {255, 255, 255, 255}
        };
        palette_set_colors(palette, 4);
    }
}


void palette_update(float dtime) {
    // check update
    float ratio = hud_camera_width() / hud_camera_height();
    bool update = fabsf(ratio - L.last_screen_ratio_for_updates) > 0.01f;
    L.last_screen_ratio_for_updates = ratio;

    if (update) {
        setup_ro();
    }
}

void palette_render() {
    r_ro_batch_render(&L.background_ro);
    r_ro_batch_render(&L.palette_ro);
    r_ro_single_render(&L.select_ro);
}


bool palette_pointer_event(ePointer_s pointer) {
    if(!pos_in_palette(pointer.pos.xy))
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


void palette_set_colors(const Color_s *palette, int size) {
    memcpy(L.palette, palette, sizeof(Color_s) * size);
    L.palette_size = size;
    palette_set_color(0);
}


int palette_get_color() {
    return L.last_selected;
}

void palette_set_color(int index) {
    brush_current_color = L.palette[index];
    L.select_ro.rect.pose = L.palette_ro.rects[index].pose;
    L.last_selected = index;
}