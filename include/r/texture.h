#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include <stdint.h>
#include <stdbool.h>
#include "core.h"

#define R_MAX_TEXTURES 1000

GLuint r_texture_from_img(SDL_Surface *img);

GLuint r_texture_from_file(const char *file);

GLuint r_texture_init_empty(bool filter);

void r_texture_update(GLuint tex, int width, int height, const uint8_t *buffer);

void r_texture_get_size(GLuint tex, int *w, int *h);

#endif //R_TEXTURE_H
