#include "s/s_full.h"
#include "r/render.h"
#include "r/program.h"


GLuint r_programshader_new(sStr_s source, GLint shader_type) {
    r_render_error_check("r_programshader_new");
    // check source available
    if (s_str_empty(source))
        return 0;

#ifdef OPTION_GLES
    const char *version = "#version 300 es\n";
#else
    const char *version = "#version 330 core\n";
#endif

    const char *type = NULL;
    if (shader_type == GL_VERTEX_SHADER)
        type = "#define VERTEX\n";
    if (shader_type == GL_FRAGMENT_SHADER)
        type = "#define FRAGMENT\n";

    s_assume(type, "neither vertex nor fragment shader used: %i", shader_type);

    const char *option_gles = "";
#ifdef OPTION_GLES
    option_gles = "#define OPTION_GLES\n";
#endif

    GLint shader = glCreateShader(shader_type);

    glShaderSource(shader, 4,
                   (const char *[]) {version, type, option_gles, source.data},
                   (GLint[]) {strlen(version), strlen(type), strlen(option_gles), source.size});

    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = s_malloc(log_len + 1);
        glGetShaderInfoLog(shader, log_len, NULL, buffer);
        s_log_error("Shader compile failure in %s shader: %s", type, buffer);
        s_free(buffer);

        glDeleteShader(shader);
        shader = 0;
    }
    r_render_error_check("r_programshader_new");
    return shader;
}

GLuint r_programshader_new_file(const char *file, GLint shader_type) {
    r_render_error_check("r_programshader_new_fileBEGIN");
    sString *source = s_file_read(file, true);
    GLuint shader = r_programshader_new(s_string_get_str(source), shader_type);
    s_string_kill(&source);
    r_render_error_check("r_programshader_new_file");
    return shader;
}

GLuint r_program_new(const GLuint *shaders, int n, bool delete_shaders) {
    r_render_error_check("r_program_newBEGIN");
    // check each shader valid
    for (int i = 0; i < n; i++) {
        if (!r_programshader_valid(shaders[i]))
            return 0;
    }

    // Combine shaders into program
    GLuint program = glCreateProgram();
    for (int i = 0; i < n; i++)
        glAttachShader(program, shaders[i]);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = s_malloc(log_len + 1);
        glGetProgramInfoLog(program, log_len, NULL, buffer);
        s_log_error("Shader linking failure: %s", buffer);
        s_free(buffer);

        glDeleteProgram(program);
        program = 0;
    }

    if (delete_shaders) {
        for (int i = 0; i < n; i++)
            glDeleteShader(shaders[i]);
    }

    r_render_error_check("r_program_new");
    return program;
}

GLuint r_program_new_file(const char *file) {
    r_render_error_check("r_program_new_fileBEGIN");
    sString *source = s_file_read(file, true);
    GLuint vertex = r_programshader_new(s_string_get_str(source), GL_VERTEX_SHADER);
    GLuint fragment = r_programshader_new(s_string_get_str(source), GL_FRAGMENT_SHADER);

    GLuint program = r_program_new((const GLuint[]) {vertex, fragment}, 2, false);

    // safe to pass 0
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    s_string_kill(&source);

    r_render_error_check("r_program_new_file");
    return program;
}

void r_program_validate(GLuint program) {
    r_render_error_check("r_program_validateBEGIN");
    if (!r_program_valid(program))
        return;

    glValidateProgram(program);

    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = s_malloc(log_len + 1);
        glGetProgramInfoLog(program, log_len, NULL, buffer);
        s_log_error("Program validate failure: %s", buffer);
        s_free(buffer);
    }
    r_render_error_check("r_program_validate");
}
