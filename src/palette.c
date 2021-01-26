#include <stdbool.h>
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "mathc/float.h"
#include "utilc/alloc.h"
#include "hud_camera.h"
#include "brush.h"
#include "palette.h"


static struct {
    color palette[PALETTE_MAX];
    int palette_size;
    rRoBatch ro;
} L;

static bool is_portrait_mode() {
    return hud_camera_height() > hud_camera_width();
}


static bool in_rect(ePointer_s pointer, mat4 pose) {
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

    mat4 pose_inv = mat4_inv(pose);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv, hud_camera_p_inv);

    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);

    float x = rect_pos.x;
    float y = rect_pos.y;
    
    return x>=-1 && x<=1 && y>=-1 && y<=1;
}

static mat4 setup_palette_color_pose(int i) {
    mat4 pose = mat4_eye();
    int cols = 10;
    int r = i / cols;
    int c = i % cols;
    u_pose_set_size(&pose, 8, 8);
    if(is_portrait_mode()) {
        u_pose_set_xy(&pose, -90 + c * 20, hud_camera_bottom() + 10 + r * 20);
    } else {
        u_pose_set_xy(&pose, hud_camera_right() - 10 - r * 20, -90 + c * 20);
    }
    return pose;
}

static void setup_ro() {
    for(int i=0; i<L.palette_size; i++) {
        L.ro.rects[i].pose = setup_palette_color_pose(i);
        L.ro.rects[i].color = color_to_vec4(L.palette[i]);
    }

    r_ro_batch_update(&L.ro, 0, L.ro.num);
}


void palette_init() {
    color *buf = New(color, 64);
    for(int i=0;i<64;i++) 
        buf[i] = COLOR_WHITE;
    GLuint tex = r_texture_init(8, 8, buf);
    r_texture_filter_nearest(tex);
    free(buf);
    
    r_ro_batch_init(&L.ro, PALETTE_MAX, &hud_camera_p.m00, tex);

    for(int i=0; i<PALETTE_MAX; i++) {
        u_pose_set(&L.ro.rects[i].pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.ro.rects[i].color = color_to_vec4(COLOR_TRANSPARENT);
    }
    
    r_ro_batch_update(&L.ro, 0, L.ro.num);


}

bool palette_pointer_event(ePointer_s pointer) {
    if(pointer.action != E_POINTER_DOWN)
        return false;

    for(int i = 0; i<L.palette_size; i++) {
    	if(in_rect(pointer, L.ro.rects[i].pose)) {
    		brush_set_color(L.palette[i]);
    		return true;
    	}
   }  
    
    return false;
}


void palette_set_colors(const color *palette, int size) {
    memcpy(L.palette, palette, sizeof(color) * size);
    L.palette_size = size;
}

void palette_update(float dtime) {
    setup_ro();
}

void palette_render() {
    r_ro_batch_render(&L.ro);
}
