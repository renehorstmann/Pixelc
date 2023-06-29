#ifndef R_RO_TEXT_H
#define R_RO_TEXT_H

//
// renders text with an internal batch.
// based on a font sprite sheet and is monospaced.
//

#include "ro_batch.h"
#include "m/types/uchar.h"


static const ucvec4 RO_TEXT_SHADOW_COLOR = {{0, 0, 0, 127}};


// text sprite from char callback
// return true for a newline
typedef bool (*ro_text_sprite_fn)(vec2 *sprite, char c);

// Renders monospace text, with a texture
typedef struct {
    RoBatch ro;             // internal batch to render
    ro_text_sprite_fn sprite_fn;    // conversion function of character to sprite mapping
    mat4 pose;              // pose (top left) for the text
    vec2 offset;            // offset to next character
} RoText;


// creates a new costum text
// sprite_fn should set the sprite from a char and return true for newline
RoText ro_text_new(int max, ro_text_sprite_fn sprite_fn, rTexture tex_sink);

// inits text with the r/font53.png sprite sheet
RoText ro_text_new_font53(int max);

// inits text with the r/font53_shadow.png sprite sheet
// adds a dark transparent shadow
// uColer_s := ucvec4
RoText ro_text_new_font53_shadow(int max, ucvec4 *opt_shadow_color);

// inits text with the r/font55.png sprite sheet
RoText ro_text_new_font55(int max);

// inits text with the r/font55_shadow.png sprite sheet
// adds a dark transparent shadow
// uColer_s := ucvec4
RoText ro_text_new_font55_shadow(int max, ucvec4 *opt_shadow_color);

// inits text with the r/font88.png sprite sheet
RoText ro_text_new_font85(int max);

// inits text with the r/font88_shadow.png sprite sheet
// adds a dark transparent shadow
// uColor_s := ucvec4
RoText ro_text_new_font85_shadow(int max, ucvec4 *opt_shadow_color);


void ro_text_kill(RoText *self);

// renders the text via the underlying RoBatch
void ro_text_render(const RoText *self, const mat4 *camera_mat);

// resets the printed text
// returns the used size
vec2 ro_text_set_text(RoText *self, const char *text);

// returns the size, without setting the text
vec2 ro_text_get_size(const RoText *self, const char *text);

// sets the color of each character via the internal RoBatch's rRect's
void ro_text_set_color(RoText *self, vec4 color);


#endif //R_RO_TEXT_H
