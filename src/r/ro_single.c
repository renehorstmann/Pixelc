#include "m/float.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_single.h"


RoSingle ro_single_new(rTexture tex_sink) {
    r_render_error_check("ro_single_newBEGIN");
    RoSingle self;

    self.rect = r_rect_new();

    self.L.program = r_program_new_file("res/r/single.glsl");

    self.tex = tex_sink;
    self.owns_tex = true;

    // needs a vao, even if its empty
    glGenVertexArrays(1, &self.L.vao);

    r_render_error_check("ro_single_new");
    return self;
}

void ro_single_kill(RoSingle *self) {
    glDeleteProgram(self->L.program);
    if (self->owns_tex)
        r_texture_kill(&self->tex);
    *self = (RoSingle) {0};
}


void ro_single_render(const RoSingle *self, const mat4 *camera_mat) {
    r_render_error_check("ro_single_renderBEGIN");
    glUseProgram(self->L.program);

    // rect
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "pose"), 1, GL_FALSE, &self->rect.pose.m00);

    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "uv"), 1, GL_FALSE, &self->rect.uv.m00);

    glUniform4fv(glGetUniformLocation(self->L.program, "color"), 1, &self->rect.color.v0);

    glUniform2fv(glGetUniformLocation(self->L.program, "sprite"), 1, &self->rect.sprite.v0);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"), 1, GL_FALSE, &camera_mat->m00);

    vec2 sprites = vec2_cast_from_int(&self->tex.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);

    glUniform1i(glGetUniformLocation(self->L.program, "tex"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex.tex);

    {
        glBindVertexArray(self->L.vao);
//        r_program_validate(self->L.program); // debug test
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_single_render");
}

void ro_single_set_texture(RoSingle *self, rTexture tex_sink) {
    if (self->owns_tex)
        r_texture_kill(&self->tex);
    self->tex = tex_sink;
}
