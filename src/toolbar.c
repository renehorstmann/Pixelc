#include <assert.h>
#include "r/texture.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "u/pose.h"
#include "mathc/sca/int.h"
#include "mathc/float.h"
#include "button.h"
#include "brushshape.h"
#include "toolbar.h"

#define LONG_PRESS_TIME 1.0

typedef struct Toolbar_Tool Tool;

//
// private 
//


static RoSingle *tool_append(Toolbar *self, float x, float y, const char *btn_file) {
    assert(self->L.tools_size < TOOLBAR_TOOL_MAX);
    Tool *tool = &self->L.tools[self->L.tools_size++];

    tool->btn = ro_single_new(r_texture_new_file(2, 1, btn_file));
    tool->x = x;
    tool->y = y;
    return &tool->btn;
}

static bool pos_in_toolbar(const Toolbar *self, vec2 pos) {
    float size = self->show_selection_copy_cut
                 || self->show_selection_ok
                 || self->canvas_ref->RO.image.layers > 1 ?
                 53 : 34;
    if (camera_is_portrait_mode(self->camera_ref))
        return pos.y >= self->camera_ref->RO.top - size;
    return pos.x <= self->camera_ref->RO.left + size;
}

static void unpress(RoSingle **btns, int n, int ignore) {
    for (int i = 0; i < n; i++) {
        if (i == ignore)
            continue;
        button_set_pressed(&btns[i]->rect, false);
    }
}


static mat4 pose_wh(const Camera_s *camera, float col, float row, float w, float h) {
    mat4 pose = mat4_eye();
    if (camera_is_portrait_mode(camera)) {
        u_pose_set(&pose, col, camera->RO.top - row, w, h, 0);
    } else {
        u_pose_set(&pose, camera->RO.left + row, col, w, h, 0);
    }
    return pose;
}

static mat4 pose16(const Camera_s *camera, float col, float row) {
    return pose_wh(camera, col, row, 16, 16);
}


//
// public
//

Toolbar *toolbar_new(const Camera_s *camera,
                     Canvas *canvas,
                     Brush *brush,
                     SelectionCtrl *selectionctrl,
                     CameraCtrl *canvascamctrl,
                     Animation *animation) {
    Toolbar *self = rhc_calloc(sizeof *self);

    self->camera_ref = camera;
    self->canvas_ref = canvas;
    self->brush_ref = brush;
    self->selectionctrl_ref = selectionctrl;
    self->canvascamctrl_ref = canvascamctrl;
    self->animation_ref = animation;

    self->L.undo = tool_append(self, -80, 26, "res/button_undo.png");
    self->L.clear = tool_append(self, -80, 9, "res/button_clear.png");
    self->L.import = tool_append(self, -62, 9, "res/button_import.png");
    self->L.selection = tool_append(self, -44, 9, "res/button_selection.png");
    self->L.grid = tool_append(self, 80, 26, "res/button_grid.png");
    self->L.camera = tool_append(self, 80, 9, "res/button_camera.png");
    self->L.animation = tool_append(self, 64, 26, "res/button_play.png");
    self->L.shade = tool_append(self, 48, 9, "res/button_shade.png");

    for (int i = 0; i < TOOLBAR_MODES; i++) {
        self->L.modes[i] = tool_append(self, -55 + 16 * i, 26,
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
    button_set_pressed(&self->L.modes[0]->rect, true);

    self->L.shape_minus = tool_append(self, 9, 9, "res/button_minus.png");
    self->L.shape_plus = tool_append(self, 25, 9, "res/button_plus.png");


    // shape kernel:
    self->L.shape = ro_single_new(brushshape_create_kernel_texture(U_COLOR_TRANSPARENT, U_COLOR_WHITE));

    // secondar color:
    self->L.color_bg = ro_single_new(r_texture_new_file(1, 1, "res/toolbar_color_bg.png"));

    self->L.color_drop = ro_single_new(r_texture_new_file(1, 1, "res/color_drop.png"));


    // selection buttons:
    self->L.selection_copy = ro_single_new(r_texture_new_file(2, 1, "res/button_copy.png"));

    self->L.selection_cut = ro_single_new(r_texture_new_file(2, 1, "res/button_cut.png"));

    self->L.selection_rotate_left = ro_single_new(r_texture_new_file(2, 1, "res/button_rotate_left.png"));

    self->L.selection_rotate_right = ro_single_new(r_texture_new_file(2, 1, "res/button_rotate_right.png"));

    self->L.selection_mirror_horizontal = ro_single_new(r_texture_new_file(2, 1, "res/button_horizontal.png"));

    self->L.selection_mirror_vertical = ro_single_new(r_texture_new_file(2, 1, "res/button_vertical.png"));

    self->L.selection_blend = ro_single_new(r_texture_new_file(2, 1, "res/button_blend.png"));

    self->L.selection_ok = ro_single_new(r_texture_new_file(2, 1, "res/button_ok.png"));

    rTexture move_tex = r_texture_new_file(2, 8, "res/button_selection_move.png");
    for (int i = 0; i < 8; i++) {
        self->L.selection_move[i] = ro_single_new(move_tex);
        self->L.selection_move[i].owns_tex = i == 0;
        self->L.selection_move[i].rect.sprite.y = i;
    }

    // layer:
    self->L.layer_prev = ro_single_new(r_texture_new_file(2, 1, "res/button_prev.png"));

    self->L.layer_next = ro_single_new(r_texture_new_file(2, 1, "res/button_next.png"));

    self->L.layer_num = ro_text_new_font55(3);

    return self;
}

void toolbar_update(Toolbar *self, float dtime) {
    for (int i = 0; i < self->L.tools_size; i++) {
        Tool *t = &self->L.tools[i];
        t->btn.rect.pose = pose16(self->camera_ref, t->x, t->y);
    }

    // shape kernel:
    self->L.shape.rect.pose = pose16(self->camera_ref, -22, 10);  // should be 16x16
    self->L.shape.rect.sprite.y = self->brush_ref->shape;

    // secondary color:    
    self->L.color_bg.rect.pose = self->L.color_drop.rect.pose = pose16(self->camera_ref, 64, 9);
    self->L.color_drop.rect.color = u_color_to_vec4(self->brush_ref->secondary_color);

    // selection buttons:
    if (self->show_selection_ok)
        self->L.selection_copy.rect.pose = pose16(self->camera_ref, 30, 43);
    else
        self->L.selection_copy.rect.pose = pose16(self->camera_ref, 54, 43);
    self->L.selection_cut.rect.pose = pose16(self->camera_ref, 70, 43);
    self->L.selection_rotate_left.rect.pose = pose16(self->camera_ref, -58, 43);
    self->L.selection_rotate_right.rect.pose = pose16(self->camera_ref, -42, 43);
    self->L.selection_mirror_horizontal.rect.pose = pose16(self->camera_ref, -26, 43);
    self->L.selection_mirror_vertical.rect.pose = pose16(self->camera_ref, -10, 43);
    self->L.selection_blend.rect.pose = pose16(self->camera_ref, 10, 43);
    self->L.selection_ok.rect.pose = pose16(self->camera_ref, 46, 43);
    for (int i = 0; i < 8; i++) {
        self->L.selection_move[i].rect.pose = pose16(self->camera_ref, -80 + i * 16, 43);
    }

    // layer:
    self->L.layer_prev.rect.pose = pose16(self->camera_ref, 50, 43);
    self->L.layer_next.rect.pose = pose16(self->camera_ref, 80, 43);
    {
        char buf[8];
        sprintf(buf, "%d", self->canvas_ref->current_layer);
        vec2 size = ro_text_set_text(&self->L.layer_num, buf);
        float x, y;
        if (camera_is_portrait_mode(self->camera_ref)) {
            x = 65 - size.x / 2;
            y = self->camera_ref->RO.top - 43 + size.y / 2;
        } else {
            x = self->camera_ref->RO.left + 43 - size.x / 2;
            y = 65 + size.y / 2;
        }
        u_pose_set_xy(&self->L.layer_num.pose, floorf(x), floorf(y));
    }

    // shape longpress:
    if (button_is_pressed(&self->L.shape_minus->rect)) {
        self->L.shape_minus_time += dtime;
        if (self->L.shape_minus_time > LONG_PRESS_TIME) {
            self->brush_ref->shape = 0;
        }
    } else
        self->L.shape_minus_time = 0;

    if (button_is_pressed(&self->L.shape_plus->rect)) {
        self->L.shape_plus_time += dtime;
        if (self->L.shape_plus_time > LONG_PRESS_TIME) {
            self->brush_ref->shape = BRUSH_NUM_SHAPES - 1;
        }
    } else
        self->L.shape_plus_time = 0;


    // unpress cpy button if selection ok is toggled
    if (!self->L.prev_show_selection_ok && self->show_selection_ok)
        button_set_pressed(&self->L.selection_copy.rect, false);
    self->L.prev_show_selection_ok = self->show_selection_ok;
}

void toolbar_render(Toolbar *self, const mat4 *camera_mat) {
    for (int i = 0; i < self->L.tools_size; i++) {
        ro_single_render(&self->L.tools[i].btn, camera_mat);
    }

    // shape kernel;
    ro_single_render(&self->L.shape, camera_mat);

    // secondary color:
    ro_single_render(&self->L.color_bg, camera_mat);
    ro_single_render(&self->L.color_drop, camera_mat);

    // selection buttons:
    if (self->show_selection_copy_cut) {
        ro_single_render(&self->L.selection_copy, camera_mat);
        ro_single_render(&self->L.selection_cut, camera_mat);
        for (int i = 0; i < 8; i++) {
            ro_single_render(&self->L.selection_move[i], camera_mat);
        }
    }
    if (self->show_selection_ok) {
        ro_single_render(&self->L.selection_rotate_left, camera_mat);
        ro_single_render(&self->L.selection_rotate_right, camera_mat);
        ro_single_render(&self->L.selection_mirror_horizontal, camera_mat);
        ro_single_render(&self->L.selection_mirror_vertical, camera_mat);
        ro_single_render(&self->L.selection_blend, camera_mat);
        ro_single_render(&self->L.selection_copy, camera_mat);
        ro_single_render(&self->L.selection_ok, camera_mat);
    }

    if (self->canvas_ref->RO.image.layers > 1) {
        ro_single_render(&self->L.layer_prev, camera_mat);
        ro_single_render(&self->L.layer_next, camera_mat);
        ro_text_render(&self->L.layer_num, camera_mat);
    }
}

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(Toolbar *self, ePointer_s pointer) {
    if (!pos_in_toolbar(self, pointer.pos.xy))
        return false;


    if (button_clicked(&self->L.undo->rect, pointer)) {
        log_info("toolbar: undo");
        canvas_undo(self->canvas_ref);
    }

    if (button_clicked(&self->L.clear->rect, pointer)) {
        log_info("toolbar: clear");
        brush_clear(self->brush_ref);
    }

    if (button_clicked(&self->L.import->rect, pointer)) {
        log_info("toolbar: import");
        selectionctrl_set_active(self->selectionctrl_ref, false, true);
        if (self->show_selection_ok) {
            canvas_reload(self->canvas_ref);
        }
        self->show_selection_copy_cut = false;

        uImage img = u_image_new_file(1, self->canvas_ref->default_import_file);
        button_set_pressed(&self->L.selection->rect, u_image_valid(img));
        self->show_selection_ok = u_image_valid(img);


        if (u_image_valid(img)) {
            selection_kill(&self->selectionctrl_ref->selection);
            self->selectionctrl_ref->selection = selection_new(0, 0, img.cols, img.rows);
            selection_copy(self->selectionctrl_ref->selection, img, 0);
            selection_paste(self->selectionctrl_ref->selection, self->canvas_ref->RO.image, self->canvas_ref->current_layer);
            u_image_kill(&img);
            self->selectionctrl_ref->mode = SELECTIONCTRL_PASTE;
            selectionctrl_set_active(self->selectionctrl_ref, true, false);
        }
        log_trace("toolbar: import finished");
    }

    if (button_toggled(&self->L.selection->rect, pointer)) {
        log_info("toolbar: selection");
        bool pressed = button_is_pressed(&self->L.selection->rect);
        selectionctrl_set_active(self->selectionctrl_ref, pressed, true);
        button_set_pressed(&self->L.selection_copy.rect, false);
        button_set_pressed(&self->L.selection_cut.rect, false);

        if (!pressed && self->show_selection_ok) {
            canvas_reload(self->canvas_ref);
        }
        self->show_selection_copy_cut = false;
        self->show_selection_ok = false;
    }

    if (button_toggled(&self->L.grid->rect, pointer)) {
        log_info("toolbar: grid");
        bool pressed = button_is_pressed(&self->L.grid->rect);
        self->canvas_ref->show_grid = pressed;

        if (pressed) {
            self->canvas_ref->alpha = self->L.grid_status ? 1 : 0.5;
            self->L.grid_status = !self->L.grid_status;
        }
    }

    if (button_clicked(&self->L.camera->rect, pointer)) {
        log_info("toolbar: camera");
        cameractrl_set_home(self->canvascamctrl_ref, self->canvas_ref->RO.image.cols, self->canvas_ref->RO.image.rows);
    }

    if (button_toggled(&self->L.animation->rect, pointer)) {
        log_info("toolbar: animation");
        self->animation_ref->show = button_is_pressed(&self->L.animation->rect);
    }

    if (button_toggled(&self->L.shade->rect, pointer)) {
        log_info("toolbar: shade");
        self->brush_ref->shading_active = button_is_pressed(&self->L.shade->rect);
    }


    for (int i = 0; i < TOOLBAR_MODES; i++) {
        if (button_pressed(&self->L.modes[i]->rect, pointer)) {
            log_info("toolbar: mode %i", i);
            unpress(self->L.modes, TOOLBAR_MODES, i);

            if (i == 0)
                self->brush_ref->mode = BRUSH_MODE_FREE;
            else if (i == 1)
                self->brush_ref->mode = BRUSH_MODE_DOT;
            else if (i == 2)
                self->brush_ref->mode = BRUSH_MODE_DITHER;
            else if (i == 3)
                self->brush_ref->mode = BRUSH_MODE_DITHER2;
            else if (i == 4)
                self->brush_ref->mode = BRUSH_MODE_FILL;
            else if (i == 5)
                self->brush_ref->mode = BRUSH_MODE_FILL8;
            else if (i == 6)
                self->brush_ref->mode = BRUSH_MODE_REPLACE;
        }
    }

    if (button_clicked(&self->L.shape_minus->rect, pointer)) {
        log_info("toolbar: shape_minus");
        self->brush_ref->shape--;
        if (self->brush_ref->shape < 0)
            self->brush_ref->shape = 0;
    }

    if (button_clicked(&self->L.shape_plus->rect, pointer)) {
        log_info("toolbar: shape_plus");
        self->brush_ref->shape++;
        if (self->brush_ref->shape >= BRUSH_NUM_SHAPES)
            self->brush_ref->shape = BRUSH_NUM_SHAPES - 1;
    }



    // secondary color:
    if (pointer.action == E_POINTER_DOWN && u_pose_aa_contains(self->L.color_drop.rect.pose, pointer.pos.xy)) {
        log_info("toolbar: secondary_color");
        self->brush_ref->secondary_color = self->brush_ref->current_color;
    }


    // selection buttons:
    if (self->show_selection_copy_cut) {
        if (button_toggled(&self->L.selection_copy.rect, pointer)) {
            log_info("toolbar: selection_copy");
            bool pressed = button_is_pressed(&self->L.selection_copy.rect);

            if (pressed) {
                button_set_pressed(&self->L.selection_cut.rect, false);
                self->selectionctrl_ref->mode = SELECTIONCTRL_COPY;
            }
        }

        if (button_toggled(&self->L.selection_cut.rect, pointer)) {
            log_info("toolbar: selection_cut");
            bool pressed = button_is_pressed(&self->L.selection_cut.rect);

            if (pressed) {
                button_set_pressed(&self->L.selection_copy.rect, false);
                self->selectionctrl_ref->mode = SELECTIONCTRL_CUT;
            }
        }

        for (int i = 0; i < 8; i++) {
            if (button_clicked(&self->L.selection_move[i].rect, pointer)) {
                Selection *s = self->selectionctrl_ref->selection;
                if (!s) {
                    log_error("toolbar: selection_move failed, selection invalid (NULL)");
                    break;
                }
                int img_cols = self->canvas_ref->RO.image.cols;
                int img_rows = self->canvas_ref->RO.image.rows;
                if (i == 0 && s->left > 0) {
                    s->left--;
                    s->cols++;
                } else if (i == 1 && s->cols > 1) {
                    s->left++;
                    s->cols--;
                } else if (i == 2) {
                    s->cols--;
                } else if (i == 3) {
                    s->cols++;
                } else if (i == 4 && s->top > 0) {
                    s->top--;
                    s->rows++;
                } else if (i == 5 && s->rows > 1) {
                    s->top++;
                    s->rows--;
                } else if (i == 6) {
                    s->rows--;
                } else if (i == 7) {
                    s->rows++;
                }
                s->left = isca_clamp(s->left, 0, img_cols - 1);
                s->top = isca_clamp(s->top, 0, img_rows - 1);
                s->cols = isca_clamp(s->cols, 1, img_cols - s->left);
                s->rows = isca_clamp(s->rows, 1, img_rows - s->top);
            }
        }
    }

    if (self->show_selection_ok) {
        bool changed = false;
        if (button_clicked(&self->L.selection_rotate_left.rect, pointer)) {
            log_info("toolbar: selection_rotate_left");
            selection_rotate(self->selectionctrl_ref->selection, false);
            changed = true;
        }
        if (button_clicked(&self->L.selection_rotate_right.rect, pointer)) {
            log_info("toolbar: selection_rotate_right");
            selection_rotate(self->selectionctrl_ref->selection, true);
            changed = true;
        }

        if (button_clicked(&self->L.selection_mirror_horizontal.rect, pointer)) {
            log_info("toolbar: selection_mirror_horizontal");
            selection_mirror(self->selectionctrl_ref->selection, false);
            changed = true;
        }
        if (button_clicked(&self->L.selection_mirror_vertical.rect, pointer)) {
            log_info("toolbar: selection_mirror_vertical");
            selection_mirror(self->selectionctrl_ref->selection, true);
            changed = true;
        }

        if(button_toggled(&self->L.selection_blend.rect, pointer)) {
            if(!self->selectionctrl_ref->selection) {
                log_error("toolbar: selection_blend failed, selection not valid (NULL)");
            } else {
                self->selectionctrl_ref->selection->blend = button_is_pressed(&self->L.selection_blend.rect);
                changed = true;
            }
        }

        if (changed) {
            canvas_reload(self->canvas_ref);
            selection_paste(self->selectionctrl_ref->selection, self->canvas_ref->RO.image, self->canvas_ref->current_layer);
        }

        if (button_clicked(&self->L.selection_copy.rect, pointer)) {
            log_info("toolbar: selection_copy");
            canvas_save(self->canvas_ref);
        }

        if (button_clicked(&self->L.selection_ok.rect, pointer)) {
            log_info("toolbar: selection_ok");
            canvas_save(self->canvas_ref);
            selectionctrl_set_active(self->selectionctrl_ref, false, true);
            self->show_selection_ok = false;
            button_set_pressed(&self->L.selection->rect, false);
        }
    }


    if (self->canvas_ref->RO.image.layers > 1) {
        if (button_clicked(&self->L.layer_prev.rect, pointer)) {
            log_info("toolbar: layer_prev");
            self->canvas_ref->current_layer = sca_max(0, self->canvas_ref->current_layer - 1);
        }
        if (button_clicked(&self->L.layer_next.rect, pointer)) {
            log_info("toolbar: layer_next");
            self->canvas_ref->current_layer = sca_min(self->canvas_ref->RO.image.layers - 1,
                                                      self->canvas_ref->current_layer + 1);
        }
    }

    return true;
}
