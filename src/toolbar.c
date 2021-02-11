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
#include "toolbar.h"

#define MODES 6
#define LONG_PRESS_TIME 1.0


static struct {
    rRoSingle undo;
    rRoSingle clear;

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


    float bottom;
} L;

static bool pos_in_toolbar(vec2 pos) {
    if (camera_is_portrait_mode())
        return pos.y <= camera_top() + 34;
    return pos.x <= camera_left() + 34;
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
        u_pose_set(&pose, col, camera_top() + row, w, h, 0);
    } else {
        u_pose_set(&pose, camera_left() + row, col, w, h, 0);
    }
    return pose;
}

static mat4 pose16(float col, float row) {
    return pose_wh(col, row, 16, 16);
}


void toolbar_init() {
    button_init(&L.undo, r_texture_init_file("res/button_undo.png", NULL));

    button_init(&L.clear, r_texture_init_file("res/button_clear.png", NULL));

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
}
const vec4 vertices[6] = {
        {-0.5, -0.5, 0, 1},
        {+0.5, -0.5, 0, 1},
        {-0.5, +0.5, 0, 1},
        {-0.5, +0.5, 0, 1},
        {+0.5, -0.5, 0, 1},
        {+0.5, +0.5, 0, 1}
};

void toolbar_update(float dtime) {
    L.undo.rect.pose = pose16(-80, 26);
    L.clear.rect.pose = pose16(-80, 9);

    for (int i = 0; i < MODES; i++) {
        L.modes[i].rect.pose = pose16(-60 + 16 * i, 9);
    }
    
    L.shape.rect.pose = pose_wh(-60, 26,
                                BRUSH_KERNEL_TEXTURE_SIZE*2, BRUSH_KERNEL_TEXTURE_SIZE*2);  // should be 16x16
    L.shape.rect.uv = brush_shape_kernel_texture_uv(brush.shape);

    L.shape_minus.rect.pose = pose16(0, 26);
    L.shape_plus.rect.pose = pose16(16, 26);

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

    L.color_bg.rect.pose = L.color_drop.rect.pose = pose16(64, 10);
    L.color_drop.rect.color = color_to_vec4(brush.secondary_color);

    L.shade.rect.pose = pose16(48, 10);
    
    L.selection.rect.pose = pose16(48, 26);

}

void toolbar_render() {
    r_ro_single_render(&L.undo);
    r_ro_single_render(&L.clear);

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

}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
    if (!pos_in_toolbar(pointer.pos.xy))
        return false;

    if (button_clicked(&L.undo, pointer)) {
        savestate_undo();
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
    	if(button_is_pressed(&L.selection)) {
    		selection_init(-5, 5, 10, 10);
    	} else {
    		selection_kill();
    	}
    	
    }

    return true;
}
