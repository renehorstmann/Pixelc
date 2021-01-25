#include <stdbool.h>
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "mathc/float.h"
#include "utilc/alloc.h"
#include "color.h"
#include "hud_camera.h"
#include "brush.h"
#include "palette.h"


static struct {
    int rows, cols;
    color *palette;
    rRoBatch ro;
} L;


static bool in_rect(ePointer_s pointer, mat4 pose) {
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

    mat4 pose_inv = mat4_inv(pose);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv, hud_camera_p_inv);

    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);

    float x = rect_pos.x;
    float y = rect_pos.y;
    
    return x>=-1 && x<=1 && y>=-1 && y<=1;
}


void palette_init() {
    L.rows = 2;
    L.cols = 8;
    L.palette = New(color, L.rows * L.cols);
    
    for(int r=0; r<L.rows; r++) {
    	for(int c=0; c<L.cols; c++) {
    	   	int index = c + r * L.cols;
           	L.palette[index] = (color) {r * 255 / (L.rows- 1), (L.rows-r) * 255 / L.rows, c * 255 / (L.cols - 1), 255};
        }
    }
    
    color *buf = New(color, 64);
    for(int i=0;i<64;i++) 
        buf[i] = COLOR_WHITE;
    GLuint tex = r_texture_init(8, 8, buf);
    r_texture_filter_nearest(tex);
    free(buf);
    
    r_ro_batch_init(&L.ro, L.rows * L.cols, &hud_camera_p.m00, tex);
    
    for(int r=0; r<L.rows; r++) {
    	for(int c=0; c<L.cols; c++) {
    	    int index = c + r * L.cols;
    	   
    	    mat4 pose = mat4_eye();
    	    u_pose_set_size(&pose, 8, 8);
    	    u_pose_set_xy(&pose, -80 + c * 20, -110 - r * 20);    	    
    	    
    	    L.ro.rects[index].pose = pose;
    	    L.ro.rects[index].color = color_to_float(L.palette[index]);
    	}
    }
    
    r_ro_batch_update(&L.ro, 0, L.rows * L.cols);
}

bool palette_pointer_event(ePointer_s pointer) {
    for(int i = 0; i<L.rows  * L.cols; i++) {
    	if(in_rect(pointer, L.ro.rects[i].pose)) {
    		brush_set_color(L.palette[i]);
    		return true;
    	}
   }  
    
    return false;
}

void palette_update(float dtime) {

}

void palette_render() {
    r_ro_batch_render(&L.ro);
}
