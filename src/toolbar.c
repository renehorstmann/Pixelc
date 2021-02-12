#include <assert.h>
#include "r/texture.h"
#include "button.h"
#include "u/pose.h"
#include "camera.h"
#include "brush.h"
#include "brush_shape.h"
#include "canvas.h"
#include "canvas_camera_control.h"
#include "animation.h"
#include "selection.h"
#include "savestate.h"
#include "io.h"
#include "toolbar.h"

#define MODES 6
#define LONG_PRESS_TIME 1.0

#define TOOL_MAX 32

struct ToolbarGlobals_s toolbar;

typedef struct {
	rRoSingle btn;
	float x, y;
} Tool;


static struct {
    Tool tools[TOOL_MAX];
    int tools_size;
    
    Tool *undo;
    
    rRoSingle clear;
    rRoSingle import;

    rRoSingle modes[MODES];

    rRoSingle shape;
    rRoSingle shape_minus, shape_plus;
    float shape_minus_time, shape_plus_time;


    rRoSingle grid;
    rRoSingle camera;
    rRoSingle animation;


    rRoSingle color_bg, color_drop;

    rRoSingle shade;
    
    rRoSingle selection;

    rRoSingle selection_copy;
    rRoSingle selection_cut;
    rRoSingle selection_ok;
    
    float bottom;
} L;

static Tool *tool_append(float x, float y, const char *btn_file) {
	assert(L.tools_size < TOOL_MAX);
	Tool *self = &L.tools[L.tools_size++];
	
	button_init(&self->btn, r_texture_init_file(btn_file, NULL));
	self->x = x;
	self->y = y;
	return self;
}

static bool pos_in_toolbar(vec2 pos) {
    float size = toolbar.show_selection_copy_cut 
            || toolbar.show_selection_ok ?
            53 : 34;
    if (camera_is_portrait_mode())
        return pos.y >= camera_top() - size;
    return pos.x <= camera_left() + size;
}

static void unpress(rRoSingle *btns, int n, int ignore) {
    for (int i = 0; i < n; i++) {
        if (i == ignore)
            continue;
        button_set_pressed(&btns[i], false);
    }
}


static mat4 pose_wh(float col, float row, float w, float h) {
    mat4 pose = mat4_eye();
    if (camera_is_portrait_mode()) {
        u_pose_set(&pose, col, camera_top() - row, w, h, 0);
    } else {
        u_pose_set(&pose, camera_left() + row, col, w, h, 0);
    }
    return pose;
}

static mat4 pose16(float col, float row) {
    return pose_wh(col, row, 16, 16);
}


void toolbar_init() {
    L.undo = tool_append(-80, 26, "res/button_undo.png");
    
    
    button_init(&L.clear, r_texture_init_file("res/button_clear.png", NULL));
    
    button_init(&L.import, r_texture_init_file("res/button_import.png", NULL));

    // modes
    for (int i = 0; i < MODES; i++) {
        button_init(&L.modes[i], r_texture_init_file((const char *[]) {
                "res/button_free.png",
                "res/button_dot.png",
                "res/button_dither.png",
                "res/button_dither2.png",
                "res/button_fill.png",
                "res/button_fill8.png"
        }[i], NULL));
    }
    button_set_pressed(&L.modes[0], true);


    r_ro_single_init(&L.shape, camera.gl, brush_shape_create_kernel_texture(COLOR_TRANSPARENT, COLOR_WHITE));

    button_init(&L.shape_minus, r_texture_init_file("res/button_minus.png", NULL));

    button_init(&L.shape_plus, r_texture_init_file("res/button_plus.png", NULL));





    // helper
    button_init(&L.grid, r_texture_init_file("res/button_grid.png", NULL));

    button_init(&L.camera, r_texture_init_file("res/button_camera.png", NULL));

    button_init(&L.animation, r_texture_init_file("res/button_play.png", NULL));


    r_ro_single_init(&L.color_bg, camera.gl, r_texture_init_file("res/toolbar_color_bg.png", NULL));

    r_ro_single_init(&L.color_drop, camera.gl, r_texture_init_file("res/color_drop.png", NULL));

    button_init(&L.shade, r_texture_init_file("res/button_shade.png", NULL));


    button_init(&L.selection, r_texture_init_file("res/button_selection.png", NULL));
    
    
    button_init(&L.selection_copy, r_texture_init_file("res/button_copy.png", NULL));
    
    button_init(&L.selection_cut, r_texture_init_file("res/button_cut.png", NULL));
    
    button_init(&L.selection_ok, r_texture_init_file("res/button_ok.png", NULL));
    
}

void toolbar_update(float dtime) {
    for(int i=0; i<L.tools_size; i++) {
        Tool *t = &L.tools[i];
        t->btn.rect.pose = pose16(t->x, t->y);
    }
     
    
    L.clear.rect.pose = pose16(-80, 9);
    L.import.rect.pose = pose16(-62, 9);
    L.selection.rect.pose = pose16(-44, 9);


    for (int i = 0; i < MODES; i++) {
        L.modes[i].rect.pose = pose16(-55 + 16 * i, 26);
    }
    
    L.shape.rect.pose = pose16(-22, 10);  // should be 16x16
    L.shape.rect.uv = brush_shape_kernel_texture_uv(brush.shape);

    L.shape_minus.rect.pose = pose16(9, 9);
    L.shape_plus.rect.pose = pose16(25, 9);

    if (button_is_pressed(&L.shape_minus)) {
        L.shape_minus_time += dtime;
        if (L.shape_minus_time > LONG_PRESS_TIME) {
            brush.shape = 0;
        }
    } else
        L.shape_minus_time = 0;

    if (button_is_pressed(&L.shape_plus)) {
        L.shape_plus_time += dtime;
        if (L.shape_plus_time > LONG_PRESS_TIME) {
            brush.shape = BRUSH_NUM_SHAPES - 1;
        }
    } else
        L.shape_plus_time = 0;

    L.grid.rect.pose = pose16(80, 26);
    L.camera.rect.pose = pose16(80, 9);
    L.animation.rect.pose = pose16(64, 26);

    L.color_bg.rect.pose = L.color_drop.rect.pose = pose16(64, 9);
    L.color_drop.rect.color = color_to_vec4(brush.secondary_color);

    L.shade.rect.pose = pose16(48, 9);
    

    L.selection_copy.rect.pose = pose16(-8, 43);
    L.selection_cut.rect.pose = pose16(8, 43);
    L.selection_ok.rect.pose = pose16(0, 43);
}

void toolbar_render() {
    for(int i=0; i<L.tools_size; i++) {
    	r_ro_single_render(&L.tools[i].btn);
    }
    
    r_ro_single_render(&L.clear);
    r_ro_single_render(&L.import);

    for (int i = 0; i < MODES; i++) {
        r_ro_single_render(&L.modes[i]);
    }

    r_ro_single_render(&L.shape);
    r_ro_single_render(&L.shape_minus);
    r_ro_single_render(&L.shape_plus);


    r_ro_single_render(&L.grid);
    r_ro_single_render(&L.camera);
    r_ro_single_render(&L.animation);


    r_ro_single_render(&L.color_bg);
    r_ro_single_render(&L.color_drop);

    r_ro_single_render(&L.shade);
    r_ro_single_render(&L.selection);
    
    if(toolbar.show_selection_copy_cut) {
    	r_ro_single_render(&L.selection_copy);
    	r_ro_single_render(&L.selection_cut);
    }
    if(toolbar.show_selection_ok) {
    	r_ro_single_render(&L.selection_ok);
    }

}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
    if (!pos_in_toolbar(pointer.pos.xy))
        return false;

    if (button_clicked(&L.undo->btn, pointer)) {
        savestate_undo();
    }
    
    if (button_clicked(&L.import, pointer)) {
    	brush_set_selection_active(false, true);
    	if(toolbar.show_selection_ok) {
    		canvas_redo_image();
    	}
    	toolbar.show_selection_copy_cut = false;
    	
    	Image *img = io_load_image("import.png");
    	button_set_pressed(&L.selection, img!=NULL);
    	toolbar.show_selection_ok = img!=NULL;
    	
    	
    	if(img) {
    		selection_init(0, 0, img->cols, img->rows);
    		selection_copy(img, 0);
    		selection_paste(canvas_image(), canvas.current_layer);
    		image_delete(img);
    		brush.selection_mode = BRUSH_SELECTION_PASTE;
    		brush_set_selection_active(true, false);
    	}
    }

    for (int i = 0; i < MODES; i++) {
        if (button_pressed(&L.modes[i], pointer)) {
            unpress(L.modes, MODES, i);

            if (i == 0)
                brush.mode = BRUSH_MODE_FREE;
            else if (i == 1)
                brush.mode = BRUSH_MODE_DOT;
            else if (i == 2)
                brush.mode = BRUSH_MODE_DITHER;
            else if (i == 3)
                brush.mode = BRUSH_MODE_DITHER2;
            else if (i == 4)
                brush.mode = BRUSH_MODE_FILL;
            else if (i == 5)
                brush.mode = BRUSH_MODE_FILL8;
        }
    }

    if (button_clicked(&L.shape_minus, pointer)) {
        brush.shape--;
        if (brush.shape < 0)
            brush.shape = 0;
    }

    if (button_clicked(&L.shape_plus, pointer)) {
        brush.shape++;
        if (brush.shape >= BRUSH_NUM_SHAPES)
            brush.shape = BRUSH_NUM_SHAPES - 1;
    }


    if (button_toggled(&L.grid, pointer)) {
        canvas.show_grid = button_is_pressed(&L.grid);
    }

    if (button_clicked(&L.camera, pointer)) {
        canvas_camera_control_set_home();
    }

    if (button_toggled(&L.animation, pointer)) {
        animation.show = button_is_pressed(&L.animation);
    }

    if (button_clicked(&L.clear, pointer)) {
        canvas_clear();
    }

    if (pointer.action == E_POINTER_DOWN && u_pose_aa_contains(L.color_drop.rect.pose, pointer.pos.xy)) {
        brush.secondary_color = brush.current_color;
    }

    if (button_toggled(&L.shade, pointer)) {
        brush.shading_active = button_is_pressed(&L.shade);
    }

    if(button_toggled(&L.selection, pointer)) {
        bool pressed = button_is_pressed(&L.selection);
        brush_set_selection_active(pressed, true);
        button_set_pressed(&L.selection_copy, false);
        button_set_pressed(&L.selection_cut, false);
        
        if(!pressed && toolbar.show_selection_ok) {
        	canvas_redo_image();
        }
        toolbar.show_selection_copy_cut = false;
        toolbar.show_selection_ok = false;
    }
    
    if(toolbar.show_selection_copy_cut) {
    	if(button_toggled(&L.selection_copy, pointer)) {
    		bool pressed = button_is_pressed(&L.selection_copy);
    		
    		if(pressed) {
    			button_set_pressed(&L.selection_cut, false);
    			brush.selection_mode = BRUSH_SELECTION_COPY;
    		}
    	}
    	
    	if(button_toggled(&L.selection_cut, pointer)) {
    		bool pressed = button_is_pressed(&L.selection_cut);
    		
    		if(pressed) {
    			button_set_pressed(&L.selection_copy, false);
    			brush.selection_mode = BRUSH_SELECTION_CUT;
    		}
    	}
    }
    
    if(toolbar.show_selection_ok) {
    	if(button_clicked(&L.selection_ok, pointer)) {
    		canvas_save();
    		brush_set_selection_active(false, true);
    		toolbar.show_selection_ok = false;
    		button_set_pressed(&L.selection, false);
    	}
    }

    return true;
}
