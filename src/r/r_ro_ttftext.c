#include "r/texture.h"
#include "r/ro_ttftext.h"

TTF_Font *r_ttftext_default_font;

GLuint r_ttftext_create_texture(TTF_Font *font, vec4 color, const char *text, int *opt_out_w, int *opt_out_h) {

    // SDL_ttf seems to render in BGRA format, so we just swap r and b
    SDL_Surface *img = TTF_RenderText_Blended(font, text,
            (SDL_Color) {color.v2*255, color.v1*255, color.v0*255, color.v3*255});
    GLuint tex = r_texture_init_img(img);
    if(opt_out_w)
        *opt_out_w = img->w;
    if(opt_out_h)
        *opt_out_h = img->h;
    SDL_FreeSurface(img);
    return tex;
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


void r_ro_ttftext_init(rRoTtfText *self, const float *vp, vec4 color, const char *text) {
    self->font = r_ttftext_default_font;
    int w, h;
    r_ro_single_init(&self->ro, vp, r_ttftext_create_texture(self->font, color, text, &w, &h));
    self->ratio = (float) w / h;
}

void r_ro_ttftext_kill(rRoTtfText *self) {
    r_ro_single_kill(&self->ro);
}

void r_ro_ttftext_render(rRoTtfText *self) {
    r_ro_single_render(&self->ro);
}

void r_ro_ttftext_set_size(rRoTtfText *self, float h) {
	u_pose_set_size(&self->ro.rect.pose, h*self->ratio, h);
}

void r_ro_ttftext_set_text(rRoTtfText *self, vec4 color, const char *text) {
    int w, h;
    r_ro_single_set_texture(&self->ro, r_ttftext_create_texture(self->font, color, text, &w, &h));
    self->ratio = (float) w / h;
    r_ro_ttftext_set_size(self, u_pose_get_h(self->ro.rect.pose));
}


