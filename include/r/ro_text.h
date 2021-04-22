#ifndef R_RO_TEXT_H
#define R_RO_TEXT_H

//
// renders text with an internal batch.
// based on a font sprite sheet and is monospaced.
//

#include "ro_batch.h"

// return true for a newline
typedef bool (*ro_text_sprite_fn)(vec2 *sprite, char c);

typedef struct {
    RoBatch ro;             // internal batch to render
    ro_text_sprite_fn sprite_fn;    // conversion function of character to sprite mapping
    mat4 pose;              // pose (top left) for the text
    vec2 size;              // character size
    vec2 offset;            // offset to next character
    const float *vp;        // mat4 camera view perspective
    mat4 mvp;               // internal mvp as vp for the batch
} RoText;

RoText ro_text_new_a(int max, ro_text_sprite_fn sprite_fn, const float *vp, rTexture tex_sink, Allocator_s alloc);

static RoText ro_text_new(int max, ro_text_sprite_fn sprite_fn, const float *vp, rTexture tex_sink) {
    return ro_text_new_a(max, sprite_fn, vp, tex_sink, allocator_new_default());
}

// inits text with the r/font55.png sprite sheet
RoText ro_text_new_font55(int max, const float *vp);

void ro_text_kill(RoText *self);

void ro_text_render(RoText *self);

// returns the used size
vec2 ro_text_set_text(RoText *self, const char *text);

// returns the size, without setting the text
vec2 ro_text_get_size(RoText *self, const char *text);

void ro_text_set_color(RoText *self, vec4 color);


#endif //R_RO_TEXT_H
