#ifndef R_RO_TEXT_H
#define R_RO_TEXT_H

//
// renders text with an internal batch.
// based on a font sprite sheet and is monospaced.
//

#include "ro_batch.h"

// return true for a newline
typedef bool (*ro_text_uv_fn)(mat4 *uv, char c);

typedef struct {
    RoBatch ro;             // internal batch to render
    ro_text_uv_fn uv_fn;    // conversion function of character to uv mapping
    mat4 pose;              // pose (top left) for the text
    vec2 size;              // character size
    vec2 offset;            // offset to next character
    const float *vp;        // mat4 camera view perspective
    mat4 mvp;               // internal mvp as vp for the batch
} RoText;

void ro_text_init(RoText *self, int max, ro_text_uv_fn uv_fn, const float *vp, GLuint tex_sink);

// inits text with the r/font55.png sprite sheet
void ro_text_init_font55(RoText *self, int max, const float *vp);

void ro_text_kill(RoText *self);

void ro_text_render(RoText *self);

// returns the used size
vec2 ro_text_set_text(RoText *self, const char *text);

// returns the size, without setting the text
vec2 ro_text_get_size(RoText *self, const char *text);


#endif //R_RO_TEXT_H
