
#include "button.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "brush.h"
#include "canvas.h"
#include "camera_control.h"
#include "animation.h"
#include "savestate.h"
#include "toolbar.h"

#define MODES 4
#define SHAPES 3
#define SIZES 3


static struct {
	rRoSingle undo;
	rRoSingle clear;
	
	rRoSingle modes[MODES];
	rRoSingle shapes[SHAPES];
	rRoSingle sizes[SIZES];
	
	rRoSingle grid;
	rRoSingle camera;
	rRoSingle animation;
	
	
	rRoSingle color_bg, color_drop;
	
	rRoSingle shade;
	
	float bottom;
} L;

static bool pos_in_toolbar(vec2 pos) {
    if(hud_camera_is_portrait_mode())
        return pos.y >= hud_camera_top() - 34;
    return pos.x <= hud_camera_left() + 34
    ;
}

static void unpress(rRoSingle *btns, int n, int ignore) {
	for(int i=0; i<n; i++) {
		if(i==ignore)
		    continue;
        button_set_pressed(&btns[i], false);
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
    button_init(&L.undo, r_texture_init_file("res/button_undo.png", NULL));
    
    button_init(&L.clear, r_texture_init_file("res/button_clear.png", NULL));

    for(int i=0; i<MODES; i++) {
        button_init(&L.modes[i], r_texture_init_file((const char *[]) {
    	        "res/button_free.png",
    	        "res/button_dot.png",
            	"res/button_fill.png",
    	        "res/button_fill8.png"
    	        }[i], NULL));
    }
    button_set_pressed(&L.modes[0], true);
    
    for(int i=0; i<SHAPES; i++) {
    	button_init(&L.shapes[i], r_texture_init_file((const char *[]) {
    	        "res/button_dot.png",
    	        "res/button_dither.png",
    	        "res/button_dither2.png"
    	        }[i], NULL));
    }
	button_set_pressed(&L.shapes[0], true);
	
	for(int i=0; i<SIZES; i++) {
    	button_init(&L.sizes[i], r_texture_init_file((const char *[]) {
    	        "res/button_dot.png",
            	"res/button_large.png",
            	"res/button_xlarge.png"
    	        }[i], NULL));
    }
	button_set_pressed(&L.sizes[0], true);
	
	
    button_init(&L.grid, r_texture_init_file("res/button_grid.png", NULL));
	
    button_init(&L.camera, r_texture_init_file("res/button_camera.png", NULL));
    
    button_init(&L.animation, r_texture_init_file("res/button_play.png", NULL));
    

    r_ro_single_init(&L.color_bg, hud_camera_gl, r_texture_init_file("res/toolbar_color_bg.png", NULL));
    
    r_ro_single_init(&L.color_drop, hud_camera_gl, r_texture_init_file("res/color_drop.png", NULL));
    
    button_init(&L.shade, r_texture_init_file("res/button_shade.png", NULL));
    
}

void toolbar_update(float dtime) {
    L.undo.rect.pose = pose16(-80, 26);
    L.clear.rect.pose = pose16(-80, 9);

    for(int i=0; i<MODES; i++) {
        L.modes[i].rect.pose = pose16(-60+16*i, 26);
    }
    
    for(int i=0; i<SHAPES; i++) {
    	L.shapes[i].rect.pose = pose16(-60 +16*i, 9);
    }
    
    for(int i=0; i<SIZES; i++) {
    	L.sizes[i].rect.pose = pose16(-8 +16*i, 9);
    }
    
    L.grid.rect.pose = pose16(80, 26);
    L.camera.rect.pose = pose16(80, 9);
    L.animation.rect.pose = pose16(64, 26);
    
    L.color_bg.rect.pose = L.color_drop.rect.pose = pose16(64, 10);
    L.color_drop.rect.color = color_to_vec4(brush_secondary_color);
    
    L.shade.rect.pose = pose16(48, 10);
}

void toolbar_render() {
	r_ro_single_render(&L.undo);
	r_ro_single_render(&L.clear);
	
	for(int i=0; i<MODES; i++) {
		r_ro_single_render(&L.modes[i]);
	}
	for(int i=0; i<SHAPES; i++) {
		r_ro_single_render(&L.shapes[i]);
	}
	for(int i=0; i<SIZES; i++) {
		r_ro_single_render(&L.sizes[i]);
	}
	
	r_ro_single_render(&L.grid);
	r_ro_single_render(&L.camera);
	r_ro_single_render(&L.animation);
	
	
	r_ro_single_render(&L.color_bg);
	r_ro_single_render(&L.color_drop);
	
	r_ro_single_render(&L.shade);
}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
    if(!pos_in_toolbar(pointer.pos.xy))
        return false;
        
    if(button_clicked(&L.undo, pointer)) {
        savestate_undo();
    }

    for(int i=0; i<MODES; i++) {
        if(button_pressed(&L.modes[i], pointer)) {
            unpress(L.modes, MODES, i);

            if(i==0) {
                brush_mode = BRUSH_MODE_FREE;
            } else if(i==1) {
                brush_mode = BRUSH_MODE_DOT;
            } else if(i==2) {
            	brush_mode = BRUSH_MODE_FILL;
            } else if(i==3) {
            	brush_mode = BRUSH_MODE_FILL8;
            }
        }
    }
    
    for(int i=0; i<SHAPES; i++) {
        if(button_pressed(&L.shapes[i], pointer)) {
            unpress(L.shapes, SHAPES, i);

            if(i==0) {
            	brush_shape = BRUSH_SHAPE_DOT;
            } else if(i==1) {
            	brush_shape = BRUSH_SHAPE_DITHER;
            } else if(i==2) {
            	brush_shape = BRUSH_SHAPE_DITHER2;
            }
        }
    }
    
    for(int i=0; i<SIZES; i++) {
        if(button_pressed(&L.sizes[i], pointer)) {
            unpress(L.sizes, SIZES, i);

            if(i==0) {
            	brush_size = BRUSH_SIZE_1;
            } else if(i==1) {
            	brush_size = BRUSH_SIZE_3;
            } else if(i==2) {
            	brush_size = BRUSH_SIZE_5;
            }
        }
    }

    
    if(button_toggled(&L.grid, pointer)) {
    	canvas_show_grid = button_is_pressed(&L.grid);
    }    
            
    if(button_clicked(&L.camera, pointer)) {
    	camera_control_set_home();
    }
    
    if(button_toggled(&L.animation, pointer)) {
    	animation_show = button_is_pressed(&L.animation);
    }   
    
    if(button_clicked(&L.clear, pointer)) {
        canvas_clear();
    }
    
    if(u_pose_aa_contains(L.color_drop.rect.pose, pointer.pos.xy)) {
    	brush_secondary_color = brush_current_color;
    }
    
    if(button_toggled(&L.shade, pointer)) {
    	brush_shading_active = button_is_pressed(&L.shade);
    }
    
    return true;
}
