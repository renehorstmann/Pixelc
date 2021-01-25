#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include <stdint.h>
#include <stdbool.h>
#include "core.h"

GLuint r_texture_init(int width, int height, const void *buffer);

GLuint r_texture_init_img(SDL_Surface *img);

GLuint r_texture_init_file(const char *file, int *opt_out_w, int *opt_out_h);

void r_texture_update(GLuint tex, int width, int height, const void *buffer);

void r_texture_filter_linear(GLuint tex);

void r_texture_filter_nearest(GLuint tex);


#endif //R_TEXTURE_H
