#include <assert.h>
#include "r/texture.h"
#include "r/ro_text.h"
#include "u/pose.h"
#include "mathc/float.h"
#include "button.h"
#include "camera.h"
#include "brush.h"
#include "brushshape.h"
#include "canvas.h"
#include "canvascamctrl.h"
#include "animation.h"
#include "selection.h"
#include "savestate.h"
#include "toolbar.h"

#define MODES 7
#define LONG_PRESS_TIME 1.0

#define TOOL_MAX 32

struct ToolbarGlobals_s toolbar;


//
// private 
//

typedef struct {
    RoSingle btn;
    float x, y;
} Tool;


static struct {
    Tool tools[TOOL_MAX];
    int tools_size;

    RoSingle *undo;
    RoSingle *clear;
    RoSingle *import;
    RoSingle *selection;
    RoSingle *grid;
    bool grid_status;

    RoSingle *camera;
    RoSingle *animation;
    RoSingle *shade;

    RoSingle *modes[MODES];

    RoSingle *shape_minus;
    RoSingle *shape_plus;

    //non tools:
    RoSingle shape;
    float shape_minus_time, shape_plus_time;

    RoSingle color_bg, color_drop;

    RoSingle selection_copy;
    RoSingle selection_cut;
    RoSingle selection_rotate_left;
    RoSingle selection_rotate_right;
    RoSingle selection_mirror_horizontal;
    RoSingle selection_mirror_vertical;
    RoSingle selection_ok;

    RoSingle layer_prev;
    RoSingle layer_next;
    RoText layer_num;

    bool prev_show_selection_ok;
} L;

static RoSingle *tool_append(float x, float y, const char *btn_file) {
    assert(L.tools_size < TOOL_MAX);
    Tool *self = &L.tools[L.tools_size++];

    self->btn = ro_single_new(camera.gl, r_texture_new_file(2, 1, btn_file));
    self->x = x;
    self->y = y;
    return &self->btn;
}

static bool pos_in_toolbar(vec2 pos) {
    float size = toolbar.show_selection_copy_cut
                 || toolbar.show_selection_ok
                 || canvas_image().layers > 1 ?
                 53 : 34;
    if (camera_is_portrait_mode())
        return pos.y >= camera_top() - size;
    return pos.x <= camera_left() + size;
}

static void unpress(RoSingle **btns, int n, int ignore) {
    for (int i = 0; i < n; i++) {
        if (i == ignore)
            continue;
        button_set_pressed(btns[i], false);
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


//
// public
//

void toolbar_init() {
    L.undo = tool_append(-80, 26, "res/button_undo.png");
    L.clear = tool_append(-80, 9, "res/button_clear.png");
    L.import = tool_append(-62, 9, "res/button_import.png");
    L.selection = tool_append(-44, 9, "res/button_selection.png");
    L.grid = tool_append(80, 26, "res/button_grid.png");
    L.camera = tool_append(80, 9, "res/button_camera.png");
    L.animation = tool_append(64, 26, "res/button_play.png");
    L.shade = tool_append(48, 9, "res/button_shade.png");

    for (int i = 0; i < MODES; i++) {
        L.modes[i] = tool_append(-55 + 16 * i, 26,
                                 (const char *[]) {
                                         "res/button_free.png",
                                         "res/button_dot.png",
                                         "res/button_dither.png",
                                         "res/button_dither2.png",
                                         "res/button_fill.png",
                                         "res/button_fill8.png",
                                         "res/button_replace.png"
                                 }[i]);
    }
    button_set_pressed(L.modes[0], true);

    L.shape_minus = tool_append(9, 9, "res/button_minus.png");
    L.shape_plus = tool_append(25, 9, "res/button_plus.png");


    // shape kernel:
    L.shape = ro_single_new(camera.gl, brushshape_create_kernel_texture(U_COLOR_TRANSPARENT, U_COLOR_WHITE));

    // secondar color:
    L.color_bg = ro_single_new(camera.gl, r_texture_new_file(1, 1, "res/toolbar_color_bg.png"));

    L.color_drop = ro_single_new(camera.gl, r_texture_new_file(1, 1, "res/color_drop.png"));


    // selection buttons:
    L.selection_copy = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_copy.png"));

    L.selection_cut = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_cut.png"));

    L.selection_rotate_left = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_rotate_left.png"));

    L.selection_rotate_right = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_rotate_right.png"));

    L.selection_mirror_horizontal = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_horizontal.png"));

    L.selection_mirror_vertical = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_vertical.png"));

    L.selection_ok = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_ok.png"));

    // layer:
    L.layer_prev = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_prev.png"));

    L.layer_next = ro_single_new(camera.gl, r_texture_new_file(2, 1, "res/button_next.png"));

    L.layer_num = ro_text_new_font55(3, camera.gl);

}

void toolbar_update(float dtime) {
    for (int i = 0; i < L.tools_size; i++) {
        Tool *t = &L.tools[i];
        t->btn.rect.pose = pose16(t->x, t->y);
    }

    // shape kernel:
    L.shape.rect.pose = pose16(-22, 10);  // should be 16x16
    L.shape.rect.sprite.y = brush.shape;

    // secondary color:    
    L.color_bg.rect.pose = L.color_drop.rect.pose = pose16(64, 9);
    L.color_drop.rect.color = u_color_to_vec4(brush.secondary_color);

    // selection buttons:
    if(toolbar.show_selection_ok)
        L.selection_copy.rect.pose = pose16(10, 43);
    else 
        L.selection_copy.rect.pose = pose16(-8, 43);
    L.selection_cut.rect.pose = pose16(8, 43);
    L.selection_rotate_left.rect.pose = pose16(-58, 43);
    L.selection_rotate_right.rect.pose = pose16(-42, 43);
    L.selection_mirror_horizontal.rect.pose = pose16(-26, 43);
    L.selection_mirror_vertical.rect.pose = pose16(-10, 43);
    L.selection_ok.rect.pose = pose16(26, 43);

    // layer:
    L.layer_prev.rect.pose = pose16(50, 43);
    L.layer_next.rect.pose = pose16(80, 43);
    {
        char buf[8];
        sprintf(buf, "%d", canvas.current_layer);
        vec2 size = ro_text_set_text(&L.layer_num, buf);
        float x, y;
        if (camera_is_portrait_mode()) {
            x = 65 - size.x / 2;
            y = camera_top() - 43 + size.y / 2;
        } else {
            x = camera_left() + 43 - size.x / 2;
            y = 65 + size.y / 2;
        }
        u_pose_set_xy(&L.layer_num.pose, floorf(x), floorf(y));
    }

    // shape longpress:
    if (button_is_pressed(L.shape_minus)) {
        L.shape_minus_time += dtime;
        if (L.shape_minus_time > LONG_PRESS_TIME) {
            brush.shape = 0;
        }
    } else
        L.shape_minus_time = 0;

    if (button_is_pressed(L.shape_plus)) {
        L.shape_plus_time += dtime;
        if (L.shape_plus_time > LONG_PRESS_TIME) {
            brush.shape = BRUSH_NUM_SHAPES - 1;
        }
    } else
        L.shape_plus_time = 0;


    // unpress cpy button if selection ok is toggled
    if(!L.prev_show_selection_ok && toolbar.show_selection_ok)
        button_set_pressed(&L.selection_copy, false);
    L.prev_show_selection_ok = toolbar.show_selection_ok;
}

void toolbar_render() {
    for (int i = 0; i < L.tools_size; i++) {
        ro_single_render(&L.tools[i].btn);
    }

    // shape kernel;
    ro_single_render(&L.shape);

    // secondary color:
    ro_single_render(&L.color_bg);
    ro_single_render(&L.color_drop);

    // selection buttons:
    if (toolbar.show_selection_copy_cut) {
        ro_single_render(&L.selection_copy);
        ro_single_render(&L.selection_cut);
    }
    if (toolbar.show_selection_ok) {
        ro_single_render(&L.selection_rotate_left);
        ro_single_render(&L.selection_rotate_right);
        ro_single_render(&L.selection_mirror_horizontal);
        ro_single_render(&L.selection_mirror_vertical);
        ro_single_render(&L.selection_copy);
        ro_single_render(&L.selection_ok);
    }

    if (canvas_image().layers > 1) {
        ro_single_render(&L.layer_prev);
        ro_single_render(&L.layer_next);
        ro_text_render(&L.layer_num);
    }
}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer) {
    if (!pos_in_toolbar(pointer.pos.xy))
        return false;


    if (button_clicked(L.undo, pointer)) {
        log_info("toolbar: undo");
        savestate_undo();
    }

    if (button_clicked(L.clear, pointer)) {
        log_info("toolbar: clear");
        canvas_clear();
    }

    if (button_clicked(L.import, pointer)) {
        log_info("toolbar: import");
        brush_set_selection_active(false, true);
        if (toolbar.show_selection_ok) {
            canvas_redo_image();
        }
        toolbar.show_selection_copy_cut = false;

        uImage img = u_image_new_file(1, canvas.default_import_file);
        button_set_pressed(L.selection, u_image_valid(img));
        toolbar.show_selection_ok = u_image_valid(img);


        if (u_image_valid(img)) {
            selection_init(0, 0, img.cols, img.rows);
            selection_copy(img, 0);
            selection_paste(canvas_image(), canvas.current_layer);
            u_image_kill(&img);
            brush.selection_mode = BRUSH_SELECTION_PASTE;
            brush_set_selection_active(true, false);
        }
        log_trace("toolbar: import finished");
    }

    if (button_toggled(L.selection, pointer)) {
        log_info("toolbar: selection");
        bool pressed = button_is_pressed(L.selection);
        brush_set_selection_active(pressed, true);
        button_set_pressed(&L.selection_copy, false);
        button_set_pressed(&L.selection_cut, false);

        if (!pressed && toolbar.show_selection_ok) {
            canvas_redo_image();
        }
        toolbar.show_selection_copy_cut = false;
        toolbar.show_selection_ok = false;
    }

    if (button_toggled(L.grid, pointer)) {
        log_info("toolbar: grid");
        bool pressed = button_is_pressed(L.grid);
        canvas.show_grid = pressed;

        if (pressed) {
            canvas.alpha = L.grid_status ? 1 : 0.5;
            L.grid_status = !L.grid_status;
        }
    }

    if (button_clicked(L.camera, pointer)) {
        log_info("toolbar: camera");
        canvascamctrl_set_home();
    }

    if (button_toggled(L.animation, pointer)) {
        log_info("toolbar: animation");
        animation.show = button_is_pressed(L.animation);
    }

    if (button_toggled(L.shade, pointer)) {
        log_info("toolbar: shade");
        brush.shading_active = button_is_pressed(L.shade);
    }


    for (int i = 0; i < MODES; i++) {
        if (button_pressed(L.modes[i], pointer)) {
            log_info("toolbar: mode %i", i);
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
            else if (i == 6)
                brush.mode = BRUSH_MODE_REPLACE;
        }
    }

    if (button_clicked(L.shape_minus, pointer)) {
        log_info("toolbar: shape_minus");
        brush.shape--;
        if (brush.shape < 0)
            brush.shape = 0;
    }

    if (button_clicked(L.shape_plus, pointer)) {
        log_info("toolbar: shape_plus");
        brush.shape++;
        if (brush.shape >= BRUSH_NUM_SHAPES)
            brush.shape = BRUSH_NUM_SHAPES - 1;
    }



    // secondary color:
    if (pointer.action == E_POINTER_DOWN && u_pose_aa_contains(L.color_drop.rect.pose, pointer.pos.xy)) {
        log_info("toolbar: secondary_color");
        brush.secondary_color = brush.current_color;
    }


    // selection buttons:
    if (toolbar.show_selection_copy_cut) {
        if (button_toggled(&L.selection_copy, pointer)) {
            log_info("toolbar: selection_copy");
            bool pressed = button_is_pressed(&L.selection_copy);

            if (pressed) {
                button_set_pressed(&L.selection_cut, false);
                brush.selection_mode = BRUSH_SELECTION_COPY;
            }
        }

        if (button_toggled(&L.selection_cut, pointer)) {
            log_info("toolbar: selection_cut");
            bool pressed = button_is_pressed(&L.selection_cut);

            if (pressed) {
                button_set_pressed(&L.selection_copy, false);
                brush.selection_mode = BRUSH_SELECTION_CUT;
            }
        }
    }

    if (toolbar.show_selection_ok) {
        bool changed = false;
        if (button_clicked(&L.selection_rotate_left, pointer)) {
            log_info("toolbar: selection_rotate_left");
            selection_rotate(false);
            changed = true;
        }
        if (button_clicked(&L.selection_rotate_right, pointer)) {
            log_info("toolbar: selection_rotate_right");
            selection_rotate(true);
            changed = true;
        }

        if (button_clicked(&L.selection_mirror_horizontal, pointer)) {
            log_info("toolbar: selection_mirror_horizontal");
            selection_mirror(false);
            changed = true;
        }
        if (button_clicked(&L.selection_mirror_vertical, pointer)) {
            log_info("toolbar: selection_mirror_vertical");
            selection_mirror(true);
            changed = true;
        }

        if (changed) {
            canvas_redo_image();
            selection_paste(canvas_image(), canvas.current_layer);
        }
        
        if (button_clicked(&L.selection_copy, pointer)) {
            log_info("toolbar: selection_copy");
            canvas_save();
        }

        if (button_clicked(&L.selection_ok, pointer)) {
            log_info("toolbar: selection_ok");
            canvas_save();
            brush_set_selection_active(false, true);
            toolbar.show_selection_ok = false;
            button_set_pressed(L.selection, false);
        }
    }


    if (canvas_image().layers > 1) {
        if (button_clicked(&L.layer_prev, pointer)) {
            log_info("toolbar: layer_prev");
            canvas.current_layer = sca_max(0, canvas.current_layer - 1);
        }
        if (button_clicked(&L.layer_next, pointer)) {
            log_info("toolbar: layer_next");
            canvas.current_layer = sca_min(canvas_image().layers - 1, canvas.current_layer + 1);
        }
    }

    return true;
}
