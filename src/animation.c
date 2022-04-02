#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "canvas.h"
#include "animation.h"


#define LONGPRESS_TIME 0.5


static void set_pose(Animation *self, const Camera_s *camera, float palette_hud_size, int c, int r) {
    uImage img = self->canvas_ref->RO.image;

    float w = self->L.size * img.cols / self->L.frames;
    float h = self->L.size * img.rows;

    float x, y;
    if (camera_is_portrait_mode(camera)) {
        x = camera->RO.left + w / 2 + c * w;
        y = camera->RO.bottom + palette_hud_size + h / 2 + r * h;
    } else {
        x = camera->RO.right - palette_hud_size - w / 2 - c * w;
        y = camera->RO.top - h / 2 - r * h;
    }

    mat4 pose = u_pose_new(floorf(x), floorf(y), w, h);
    for (int i = 0; i <= self->canvas_ref->current_layer; i++) {
        self->L.ro[i].rects[r * self->L.mcols + c].pose = pose;
    }
}


//
// public
//


Animation *animation_new(const Canvas *canvas, int multi_cols, int multi_rows, float size, int frames, float fps) {
    Animation *self = rhc_calloc(sizeof *self);

    self->canvas_ref = canvas;

    self->L.mcols = multi_cols;
    self->L.mrows = multi_rows;
    self->L.size = size;
    self->L.frames = frames;
    self->L.fps = fps;

    uImage img = canvas->RO.image;

    for (int i = 0; i < img.layers; i++) {
        rTexture tex = r_texture_new(img.cols, img.rows, frames, 1, u_image_layer(img, i));
        self->L.ro[i] = ro_batch_new(self->L.mcols * self->L.mrows, tex);
    }

    self->L.horsimann = ro_text_new_font55(9);
    ro_text_set_color(&self->L.horsimann, (vec4) {{0.25, 0.25, 0.25, 1}});
    ro_text_set_text(&self->L.horsimann, "horsimann");
    
    self->L.longpress.ro = ro_single_new(r_texture_new_file(1, 1, "res/longpress.png"));
    u_pose_set_size(&self->L.longpress.ro.rect.pose, 64, 64);

    return self;
}

void animation_update(Animation *self, const Camera_s *camera, float palette_hud_size, float dtime) {
    if(self->L.longpress.time>0) {
        self->L.longpress.ro.rect.color = vec4_mix(
                R_COLOR_TRANSPARENT,
                self->L.longpress.color,
                self->L.longpress.time/LONGPRESS_TIME);
        self->L.longpress.time -= dtime;
    }
    
    if (!self->show) {
        if (camera_is_portrait_mode(camera))
            u_pose_set_xy(&self->L.horsimann.pose,
                          camera->RO.left + 1,
                          ceilf(camera->RO.bottom + palette_hud_size + 6));
        else
            u_pose_set_xy(&self->L.horsimann.pose,
                          camera->RO.left + 40, ceilf(camera->RO.bottom + 6));
        return;
    }


    for (int r = 0; r < self->L.mrows; r++) {
        for (int c = 0; c < self->L.mcols; c++) {
            set_pose(self, camera, palette_hud_size, c, r);
        }
    }

    self->L.time = fmodf(self->L.time + dtime, self->L.frames / self->L.fps);
    float frame = floorf(self->L.time * self->L.fps);
    for (int i = 0; i <= self->canvas_ref->current_layer; i++) {
        for (int j = 0; j < self->L.ro[i].num; j++) {
            self->L.ro[i].rects[j].sprite.x = frame;
        }
    }

    uImage img = self->canvas_ref->RO.image;
    for (int i = 0; i <= self->canvas_ref->current_layer; i++) {
        r_texture_set(self->L.ro[i].tex, u_image_layer(img, i));
    }
}

void animation_render(const Animation *self, const mat4 *cam_mat) {
    if(self->L.longpress.time>0) {
        ro_single_render(&self->L.longpress.ro, cam_mat);
    }
    if (!self->show) {
        //ro_text_render(&self->L.horsimann, cam_mat);
        return;
    }

    for (int i = 0; i <= self->canvas_ref->current_layer; i++) {
        ro_batch_render(&self->L.ro[i], cam_mat, true);
    }
}

void animation_longpress(Animation *self, vec2 pos, vec4 color) {
    u_pose_set_xy(&self->L.longpress.ro.rect.pose, pos.x, pos.y);
    self->L.longpress.color = color;
    self->L.longpress.time = LONGPRESS_TIME;
}
