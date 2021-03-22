#ifndef R_RO_TEXT_H
#define R_RO_TEXT_H

#include "ro_batch.h"

// return true for a newline
typedef bool (*r_ro_text_uv_fn)(mat4 *uv, char c);

// Uses rRoBatch to render a text, based on a font sprite sheet
typedef struct {
    rRoBatch ro;
    r_ro_text_uv_fn uv_fn;
    mat4 pose;
    vec2 size;
    vec2 offset;
    const float *vp;
    mat4 mvp;
} rRoText;

void r_ro_text_init(rRoText *self, int max, r_ro_text_uv_fn uv_fn, const float *vp, GLuint tex_sink);

void r_ro_text_init_font55(rRoText *self, int max, const float *vp);

void r_ro_text_kill(rRoText *self);

void r_ro_text_render(rRoText *self);

// returns the used size
vec2 r_ro_text_set_text(rRoText *self, const char *text);

// returns the size, without setting the text
vec2 r_ro_text_get_size(rRoText *self, const char *text);


#endif //R_RO_TEXT_H
