#ifndef R_PROGRAM_H
#define R_PROGRAM_H

//
// create and compile shader programs
//

#include "core.h"
#include "s/str.h"


// tests if the shader is valid
static bool r_programshader_valid(GLuint shader) {
    return shader > 0;
}

// tests if the program is valid
static bool r_program_valid(GLuint program) {
    return program > 0;
}

// compiles a shader
GLuint r_programshader_new(sStr_s source, GLint shader_type);

// compiles a shader, src=file
GLuint r_programshader_new_file(const char *file, GLint shader_type);

// creates a program from given shaders
GLuint r_program_new(const GLuint *shaders, int n, bool delete_shaders);

// loads a program from a single file (only vertex and fragment shader)
GLuint r_program_new_file(const char *file);

// tests if a draw call is valid (heavy call)
void r_program_validate(GLuint program);


#endif //R_PROGRAM_H
