#ifndef R_RO_TTFTEXT_H
#define R_RO_TTFTEXT_H

#include "SDL_ttf.h"
#include "mathc/types/float.h"
#include "ro_single.h"

struct rRoTtfTextGlobals_s {
    TTF_Font *default_font;
};
extern struct rRoTtfTextGlobals_s r_ro_ttftext;

GLuint r_ro_ttftext_create_texture(TTF_Font *font, vec4 color, const char *text, int *opt_out_w, int *opt_out_h);

typedef struct {
	rRoSingle ro;
	TTF_Font *font;
	float ratio;    // width / height
} rRoTtfText;

void r_ro_ttftext_init(rRoTtfText *self, const float *vp, vec4 color, const char *text);

void r_ro_ttftext_kill(rRoTtfText *self);

void r_ro_ttftext_render(rRoTtfText *self);

void r_ro_ttftext_set_size(rRoTtfText *self, float h);

void r_ro_ttftext_set_text(rRoTtfText *self, vec4 color, const char *text);

#endif //R_RO_TTFTEXT_H
