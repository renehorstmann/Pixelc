#include "mathc/float.h"
#include "button.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "brush.h"
#include "toolbar.h"


static struct {
	rRoSingle undo;
	
	rRoSingle mode[4];
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

static void unpress_modes(int ignore) {
	for(int i=0; i<4; i++) {
		if(i==ignore)
		    continue;
        button_set_pressed(&L.mode[i], false);
	}
}

void toolbar_init() {
	GLuint undo_tex = r_texture_init_file("res/button_undo.png", NULL);
	r_texture_filter_nearest(undo_tex);
    button_init(&L.undo, undo_tex);

    const char *mode_files[4] = {
    	"res/button_dot.png",
    	"res/button_free.png",
    	"res/button_fill.png",
    	"res/button_fill.png"
    };
    
    for(int i=0; i<4; i++) {
    	GLuint tex = r_texture_init_file(mode_files[i], NULL);
    r_texture_filter_nearest(tex);

        button_init(&L.mode[i], tex);
    }
	
}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
	if(button_clicked(&L.undo, pointer)) {
	    	
	    puts("click");
	    
	    unpress_modes(-1);
	}
	
	for(int i=0; i<4; i++) {
		if(button_pressed(&L.mode[i], pointer)) {
			
			printf("mode %d\n", i);
			unpress_modes(i);
			
			if(i==0) {
				brush_set_mode(BRUSH_MODE_DOT);
			} else if(i==1) {
				brush_set_mode(BRUSH_MODE_FREE);
			}
		}
	}
	
	return false;
}

void toolbar_update(float dtime) {
	//u_pose_set(L.undo.pose, hud_camera_left() + 8, hud_camera_top() - 8, 16, 16, 0);
	
	u_pose_set(&L.undo.rect.pose, 0, -20, 16, 16, 0);
	
	for(int i=0; i<4; i++) {
		u_pose_set(&L.mode[i].rect.pose, -24+16*i, -40, 16, 16, 0);
	}
}

void toolbar_render() {
	r_ro_single_render(&L.undo);
	for(int i=0; i<4; i++) {
		r_ro_single_render(&L.mode[i]);
	}
}
