#ifndef R_TEXT_H
#define R_TEXT_H

#include "SDL_ttf.h"
#include "mathc/types/float.h"
#include "single.h"


extern TTF_Font *r_text_default_font;

GLuint r_text_create_texture(TTF_Font *font, vec4 color, const char *text);

typedef struct rText {
	rSingle r;
	TTF_Font *font;
	float ratio;    // width / height
} rText;

void r_text_init(rText *self, const float *vp, vec4 color, const char *text);

void r_text_kill(rText *self);

void r_text_render(rText *self);

void r_text_set_size(rText *self, float h);

void r_text_set_text(rText *self, vec4 color, const char *text);

#endif //R_TEXT_H
