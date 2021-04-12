#ifndef R_RO_TEXT_H
#define R_RO_TEXT_H

#include "ro_batch.h"

// return true for a newline
typedef bool (*ro_text_uv_fn)(mat4 *uv, char c);

// Uses RoBatch to render a text, based on a font sprite sheet
typedef struct {
    RoBatch ro;
    ro_text_uv_fn uv_fn;
    mat4 pose;
    vec2 size;
    vec2 offset;
    const float *vp;
    mat4 mvp;
} RoText;

void ro_text_init(RoText *self, int max, ro_text_uv_fn uv_fn, const float *vp, GLuint tex_sink);

void ro_text_init_font55(RoText *self, int max, const float *vp);

void ro_text_kill(RoText *self);

void ro_text_render(RoText *self);

// returns the used size
vec2 ro_text_set_text(RoText *self, const char *text);

// returns the size, without setting the text
vec2 ro_text_get_size(RoText *self, const char *text);


#endif //R_RO_TEXT_H
