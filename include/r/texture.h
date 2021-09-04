#ifndef R_TEXTURE_H
#define R_TEXTURE_H

//
// load and setup textures as texture arrays
//

#include <stdint.h>
#include <stdbool.h>
#include "types.h"


static bool r_texture_valid(rTexture self) {
    return self.tex > 0
            && self.sprite_size.x > 0 && self.sprite_size.y > 0
            && self.sprites.x > 0 && self.sprites.y > 0;
}

static rTexture r_texture_new_invalid() {
    return (rTexture) {0};
}

rTexture r_texture_new(int image_cols, int image_rows, int sprites_cols, int sprites_rows, const void *opt_buffer);

rTexture r_texture_new_sdl_surface(int sprites_cols, int sprites_rows, const SDL_Surface *img);

rTexture r_texture_new_file(int sprites_cols, int sprite_rows, const char *file);

rTexture r_texture_new_empty(int image_cols, int image_rows, int sprites_cols, int sprites_rows);

rTexture r_texture_new_white_pixel();

void r_texture_kill(rTexture *self);

// updates the texture with the given buffer
// buffer has to be the size of:
//     4 * sprite_size.x * _y * sprites.x * _y
void r_texture_set(rTexture self, const void *buffer);

// r_texture_get not available
// gles3 does not support 3D (2D_ARRAY) there

void r_texture_filter_linear(rTexture self);

void r_texture_filter_nearest(rTexture self);

#endif //R_TEXTURE_H
