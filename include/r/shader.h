#ifndef R_SHADER_H
#define R_SHADER_H

#include "core.h"

GLuint r_compile_shader(GLint type, const char *src);

typedef struct r_shader_source_s {
    GLint type;
    const char *src;
} r_shader_source_s;

GLuint r_compile_glsl(r_shader_source_s *sources, int n);

GLuint r_compile_shader_from_file(const char *file);

GLuint r_compile_glsl_from_files(char **files);

#endif //R_SHADER_H
