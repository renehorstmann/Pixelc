
#include "button.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "brush.h"
#include "canvas.h"
#include "camera_control.h"
#include "savestate.h"
#include "toolbar.h"

#define MODES 4


static struct {
	rRoSingle undo;
	
	rRoSingle mode[MODES];
	
	rRoSingle camera;
	rRoSingle clear;
	
	float bottom;
} L;

static bool pos_in_toolbar(vec2 pos) {
    return pos.y >= hud_camera_top() - 20;
}

static void unpress_modes(int ignore) {
	for(int i=0; i<MODES; i++) {
		if(i==ignore)
		    continue;
        button_set_pressed(&L.mode[i], false);
	}
}

void toolbar_init() {
	GLuint undo_tex = r_texture_init_file("res/button_undo.png", NULL);
	r_texture_filter_nearest(undo_tex);
    button_init(&L.undo, undo_tex);

    const char *mode_files[MODES] = {
    	"res/button_dot.png",
    	"res/button_free.png",
    	"res/button_fill.png",
    	"res/button_fill8.png"
    };
    
    for(int i=0; i<MODES; i++) {
    	GLuint tex = r_texture_init_file(mode_files[i], NULL);
    r_texture_filter_nearest(tex);

        button_init(&L.mode[i], tex);
    }
	
	button_set_pressed(&L.mode[1], true);
	
	
	GLuint camera_tex = r_texture_init_file("res/button_camera.png", NULL);
	r_texture_filter_nearest(camera_tex);
    button_init(&L.camera, camera_tex);
	
	GLuint clear_tex = r_texture_init_file("res/button_clear.png", NULL);
	r_texture_filter_nearest(clear_tex);
    button_init(&L.clear, clear_tex);

}

void toolbar_update(float dtime) {
	//u_pose_set(L.undo.pose, hud_camera_left() + 8, hud_camera_top() - 8, 16, 16, 0);
	
	float top = hud_camera_top() - 10;
	
	u_pose_set(&L.undo.rect.pose, 
        hud_camera_left()+10, top,
	    16, 16, 0);
	
	for(int i=0; i<MODES; i++) {
		u_pose_set(&L.mode[i].rect.pose, 
		-24+16*i, top, 
		16, 16, 0);
	}
    
    
    u_pose_set(&L.camera.rect.pose,
        hud_camera_right()-30, top,
        16, 16, 0);
        
    u_pose_set(&L.clear.rect.pose,
        hud_camera_right()-10, top,
        16, 16, 0);
}

void toolbar_render() {
	r_ro_single_render(&L.undo);
	for(int i=0; i<MODES; i++) {
		r_ro_single_render(&L.mode[i]);
	}
	r_ro_single_render(&L.camera);
	r_ro_single_render(&L.clear);
}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
    if(!pos_in_toolbar(pointer.pos.xy))
        return false;
        
    if(button_clicked(&L.undo, pointer)) {
        savestate_undo();
    }

    for(int i=0; i<MODES; i++) {
        if(button_pressed(&L.mode[i], pointer)) {

            printf("mode %d\n", i);
            unpress_modes(i);

            if(i==0) {
                brush_set_mode(BRUSH_MODE_DOT);
            } else if(i==1) {
                brush_set_mode(BRUSH_MODE_FREE);
            } else if(i==2) {
            	brush_set_mode(BRUSH_MODE_FILL);
            } else if(i==3) {
            	brush_set_mode(BRUSH_MODE_FILL8);
            }
        }
    }
    
    if(button_clicked(&L.camera, pointer)) {
    	camera_control_set_home();
    }
    
    if(button_clicked(&L.clear, pointer)) {
        canvas_clear();
    }
    
    return true;
}
