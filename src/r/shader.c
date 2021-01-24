#include "utilc/strviu.h"
#include "r/definitions.h"
#include "r/shader.h"


static char *file_read(const char *filename) {
    SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
    if (rw == NULL) return NULL;

    Sint64 res_size = SDL_RWsize(rw);
    char *res = (char *) malloc(res_size + 1);

    Sint64 nb_read_total = 0, nb_read = 1;
    char *buf = res;
    while (nb_read_total < res_size && nb_read != 0) {
        nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
        nb_read_total += nb_read;
        buf += nb_read;
    }
    SDL_RWclose(rw);
    if (nb_read_total != res_size) {
        free(res);
        return NULL;
    }

    res[nb_read_total] = '\0';
    return res;
}


GLuint r_compile_shader(GLint type, const char *src) {
    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = malloc(log_len + 1);
        glGetShaderInfoLog(shader, log_len, NULL, buffer);
        SDL_Log("Shader compile failure in %s shader: %s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", buffer);
        free(buffer);

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}


GLuint r_compile_glsl(r_shader_source_s *sources, int n) {
    GLuint program = 0;
    GLuint shaders[n];

    // Compile shaders
    for (int i = 0; i < n; i++) {
        shaders[i] = r_compile_shader(sources[i].type, sources[i].src);
        if (shaders[i] == 0) {
            n = i;  // delete previous compiled shaders
            goto CLEAN_UP;
        }
    }

    // Combine shaders into program
    program = glCreateProgram();
    for (int i = 0; i < n; i++)
        glAttachShader(program, shaders[i]);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = malloc(log_len + 1);
        glGetProgramInfoLog(program, log_len, NULL, buffer);
        SDL_Log("Shader linking failure: %s", buffer);
        free(buffer);

        glDeleteProgram(program);
        program = 0;
    }

    CLEAN_UP:
    for (int i = 0; i < n; i++)
        glDeleteShader(shaders[i]);

    return program;
}


GLuint r_compile_shader_from_file(const char *file) {
    GLint type;
    const char *shader_begin;
    {
        strviu viu = ToStrViu(file);
        if (sv_ends_with_cstring(viu, ".vsh")) {
            type = GL_VERTEX_SHADER;
            shader_begin = R_VERTEX_BEGIN;
        } else if (sv_ends_with_cstring(viu, ".fsh")) {
            type = GL_FRAGMENT_SHADER;
            shader_begin = R_FRAGMENT_BEGIN;
        } else {
            SDL_Log("Compile shader failed, neither .vsh nor .fsh: %s", file);
            return 0;
        }
    }

    char *src = file_read(file);
    if (!src) {
        SDL_Log("Load shader file %s failed: %s", file, SDL_GetError());
        return 0;
    }


    char *shader = malloc(strlen(shader_begin) + strlen(src) + 1);
    strcpy(shader, shader_begin);
    strcat(shader, src);


    GLint out = r_compile_shader(type, shader);
    free(src);
    free(shader);
    return out;
}

GLuint r_compile_glsl_from_files(char **files) {
    int n = -1;
    while(files[++n]);

    GLuint program = 0;
    GLuint shaders[n];

    // Compile shaders
    for (int i = 0; i < n; i++) {
        shaders[i] = r_compile_shader_from_file(files[i]);
        if (shaders[i] == 0) {
            n = i;  // delete previous compiled shaders
            goto CLEAN_UP;
        }
    }

    // Combine shaders into program
    program = glCreateProgram();
    for (int i = 0; i < n; i++)
        glAttachShader(program, shaders[i]);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

        char *buffer = malloc(log_len + 1);
        glGetProgramInfoLog(program, log_len, NULL, buffer);
        SDL_Log("Shader linking failure: %s", buffer);
        free(buffer);

        glDeleteProgram(program);
        program = 0;
    }

    glUseProgram(program);

    CLEAN_UP:
    for (int i = 0; i < n; i++)
        glDeleteShader(shaders[i]);


    return program;
}
