#include "r/texture.h"
#include "r/text.h"

TTF_Font *r_text_default_font;

GLuint r_text_create_texture(TTF_Font *font, vec4 color, const char *text) {

    // SDL_ttf seems to render in BGRA format, so we just swap r and b
    SDL_Surface *img = TTF_RenderText_Blended(font, text,
            (SDL_Color) {color.v2*255, color.v1*255, color.v0*255, color.v3*255});
    return r_texture_from_img(img);
}


// from u/pose.h
static float u_pose_get_w(mat4 p) {
    return sqrtf(powf(p.m00, 2) + powf(p.m01, 2));
}
static float u_pose_get_h(mat4 p) {
    return sqrtf(powf(p.m10, 2) + powf(p.m11, 2));
}
static void u_pose_set_w(mat4 *p, float w) {
    float f = w / u_pose_get_w(*p);
    p->m00 *= f;
    p->m01 *= f;
}
static void u_pose_set_h(mat4 *p, float h) {
    float f = h / u_pose_get_h(*p);
    p->m10 *= f;
    p->m11 *= f;
}
static void u_pose_set_size(mat4 *p, float w, float h) {
    u_pose_set_w(p, w);
    u_pose_set_h(p, h);
}


void r_text_init(rText *self, const float *vp, vec4 color, const char *text) {
    self->font = r_text_default_font;
    r_single_init(&self->r, vp, r_text_create_texture(self->font, color, text));
    int w, h;
    r_texture_get_size(self->r.tex, &w, &h);
    self->ratio = (float) w / h;
}

void r_text_kill(rText *self) {
    r_single_kill(&self->r);
}

void r_text_render(rText *self) {
    r_single_render(&self->r);
}

void r_text_set_size(rText *self, float h) {
	u_pose_set_size(&self->r.rect.pose, h*self->ratio, h);
}

void r_text_set_text(rText *self, vec4 color, const char *text) {
    r_single_set_texture(&self->r, r_text_create_texture(self->font, color, text));
    int w, h;
    r_texture_get_size(self->r.tex, &w, &h);
    self->ratio = (float) w / h;
    r_text_set_size(self, u_pose_get_h(self->r.rect.pose));
}

