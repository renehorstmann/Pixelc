#ifndef R_RO_TEXT_H
#define R_RO_TEXT_H

//
// renders text with an internal batch.
// based on a font sprite sheet and is monospaced.
//

#include "rhc/alloc.h"
#include "ro_types.h"




RoText ro_text_new_a(int max, ro_text_sprite_fn sprite_fn, rTexture tex_sink, Allocator_s alloc);

static RoText ro_text_new(int max, ro_text_sprite_fn sprite_fn, rTexture tex_sink) {
    return ro_text_new_a(max, sprite_fn, tex_sink, rhc_allocator_new());
}

// inits text with the r/font55.png sprite sheet
RoText ro_text_new_font55(int max);

void ro_text_kill(RoText *self);

void ro_text_render(RoText *self, const mat4 *camera_mat);

// returns the used size
vec2 ro_text_set_text(RoText *self, const char *text);

// returns the size, without setting the text
vec2 ro_text_get_size(RoText *self, const char *text);

void ro_text_set_color(RoText *self, vec4 color);


#endif //R_RO_TEXT_H
