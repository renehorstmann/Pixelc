#include "s/error.h"
#include "m/float.h"
#include "m/utils/camera.h"
#include "m/utils/color.h"
#include "e/window.h"
#include "r/texture.h"
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "u/pose.h"
#include "u/button.h"
#include "colorpicker.h"

#define SLIDER_SIZE 80
#define IMAGE_SIZE 20

#define SLIDER_LEFT -60
#define SLIDER_HEIGHT 12
#define SLIDER_OFFSET 16

#define SLIDER_FIRST_TOP 48

// 
// private
//

static void handle_cancel(ColorPicker *self) {
    s_log("colorpicker canceled");
    self->color = self->L.init_color;
    self->state = COLORPICKER_CANCELED;
}

static void handle_ok(ColorPicker *self) {
    if (!self->ok_active)
        return;
    s_log("colorpicker finished");
    self->state = COLORPICKER_DONE;
}

static void pointer_event(ePointer_s pointer, void *user_data) {
    ColorPicker *self = user_data;

    // wait for first new press
    if(!self->L.enable_touch && pointer.action != E_POINTER_DOWN)
        return;
    self->L.enable_touch = true;

    pointer.pos = mat4_mul_vec(self->L.cam.p_inv, pointer.pos);


    if(u_button_clicked(&self->L.btns.rects[0], pointer)) {
        handle_ok(self);
    }
    if(u_button_clicked(&self->L.btns.rects[1], pointer)) {
        handle_cancel(self);
    }

    // reset color to init
    if(pointer.action == E_POINTER_DOWN && u_pose_aa_contains(self->L.color_prev.rect.pose, pointer.pos.xy)) {
        self->color = self->L.init_color;
    }

    mat4 pose_inv;
    vec4 pos;

    // hue
    pose_inv = mat4_inv(self->L.h.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        vec4 color = u_color_to_vec4(self->color);
        vec3 hsv = vec3_rgb2hsv(color.rgb);
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            val *= 360;
            hsv.v0 = val;
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0)
                hsv.v0 -= 5;
            else
                hsv.v0 += 5;
        }
        // reset sat if near 0, else the hue will directly be overridden with 0
        if(hsv.v0>1 && hsv.v1<=0.01)
            hsv.v1=1;
        // reset val if near 0, else the hue will directly be overridden with 0
        if(hsv.v0>1 && hsv.v2<=0.01)
            hsv.v2=1;
        hsv = vec3_clamp_vec(hsv, vec3_set(0), (vec3) {{360, 1, 1}});
        color.rgb = vec3_hsv2rgb(hsv);
        self->color = u_color_from_vec4(color);
    }

    // sat
    pose_inv = mat4_inv(self->L.s.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        vec4 color = u_color_to_vec4(self->color);
        vec3 hsv = vec3_rgb2hsv(color.rgb);
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            hsv.v1 = val;
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0)
                hsv.v1 -= 0.05;
            else
                hsv.v1 += 0.05;
        }
        // reset val if near 0, else the sat will directly be overridden with 0
        if(hsv.v1>0.01 && hsv.v2<=0.01)
            hsv.v2=1;
        hsv = vec3_clamp_vec(hsv, vec3_set(0), (vec3) {{360, 1, 1}});
        color.rgb = vec3_hsv2rgb(hsv);
        self->color = u_color_from_vec4(color);
    }

    // val
    pose_inv = mat4_inv(self->L.v.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        vec4 color = u_color_to_vec4(self->color);
        vec3 hsv = vec3_rgb2hsv(color.rgb);
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            hsv.v2 = val;
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0)
                hsv.v2 -= 0.02;
            else
                hsv.v2 += 0.02;
        }
        hsv = vec3_clamp_vec(hsv, vec3_set(0), (vec3) {{360, 1, 1}});
        color.rgb = vec3_hsv2rgb(hsv);
        self->color = u_color_from_vec4(color);
    }

    // r
    pose_inv = mat4_inv(self->L.r.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            vec4 color = u_color_to_vec4(self->color);
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            color.r = val;
            self->color = u_color_from_vec4(color);
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0 && self->color.r>0)
                self->color.r--;
            else if(pos.x>0 && self->color.r<255)
                self->color.r++;
        }
    }

    // g
    pose_inv = mat4_inv(self->L.g.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            vec4 color = u_color_to_vec4(self->color);
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            color.g = val;
            self->color = u_color_from_vec4(color);
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0 && self->color.g>0)
                self->color.g--;
            else if(pos.x>0 && self->color.g<255)
                self->color.g++;
        }
    }

    // b
    pose_inv = mat4_inv(self->L.b.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            vec4 color = u_color_to_vec4(self->color);
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            color.b = val;
            self->color = u_color_from_vec4(color);
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0 && self->color.b>0)
                self->color.b--;
            else if(pos.x>0 && self->color.b<255)
                self->color.b++;
        }
    }

    // a
    pose_inv = mat4_inv(self->L.a.rect.pose);
    pos = mat4_mul_vec(pose_inv, pointer.pos);
    if (pos.x >= -1 && pos.x <= 1 && pos.y >= -0.5 && pos.y <= 0.5) {
        if (pos.x >= -0.6 && pos.x <= 0.6) {
            vec4 color = u_color_to_vec4(self->color);
            float val = sca_clamp(pos.x + 0.5, 0, 1);
            color.a = val;
            self->color = u_color_from_vec4(color);
        } else if (pointer.action == E_POINTER_DOWN) {
            if (pos.x < 0 && self->color.a>0)
                self->color.a--;
            else if(pos.x>0 && self->color.a<255)
                self->color.a++;
        }
    }
}

static void camera(ColorPicker *self, ivec2 window_size) {
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

ColorPicker *colorpicker_new(const char *title, uColor_s init_color) {
    ColorPicker *self = s_new0(ColorPicker, 1);

    e_input_set_vip_pointer_event(pointer_event, self);

    self->state = COLORPICKER_IN_PROGRESS;
    self->ok_active = true;

    self->color = init_color;
    self->L.init_color = init_color;

    self->L.title = ro_text_new_font85(COLORPICKER_TITLE_MAX_LENGTH);
    vec2 title_size = ro_text_set_text(&self->L.title, title);
    self->L.title.pose = u_pose_new(-80, 80,
            title_size.x > 85? 1 : 2, 2);

    self->L.title_shadow = ro_text_new_font85(COLORPICKER_TITLE_MAX_LENGTH);
    ro_text_set_text(&self->L.title_shadow, title);
    ro_text_set_color(&self->L.title_shadow, (vec4) {{0, 0, 0, 0.5}});
    self->L.title_shadow.pose = self->L.title.pose;
    u_pose_shift_xy(&self->L.title_shadow.pose, 1, -1);

    float top = SLIDER_FIRST_TOP;

    self->L.h = ro_single_new(r_texture_new_invalid());
    self->L.h.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.h_num = ro_text_new_font55(12);
    self->L.h_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    top -= SLIDER_OFFSET;

    self->L.s = ro_single_new(r_texture_new_invalid());
    self->L.s.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.s_num = ro_text_new_font55(12);
    self->L.s_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    top -= SLIDER_OFFSET;

    self->L.v = ro_single_new(r_texture_new_invalid());
    self->L.v.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.v_num = ro_text_new_font55(12);
    self->L.v_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    top -= SLIDER_OFFSET;

    self->L.r = ro_single_new(r_texture_new_invalid());
    self->L.r.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.r_num = ro_text_new_font55(12);
    self->L.r_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    ro_text_set_color(&self->L.r_num, (vec4) {{1, 0.25, 0.25, 1}});
    top -= SLIDER_OFFSET;

    self->L.g = ro_single_new(r_texture_new_invalid());
    self->L.g.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.g_num = ro_text_new_font55(12);
    self->L.g_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    ro_text_set_color(&self->L.g_num, (vec4) {{0.25, 1, 0.25, 1}});
    top -= SLIDER_OFFSET;

    self->L.b = ro_single_new(r_texture_new_invalid());
    self->L.b.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.b_num = ro_text_new_font55(12);
    self->L.b_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    ro_text_set_color(&self->L.b_num, (vec4) {{0.25, 0.25, 1, 1}});
    top -= SLIDER_OFFSET;

    self->L.a = ro_single_new(r_texture_new_invalid());
    self->L.a.rect.pose = u_pose_new_aa(SLIDER_LEFT, top, SLIDER_SIZE, SLIDER_HEIGHT);
    self->L.a_num = ro_text_new_font55(12);
    self->L.a_num.pose = u_pose_new(SLIDER_LEFT + SLIDER_SIZE + 4, top, 1, 2);
    ro_text_set_color(&self->L.a_num, (vec4) {{0.5, 0.5, 0.5, 1}});
    top -= SLIDER_OFFSET;

    uColor_s pattern[4];
    pattern[0] = pattern[3] = (uColor_s) {{64, 64, 64, 255}};
    pattern[1] = pattern[2] = (uColor_s) {{32, 32, 32, 255}};
    self->L.a_bg = ro_single_new(r_texture_new(2, 2, 1, 1, pattern));
    self->L.a_bg.rect.pose = self->L.a.rect.pose;
    u_pose_set_size(&self->L.a_bg.rect.uv, (float)SLIDER_SIZE/4, (float)SLIDER_HEIGHT/4);
    r_texture_wrap_repeat(self->L.a_bg.tex);



    self->L.color_prev = ro_single_new(r_texture_new_white_pixel());
    self->L.color_prev.rect.color = u_color_to_vec4(init_color);
    self->L.color_prev.rect.pose = u_pose_new(-16, -80, 32, 12);

    self->L.color_new = ro_single_new(r_texture_new_white_pixel());
    self->L.color_new.rect.pose = u_pose_new(16, -80, 32, 12);

    self->L.color_bg = ro_single_new(r_texture_new(2, 2, 1, 1, pattern));
    self->L.color_bg.rect.pose = u_pose_new(0, -80, 64, 12);
    u_pose_set_size(&self->L.color_bg.rect.uv, (float)64/4, (float)12/4);
    r_texture_wrap_repeat(self->L.color_bg.tex);

    pattern[0] = pattern[3] = (uColor_s) {{128, 128, 128, 200}};
    pattern[1] = pattern[2] = (uColor_s) {{255, 255, 255, 200}};
    self->L.slider = ro_batch_new(7, r_texture_new(2, 2, 1, 1, pattern));
    for(int i=0; i<self->L.slider.num; i++) {
        self->L.slider.rects[i].pose = u_pose_new_aa(SLIDER_LEFT, SLIDER_FIRST_TOP-SLIDER_OFFSET*i, 2, SLIDER_HEIGHT);
    }

    self->L.btns = ro_batch_new(2, r_texture_new_file(2, 2, "res/colorpicker_btns.png"));
    self->L.btns.rects[0].pose = u_pose_new(56, -80, 32, 16);
    self->L.btns.rects[1].pose = u_pose_new(-56, -80, 32, 16);
    self->L.btns.rects[1].sprite.y = 1;

    self->L.bg = ro_single_new(r_texture_new_white_pixel());
    self->bg_color = (vec4) {{0, 0, 0, 0.66}};

    return self;
}

void colorpicker_kill(ColorPicker **self_ptr) {
    ColorPicker *self = *self_ptr;
    if (!self)
        return;

    e_input_set_vip_pointer_event(NULL, NULL); // reset

    ro_text_kill(&self->L.title);
    ro_text_kill(&self->L.title_shadow);
    ro_single_kill(&self->L.h);
    ro_single_kill(&self->L.s);
    ro_single_kill(&self->L.v);
    ro_single_kill(&self->L.r);
    ro_single_kill(&self->L.g);
    ro_single_kill(&self->L.b);
    ro_single_kill(&self->L.a);
    ro_single_kill(&self->L.a_bg);
    ro_batch_kill(&self->L.slider);
    ro_text_kill(&self->L.h_num);
    ro_text_kill(&self->L.s_num);
    ro_text_kill(&self->L.v_num);
    ro_text_kill(&self->L.r_num);
    ro_text_kill(&self->L.g_num);
    ro_text_kill(&self->L.b_num);
    ro_text_kill(&self->L.a_num);
    ro_single_kill(&self->L.color_prev);
    ro_single_kill(&self->L.color_new);
    ro_single_kill(&self->L.color_bg);
    ro_batch_kill(&self->L.btns);
    ro_single_kill(&self->L.bg);

    s_free(self);
    *self_ptr = NULL;
}

void colorpicker_update(ColorPicker *self, float dtime) {
    camera(self, e_window.size);

    self->L.bg.rect.pose = u_pose_new_aa(
            self->L.cam.left, self->L.cam.top,
            self->L.cam.width, self->L.cam.height);
    self->L.bg.rect.color = self->bg_color;


    vec4 color = u_color_to_vec4(self->color);
    self->L.color_new.rect.color = color;

    vec3 hsv = vec3_rgb2hsv(color.rgb);

    char txt[16];

    snprintf(txt, sizeof txt, "hue: %3i", (int) hsv.v0);
    ro_text_set_text(&self->L.h_num, txt);

    snprintf(txt, sizeof txt, "sat: %3i", (int) (100*hsv.v1));
    ro_text_set_text(&self->L.s_num, txt);

    snprintf(txt, sizeof txt, "val: %3i", (int) (100*hsv.v2));
    ro_text_set_text(&self->L.v_num, txt);

    snprintf(txt, sizeof txt, "red: %3i", (int) self->color.r);
    ro_text_set_text(&self->L.r_num, txt);

    snprintf(txt, sizeof txt, "grn: %3i", (int) self->color.g);
    ro_text_set_text(&self->L.g_num, txt);

    snprintf(txt, sizeof txt, "blu: %3i", (int) self->color.b);
    ro_text_set_text(&self->L.b_num, txt);

    snprintf(txt, sizeof txt, "alp: %3i", (int) self->color.a);
    ro_text_set_text(&self->L.a_num, txt);

    u_pose_set_x(&self->L.slider.rects[0].pose, SLIDER_LEFT+SLIDER_SIZE*hsv.v0/360);
    u_pose_set_x(&self->L.slider.rects[1].pose, SLIDER_LEFT+SLIDER_SIZE*hsv.v1);
    u_pose_set_x(&self->L.slider.rects[2].pose, SLIDER_LEFT+SLIDER_SIZE*hsv.v2);
    for(int rgba=0; rgba<4; rgba++) {
        u_pose_set_x(&self->L.slider.rects[3+rgba].pose, SLIDER_LEFT+SLIDER_SIZE*color.v[rgba]);
    }


    uImage img = u_image_new_empty(IMAGE_SIZE, 1, 1);

    // hue
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        val *= 360;
        vec4 c;
        c.rgb = vec3_hsv2rgb((vec3) {{val, 1, 1}});
        c.a = 1.0;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.h, r_texture_new(img.cols, img.rows, 1, 1, img.data));

    // sat
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        vec4 c;
        c.rgb = vec3_hsv2rgb((vec3) {{hsv.v0, val, 1}});
        c.a = 1.0;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.s, r_texture_new(img.cols, img.rows, 1, 1, img.data));

    // v
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        vec4 c;
        c.rgb = vec3_hsv2rgb((vec3) {{hsv.v0, hsv.v1, val}});
        c.a = 1.0;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.v, r_texture_new(img.cols, img.rows, 1, 1, img.data));

    // r
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        vec4 c = color;
        c.r = val;
        c.a = 1.0;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.r, r_texture_new(img.cols, img.rows, 1, 1, img.data));

    // g
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        vec4 c = color;
        c.g = val;
        c.a = 1.0;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.g, r_texture_new(img.cols, img.rows, 1, 1, img.data));

    // b
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        vec4 c = color;
        c.b = val;
        c.a = 1.0;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.b, r_texture_new(img.cols, img.rows, 1, 1, img.data));

    // a
    for (int i = 0; i < img.cols; i++) {
        float val = (float) i / (img.cols - 1);
        vec4 c = color;
        c.a = val;
        *u_image_pixel(img, i, 0, 0) = u_color_from_vec4(c);
    }
    ro_single_set_texture(&self->L.a, r_texture_new(img.cols, img.rows, 1, 1, img.data));


    u_image_kill(&img);
}

void colorpicker_render(const ColorPicker *self) {
    const mat4 *cam_mat = &self->L.cam.p;

    ro_single_render(&self->L.bg, cam_mat);

    ro_text_render(&self->L.title_shadow, cam_mat);
    ro_text_render(&self->L.title, cam_mat);

    ro_single_render(&self->L.h, cam_mat);
    ro_single_render(&self->L.s, cam_mat);
    ro_single_render(&self->L.v, cam_mat);
    ro_single_render(&self->L.r, cam_mat);
    ro_single_render(&self->L.g, cam_mat);
    ro_single_render(&self->L.b, cam_mat);
    ro_single_render(&self->L.a_bg, cam_mat);
    ro_single_render(&self->L.a, cam_mat);

    ro_batch_render(&self->L.slider, cam_mat, true);

    ro_text_render(&self->L.h_num, cam_mat);
    ro_text_render(&self->L.s_num, cam_mat);
    ro_text_render(&self->L.v_num, cam_mat);
    ro_text_render(&self->L.r_num, cam_mat);
    ro_text_render(&self->L.g_num, cam_mat);
    ro_text_render(&self->L.b_num, cam_mat);
    ro_text_render(&self->L.a_num, cam_mat);

    ro_single_render(&self->L.color_bg, cam_mat);
    ro_single_render(&self->L.color_prev, cam_mat);
    ro_single_render(&self->L.color_new, cam_mat);

    ro_batch_render(&self->L.btns, cam_mat, true);
}
