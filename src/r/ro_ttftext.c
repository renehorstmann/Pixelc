#ifdef OPTION_TTF
#include "r/texture.h"
#include "r/ro_single.h"
#include "r/ro_ttftext.h"

struct RoTtfTextGlobals_s ro_ttftext;

rTexture ro_ttftext_create_texture(TTF_Font *font, vec4 color, const char *text, int *opt_out_w, int *opt_out_h) {

    // SDL_ttf seems to render in BGRA format, so we just swap r and b
    SDL_Surface *img = TTF_RenderText_Blended(font, text,
                                              (SDL_Color) {color.v2 * 255, color.v1 * 255, color.v0 * 255,
                                                           color.v3 * 255});
    rTexture tex = r_texture_new_sdl_surface(1, 1, img);
    r_texture_filter_linear(tex);
    if (opt_out_w)
        *opt_out_w = img->w;
    if (opt_out_h)
        *opt_out_h = img->h;
    SDL_FreeSurface(img);
    return tex;
}



//
// private
//

// from u/pose
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
// end of u/pose copy



//
// public
//

RoTtfText ro_ttftext_new(vec4 color, const char *text) {
    RoTtfText self;
    
    self.font = ro_ttftext.default_font;
    int w, h;
    self.ro = ro_single_new(ro_ttftext_create_texture(self.font, color, text, &w, &h));
    self.ratio = (float) w / h;
    
    return self;
}

void ro_ttftext_kill(RoTtfText *self) {
    ro_single_kill(&self->ro);
}

void ro_ttftext_render(const RoTtfText *self, const mat4 *camera_mat) {
    ro_single_render(&self->ro, camera_mat);
}

void ro_ttftext_set_size(RoTtfText *self, float h) {
    u_pose_set_size(&self->ro.rect.pose, h * self->ratio, h);
}

void ro_ttftext_set_text(RoTtfText *self, vec4 color, const char *text) {
    int w, h;
    ro_single_set_texture(&self->ro, ro_ttftext_create_texture(self->font, color, text, &w, &h));
    self->ratio = (float) w / h;
    ro_ttftext_set_size(self, u_pose_get_h(self->ro.rect.pose));
}
#else //OPTION_TTF
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
