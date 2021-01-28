#include "mathc/float.h"
#include "r/ro_button.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "toolbar.h"


static struct {
	rRoSingle undo;
} L;


static bool in_rect(ePointer_s pointer, mat4 pose) {
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

    mat4 pose_inv = mat4_inv(pose);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv, hud_camera_p_inv);

    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);

    float x = rect_pos.x;
    float y = rect_pos.y;
    
    return x>=-0.5 && x<=0.5 && y>=-0.5 && y<=0.5;
}


void toolbar_init() {
	GLuint undo_tex = r_texture_init_file("res/button_undo.png", NULL);
	r_texture_filter_nearest(undo_tex);
	r_ro_button_init(&L.undo, &hud_camera_p.m00, undo_tex);
	
}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
	if(r_ro_button_clicked(
	    &L.undo, 
	    in_rect(pointer, L.undo.rect.pose),
	    pointer.action == E_POINTER_UP)) {
	    	
	    puts("click");
	}
	
	return false;
}

void toolbar_update(float dtime) {
	//u_pose_set(L.undo.pose, hud_camera_left() + 8, hud_camera_top() - 8, 16, 16, 0);
	
	u_pose_set(&L.undo.rect.pose, 0, -30 - 8, 16, 16, 0);
}

void toolbar_render() {
	r_ro_single_render(&L.undo);
}
