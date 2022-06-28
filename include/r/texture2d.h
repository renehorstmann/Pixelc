#ifndef R_TEXTURE2D_H
#define R_TEXTURE2D_H

//
// load and setup textures as simple 2D textures
//

#include "core.h"
#include "m/types/int.h"

// Simple Texture, without a sprite grid
typedef struct {
    GLuint tex;    // GL_TEXTURE_2D
    ivec2 size;
} rTexture2D;

static bool r_texture2d_valid(rTexture2D self) {
    return self.tex > 0
           && self.size.x > 0 && self.size.y > 0;
}

static rTexture2D r_texture2d_new_invalid() {
    return (rTexture2D) {0};
}

// returns a new texture from an optional buffer
rTexture2D r_texture2d_new(int image_cols, int image_rows, const void *opt_buffer);

// returns a new texture, loaded from an SDL_Surface
rTexture2D r_texture2d_new_sdl_surface(const SDL_Surface *img);

// returns a new texture, loaded from a file (.png)
rTexture2D r_texture2d_new_file(const char *file);

// returns a new white texture, useful for quads with color, specified in the rRect
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

// sets the rendering interpolation to linear (normal images)
void r_texture2d_filter_linear(rTexture2D self);

// sets the rendering interpolation to nearest (pixelart)
void r_texture2d_filter_nearest(rTexture2D self);

// sets the texture wrap mode to repeat, so that the texture will be repeated, if uv is reset
void r_texture2d_wrap_repeat(rTexture2D self);

// sets the texture wrap mode to clamp, so that the border pixels will be repeated, if uv is reset (default)
void r_texture2d_wrap_clamp(rTexture2D self);

#endif //R_TEXTURE2D_H
