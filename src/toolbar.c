
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
	
	rRoSingle grid;
	rRoSingle camera;
	rRoSingle clear;
	
	float bottom;
} L;

static bool pos_in_toolbar(vec2 pos) {
    if(hud_camera_is_portrait_mode())
        return pos.y >= hud_camera_top() - 20;
    return pos.x <= hud_camera_left() + 20;
}

static void unpress_modes(int ignore) {
	for(int i=0; i<MODES; i++) {
		if(i==ignore)
		    continue;
        button_set_pressed(&L.mode[i], false);
	}
}

static mat4 pose16(float col, float row) {
    mat4 pose = mat4_eye();
    if(hud_camera_is_portrait_mode()) {
        u_pose_set(&pose, col, hud_camera_top() - row, 16, 16, 0);
    } else {
        u_pose_set(&pose, hud_camera_left() + row, col, 16, 16, 0);
    }
    return pose;
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
	
	
	GLuint grid_tex = r_texture_init_file("res/button_grid.png", NULL);
	r_texture_filter_nearest(grid_tex);
    button_init(&L.grid, grid_tex);
	
	GLuint camera_tex = r_texture_init_file("res/button_camera.png", NULL);
	r_texture_filter_nearest(camera_tex);
    button_init(&L.camera, camera_tex);
	
	GLuint clear_tex = r_texture_init_file("res/button_clear.png", NULL);
	r_texture_filter_nearest(clear_tex);
    button_init(&L.clear, clear_tex);

}

void toolbar_update(float dtime) {
    L.undo.rect.pose = pose16(-80, 10);

    for(int i=0; i<MODES; i++) {
        L.mode[i].rect.pose = pose16(-50+16*i, 10);
    }
    
    L.grid.rect.pose = pose16(40, 10);
    L.camera.rect.pose = pose16(60, 10);
    L.clear.rect.pose = pose16(80, 10);
}

void toolbar_render() {
	r_ro_single_render(&L.undo);
	for(int i=0; i<MODES; i++) {
		r_ro_single_render(&L.mode[i]);
	}
	r_ro_single_render(&L.grid);
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

    
    if(button_toggled(&L.grid, pointer)) {
    	canvas_show_grid = button_is_pressed(&L.grid);
    }    
            
    if(button_clicked(&L.camera, pointer)) {
    	camera_control_set_home();
    }
    
    if(button_clicked(&L.clear, pointer)) {
        canvas_clear();
    }
    
    return true;
}
