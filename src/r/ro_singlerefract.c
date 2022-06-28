#include "m/float.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_singlerefract.h"


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


RoSingleRefract ro_singlerefract_new(
        const float *scale_ptr,
        rTexture tex_main_sink, rTexture tex_refraction_sink) {

    r_render_error_check("ro_singlerefract_newBEGIN");
    RoSingleRefract self;

    self.rect = r_rect_new();

    self.L.program = r_program_new_file("res/r/singlerefract.glsl");

    self.tex_main = tex_main_sink;
    self.tex_refraction = tex_refraction_sink;
    self.owns_tex_main = true;
    self.owns_tex_refraction = true;

    // needs a vao, even if its empty
    glGenVertexArrays(1, &self.L.vao);

    r_render_error_check("ro_singlerefract_new");
    return self;
}

void ro_singlerefract_kill(RoSingleRefract *self) {
    glDeleteProgram(self->L.program);
    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    *self = (RoSingleRefract) {0};
}


void ro_singlerefract_render(const RoSingleRefract *self, const mat4 *camera_mat, float scale,
                             const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer) {
    r_render_error_check("ro_singlerefract_renderBEGIN");

    if (!opt_view_aabb)
        opt_view_aabb = &VIEW_AABB_FULLSCREEN;
    if (!opt_framebuffer) {
        opt_framebuffer = &r_render.framebuffer_tex;

    }

    glUseProgram(self->L.program);

    // rect
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "pose"), 1, GL_FALSE, &self->rect.pose.m00);

    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "uv"), 1, GL_FALSE, &self->rect.uv.m00);

    glUniform4fv(glGetUniformLocation(self->L.program, "color"), 1, &self->rect.color.v0);

    glUniform2fv(glGetUniformLocation(self->L.program, "sprite"), 1, &self->rect.sprite.v0);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"), 1, GL_FALSE, &camera_mat->m00);

    vec2 sprites = vec2_cast_from_int(&self->tex_main.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);


    // fragment shader
    glUniform1f(glGetUniformLocation(self->L.program, "scale"), scale);

    glUniform4fv(glGetUniformLocation(self->L.program, "view_aabb"), 1, opt_view_aabb->v);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_main"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex_main.tex);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_refract"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex_refraction.tex);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_framebuffer"), 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, opt_framebuffer->tex);

    {
        glBindVertexArray(self->L.vao);
//        r_program_validate(self->L.program); // debug test
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_singlerefract_render");
}

void ro_singlerefract_set_texture_main(RoSingleRefract *self, rTexture tex_main_sink) {
    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    self->tex_main = tex_main_sink;
}

void ro_singlerefract_set_texture_refraction(RoSingleRefract *self, rTexture tex_refraction_sink) {
    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    self->tex_refraction = tex_refraction_sink;
}
