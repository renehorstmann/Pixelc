#ifndef R_TEXTURE2D_H
#define R_TEXTURE2D_H

//
// load and setup textures as simple 2D textures
//

#include <stdint.h>
#include <stdbool.h>
#include "core.h"
#include "mathc/types/int.h"
#include "types.h"

static bool r_texture2d_valid(rTexture2D self) {
    return self.tex > 0
            && self.size.x > 0 && self.size.y > 0;
}

static rTexture2D r_texture2d_new_invalid() {
    return (rTexture2D) {0};
}

rTexture2D r_texture2d_new(int image_cols, int image_rows, const void *opt_buffer);

rTexture2D r_texture2d_new_sdl_surface(const SDL_Surface *img);

rTexture2D r_texture2d_new_file(const char *file);

rTexture2D r_texture2d_new_empty(int image_cols, int image_rows);

rTexture2D r_texture2d_new_white_pixel();

void r_texture2d_kill(rTexture2D *self);

// updates the texture with the given buffer
// buffer has to be the size of:
//     4 * size.x * _y
void r_texture2d_set(rTexture2D self, const void *buffer);

// updates buffer with the content of the texture
// buffer has to be the size of:
//     4 * size.x * _y
void r_texture2d_get(rTexture2D self, void *buffer);


void r_texture2d_filter_linear(rTexture2D self);

void r_texture2d_filter_nearest(rTexture2D self);

#endif //R_TEXTURE2D_H
