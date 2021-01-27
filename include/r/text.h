#ifndef R_TEXT_H
#define R_TEXT_H

#include "SDL_ttf.h"
#include "mathc/types/float.h"
#include "ro_single.h"


extern TTF_Font *r_text_default_font;

GLuint r_text_create_texture(TTF_Font *font, vec4 color, const char *text, int *opt_out_w, int *opt_out_h);

typedef struct {
	rRoSingle r;
	TTF_Font *font;
	float ratio;    // width / height
} rRoText;

void r_ro_text_init(rRoText *self, const float *vp, vec4 color, const char *text);

void r_ro_text_kill(rRoText *self);

void r_ro_text_render(rRoText *self);

void r_ro_text_set_size(rRoText *self, float h);

void r_ro_text_set_text(rRoText *self, vec4 color, const char *text);

#endif //R_TEXT_H
