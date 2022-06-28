#include "m/float.h"
#include "m/utils/camera.h"
#include "e/window.h"
#include "r/texture.h"
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "u/pose.h"
#include "u/button.h"
#include "textinput.h"

#define KEY_COLS 10
#define KEY_ROWS 4
#define MAX_WIDTH 250

//
// private
//

// shift alternates between lower, upper, alt
// S = shift
// BB = backspace
// CC = cancel
// SSSSSS = space
// OO = ok

static const char layout[4][10] = {
        "qwertzuiop",
        "asdfghjkl_",
        "SyxcvbnmBB",
        "CCSSSSSSOO"
};
static const char layout_alt[4][10] = {
        "1234567890",
        "+-*/=<>()%",
        "S!?#.,;:BB",
        "CCSSSSSSOO"
};

void set_key_pos(TextInput *self, mat4 *pose, int col, int row, int cols, float x_offset, float y_offset) {
    float width = self->L.cam.width - 16;
    width = sca_min(width, MAX_WIDTH);

    float x = 8 - width / 2 + width * col / KEY_COLS + (cols - 1) * 8;
    float y = self->L.cam.bottom + 12 + 18 * (KEY_ROWS - row - 1) + y_offset + (row != 3) * 4;
    u_pose_set_xy(pose, ((int) x) + x_offset, (int) y);
}

static char get_key_char(const TextInput *self, int idx) {
    int row = idx / 10;
    int col = idx % 10;
    if (row == 2)
        col += 1; // S(hift)
    switch (self->shiftstate) {
        case TEXTINPUT_SHIFT_LOWER:
            return layout[row][col];
        case TEXTINPUT_SHIFT_UPPER:
            return toupper(layout[row][col]);
        case TEXTINPUT_SHIFT_ALT:
            return layout_alt[row][col];
        default:
            s_assume(false, "wtf");
            return 0;
    }
}

static void append_char(TextInput *self, char append) {
    int len = strlen(self->text);
    if (len >= self->L.max_chars)
        return;
    self->text[len++] = append;
    self->text[len] = '\0';
    self->L.blink_time = 0;
}

static void handle_backspace(TextInput *self) {
    int len = strlen(self->text);
    if (len > 0)
        self->text[len - 1] = '\0';
    self->L.blink_time = 0;
}

static void handle_cancel(TextInput *self) {
    s_log("textinput canceled: %s", self->text);
    self->state = TEXTINPUT_CANCELED;
}

static void handle_ok(TextInput *self) {
    if (!self->ok_active)
        return;
    s_log("textinput finished: %s", self->text);
    self->state = TEXTINPUT_DONE;
}

static void pointer_event(ePointer_s pointer, void *user_data) {
    TextInput *self = user_data;
    pointer.pos = mat4_mul_vec(self->L.cam.p_inv, pointer.pos);

    if (u_button_clicked(&self->L.shift.rect, pointer)) {
        self->shiftstate++;
        if (self->shiftstate >= TEXTINPUT_SHIFT_NUM_STATES) {
            self->shiftstate = 0;
        }
    }

    if (u_button_clicked(&self->L.space.rect, pointer)) {
        append_char(self, ' ');
    }

    for (int i = 0; i < 27; i++) {
        if (u_button_clicked(&self->L.keys.rects[i], pointer)) {
            append_char(self, get_key_char(self, i));
        }
    }

    // ok, cancel, backspace
    for (int i = 0; i < 3; i++) {
        if (u_button_clicked(&self->L.special.rects[i], pointer)) {
            if (i == 0)
                handle_ok(self);
            else if (i == 1)
                handle_cancel(self);
            else if (i == 2)
                handle_backspace(self);
        }
    }
}

static void key_raw_event(const SDL_Event *event, void *user_data) {
    TextInput *self = user_data;
    bool down = event->type == SDL_KEYDOWN;
    if (!down)
        return;

    SDL_Keycode code = event->key.keysym.sym;
    if (event->key.keysym.mod & KMOD_SHIFT) {
        if (code >= 'a' && code <= 'z')
            code = code - 'a' + 'A';
        // special keys can be set with the virtual keyboard btns
    }

    if (code >= ' ' && code <= '~')
        append_char(self, (char) code);
    else if (code == SDLK_BACKSPACE)
        handle_backspace(self);
    else if (code == SDLK_ESCAPE)
        handle_cancel(self);
    else if (code == SDLK_RETURN || code == SDLK_KP_ENTER)
        handle_ok(self);

}

static void camera(TextInput *self, ivec2 window_size) {
    int wnd_width = window_size.x;
    int wnd_height = window_size.y;
    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    float real_pixel_per_pixel = floorf(smaller_size / 180.0f);

    float width_2 = wnd_width / (2 * real_pixel_per_pixel);
    float height_2 = wnd_height / (2 * real_pixel_per_pixel);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    self->L.cam.left = -floorf(width_2);
    self->L.cam.top = floorf(height_2);
    self->L.cam.right = width_2 + (width_2 - floorf(width_2));
    self->L.cam.bottom = -height_2 - (height_2 - floorf(height_2));
    self->L.cam.width = self->L.cam.right - self->L.cam.left;
    self->L.cam.height = self->L.cam.top - self->L.cam.bottom;

    self->L.cam.p = mat4_camera_ortho(
            self->L.cam.left, self->L.cam.right,
            self->L.cam.bottom, self->L.cam.top,
            -1, 1);
    self->L.cam.p_inv = mat4_inv(self->L.cam.p);
}

//
// public
//

TextInput *textinput_new(const char *title, int opt_max_chars) {
    TextInput *self = s_new0(TextInput, 1);

    e_input_set_vip_pointer_event(pointer_event, self);
    e_input_set_vip_key_raw_event(key_raw_event, self);

    self->state = TEXTINPUT_IN_PROGRESS;
    self->ok_active = true;

    if (opt_max_chars <= 0) {
        opt_max_chars = TEXTINPUT_MAX_CHARS;
    } else if (opt_max_chars > TEXTINPUT_MAX_CHARS) {
        s_log_warn("textinput_new: opt_max_chars > TEXTINPUT_MAX_CHARS, reset from (%i) to (%i)",
                   opt_max_chars, TEXTINPUT_MAX_CHARS);
        opt_max_chars = TEXTINPUT_MAX_CHARS;
    }
    self->L.max_chars = opt_max_chars;


    self->L.title = ro_text_new_font85(TEXTINPUT_TITLE_MAX_LENGTH);
    vec2 title_size = ro_text_set_text(&self->L.title, title);
    if(title_size.x>85)
        self->L.title.pose = u_pose_new(-80, 32,
                                        1, 1);
    else
        self->L.title.pose = u_pose_new(-80, 32,
                                        2, 2);

    self->L.title_shadow = ro_text_new_font85(TEXTINPUT_TITLE_MAX_LENGTH);
    ro_text_set_text(&self->L.title_shadow, title);
    ro_text_set_color(&self->L.title_shadow, (vec4) {{0, 0, 0, 0.5}});
    self->L.title_shadow.pose = self->L.title.pose;
    u_pose_shift_xy(&self->L.title_shadow.pose, 1, -1);

    self->L.textfield = ro_text_new_font85(self->L.max_chars);
    ro_text_set_color(&self->L.textfield, R_COLOR_BLACK);

    self->L.keys = ro_batch_new(27, r_texture_new_file(2, 1, "res/textinput_key.png"));

    self->L.chars = ro_batch_new(27, self->L.textfield.ro.tex);
    self->L.chars.owns_tex = false;

    self->L.shift = ro_single_new(r_texture_new_file(2, 3, "res/textinput_key_shift.png"));
    self->L.space = ro_single_new(r_texture_new_file(2, 1, "res/textinput_key_space.png"));
    self->L.special = ro_batch_new(3, r_texture_new_file(2, 3, "res/textinput_key_special.png"));

    self->L.bg = ro_single_new(r_texture_new_white_pixel());
    self->bg_color = (vec4) {{0, 0, 0, 0.66}};

    self->L.text_bg = ro_single_new(r_texture_new_white_pixel());
    self->L.text_bg.rect.color = (vec4) {{1, 1, 1, 0.5}};

    for (int i = 0; i < 27; i++) {
        self->L.keys.rects[i].pose = u_pose_new(0, 0,
                                                16, 16);
        self->L.chars.rects[i].pose = u_pose_new(0, 0,
                                                 5, 8);
        self->L.chars.rects[i].color = R_COLOR_BLACK;
    }

    self->L.shift.rect.pose = u_pose_new(0, 0,
                                         16, 16);
    self->L.space.rect.pose = u_pose_new(0, 0,
                                         16 * 6,
                                         16);
    for (int i = 0; i < 3; i++) {
        self->L.special.rects[i].pose = u_pose_new(0, 0,
                                                   16 * 2,
                                                   16);
        self->L.special.rects[i].sprite.y = i;
    }

    return self;
}

void textinput_kill(TextInput **self_ptr) {
    TextInput *self = *self_ptr;
    if (!self)
        return;

    e_input_set_vip_pointer_event(NULL, NULL); // reset
    e_input_set_vip_key_raw_event(NULL, NULL); // reset

    ro_text_kill(&self->L.title);
    ro_text_kill(&self->L.title_shadow);
    ro_text_kill(&self->L.textfield);
    ro_batch_kill(&self->L.keys);
    ro_batch_kill(&self->L.chars);
    ro_single_kill(&self->L.shift);
    ro_single_kill(&self->L.space);
    ro_batch_kill(&self->L.special);
    ro_single_kill(&self->L.text_bg);
    ro_single_kill(&self->L.bg);

    s_free(self);
    *self_ptr = NULL;
}

void textinput_update(TextInput *self, float dtime) {
    camera(self, e_window.size);

    char text[TEXTINPUT_MAX_CHARS];
    strcpy(text, self->text);

    self->L.blink_time += dtime;
    if (self->L.blink_time > 1.0)
        self->L.blink_time -= 1.0;
    if (self->L.blink_time < 0.5) {
        int len = strlen(text);
        if (len < self->L.max_chars - 1) {
            strcpy(text + len, "|");
        }
    }

    ro_text_set_text(&self->L.textfield, text);

    u_pose_set_xy(&self->L.textfield.pose, -80, 4);

    self->L.text_bg.rect.pose = u_pose_new_aa(
            self->L.cam.left, 6,
            self->L.cam.width, 12);
    self->L.bg.rect.color = self->bg_color;

    int idx = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 10; c++) {
            char key = self->shiftstate == TEXTINPUT_SHIFT_ALT ? layout_alt[r][c] : layout[r][c];
            if (isupper(key))
                continue;
            if (self->shiftstate == TEXTINPUT_SHIFT_UPPER)
                key = toupper(key);

            bool pressed = u_button_is_pressed(&self->L.keys.rects[idx]);

            set_key_pos(self, &self->L.keys.rects[idx].pose, c, r, 1, 0, 0);
            set_key_pos(self, &self->L.chars.rects[idx].pose, c, pressed ? 0 : r, 1, 0.5, pressed ? 16 : 1);
            self->L.chars.rects[idx].color = pressed ? R_COLOR_WHITE : R_COLOR_BLACK;

            self->L.textfield.sprite_fn(&self->L.chars.rects[idx].sprite, key);

            idx++;
        }
    }

    self->L.shift.rect.sprite.y = self->shiftstate;
    set_key_pos(self, &self->L.shift.rect.pose, 0, 2, 1, 0, 0);
    set_key_pos(self, &self->L.space.rect.pose, 2, 3, 6, 0, 0);

    // ok, cancel, backspace
    if (self->ok_active) {
        set_key_pos(self, &self->L.special.rects[0].pose, 8, 3, 2, 0, 0);
    } else {
        u_pose_set_xy(&self->L.special.rects[0].pose, FLT_MAX, FLT_MAX);
    }
    set_key_pos(self, &self->L.special.rects[1].pose, 0, 3, 2, 0, 0);
    set_key_pos(self, &self->L.special.rects[2].pose, 8, 2, 2, 0, 0);

    self->L.bg.rect.pose = u_pose_new_aa(
            self->L.cam.left, self->L.cam.top,
            self->L.cam.width, self->L.cam.height);

}

void textinput_render(const TextInput *self) {
    const mat4 *cam_mat = &self->L.cam.p;

    ro_single_render(&self->L.bg, cam_mat);
    ro_single_render(&self->L.text_bg, cam_mat);

    ro_text_render(&self->L.title_shadow, cam_mat);
    ro_text_render(&self->L.title, cam_mat);
    ro_text_render(&self->L.textfield, cam_mat);
    ro_batch_render(&self->L.keys, cam_mat, true);
    ro_batch_render(&self->L.chars, cam_mat, true);
    ro_single_render(&self->L.shift, cam_mat);
    ro_single_render(&self->L.space, cam_mat);
    ro_batch_render(&self->L.special, cam_mat, true);
}
