#ifndef R_SHADER_H
#define R_SHADER_H

//
// create and compile shader programs
//

#include "core.h"

GLuint r_shader_compile(GLint type, const char *src);

typedef struct {
    GLint type;
    const char *src;
} rShaderSource_s;

GLuint r_shader_compile_glsl(rShaderSource_s *sources, int n);

GLuint r_shader_compile_from_file(const char *file);

GLuint r_shader_compile_glsl_from_files(char **files);

void r_shader_validate(GLuint program);

#endif //R_SHADER_H
