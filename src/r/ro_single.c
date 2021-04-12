#include "mathc/float.h"
#include "r/shader.h"
#include "r/ro_single.h"


void ro_single_init(RoSingle *self, const float *vp, GLuint tex_sink) {
    self->rect.pose = mat4_eye();
    self->rect.uv = mat4_eye();
    self->rect.color = vec4_set(1);

    self->vp = vp;

    self->program = r_shader_compile_glsl_from_files((char *[]) {
            "res/r/single.vsh",
            "res/r/single.fsh",
            NULL
    });

    self->tex = tex_sink;
    self->owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // texture (using only unit 0)
        glUniform1i(glGetUniformLocation(self->program, "tex"), 0);

        glBindVertexArray(0);
    }
}

void ro_single_kill(RoSingle *self) {
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    if (self->owns_tex)
        glDeleteTextures(1, &self->tex);
    *self = (RoSingle) {0};
}


void ro_single_render(RoSingle *self) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "pose"), 1, GL_FALSE, &self->rect.pose.m00);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"), 1, GL_FALSE, self->vp);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "uv"), 1, GL_FALSE, &self->rect.uv.m00);

    glUniform4fv(glGetUniformLocation(self->program, "color"), 1, &self->rect.color.v0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        // r_shader_validate(self->program); // debug test
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void ro_single_set_texture(RoSingle *self, GLuint tex_sink) {
    if (self->owns_tex)
        glDeleteTextures(1, &self->tex);
    self->tex = tex_sink;
}
