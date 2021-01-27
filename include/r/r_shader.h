#ifndef R_SHADER_H
#define R_SHADER_H

#include "core.h"

GLuint r_compile_shader(GLint type, const char *src);

typedef struct {
    GLint type;
    const char *src;
} rShaderSource_s;

GLuint r_compile_glsl(rShaderSource_s *sources, int n);

GLuint r_compile_shader_from_file(const char *file);

GLuint r_compile_glsl_from_files(char **files);

#endif //R_SHADER_H
