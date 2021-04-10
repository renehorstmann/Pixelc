#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include <stdint.h>
#include <stdbool.h>
#include "core.h"
#include "mathc/types/int.h"

GLuint r_texture_new(int cols, int rows, const void *buffer);

GLuint r_texture_new_img(SDL_Surface *img);

GLuint r_texture_new_file(const char *file, ivec2 *opt_out_size);

GLuint r_texture_new_empty(int cols, int rows);

GLuint r_texture_new_white_pixel();

void r_texture_update(GLuint tex, int cols, int rows, const void *buffer);

void r_texture_filter_linear(GLuint tex);

void r_texture_filter_nearest(GLuint tex);


#endif //R_TEXTURE_H
