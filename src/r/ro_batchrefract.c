#include "m/float.h"
#include "m/sca/int.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_batchrefract.h"


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


RoBatchRefract ro_batchrefract_new(int num,
                                   rTexture tex_main_sink, rTexture tex_refraction_sink) {
    r_render_error_check("ro_batchrefract_newBEGIN");
    RoBatchRefract self;

    s_assume(num > 0, "batch needs atleast 1 rect");
    self.rects = s_malloc(sizeof *self.rects * num);
    for (int i = 0; i < num; i++) {
        self.rects[i] = r_rect_new();
    }

    self.num = num;

    self.L.program = r_program_new_file("res/r/batchrefract.glsl");
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_color = 8;
    const int loc_sprite = 9;

    self.tex_main = tex_main_sink;
    self.tex_refraction = tex_refraction_sink;
    self.owns_tex_main = true;
    self.owns_tex_refraction = true;

    // vao scope
    {
        glGenVertexArrays(1, &self.L.vao);
        glBindVertexArray(self.L.vao);

        // vbo
        {
            glGenBuffers(1, &self.L.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self.L.vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rRect_s),
                         self.rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self.L.vao);

            // pose
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rRect_s), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // uv
            for (int c = 0; c < 4; c++) {
                int loc = loc_uv + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rRect_s), (void *) (offsetof(rRect_s, uv) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rRect_s),
                                  (void *) offsetof(rRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            // sprite
            glEnableVertexAttribArray(loc_sprite);
            glVertexAttribPointer(loc_sprite, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(rRect_s),
                                  (void *) offsetof(rRect_s, sprite));
            glVertexAttribDivisor(loc_sprite, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }

    r_render_error_check("ro_batchrefract_new");
    return self;
}


void ro_batchrefract_kill(RoBatchRefract *self) {
    s_free(self->rects);
    glDeleteProgram(self->L.program);
    glDeleteVertexArrays(1, &self->L.vao);
    glDeleteBuffers(1, &self->L.vbo);
    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    *self = (RoBatchRefract) {0};
}

void ro_batchrefract_update_sub(const RoBatchRefract *self, int offset, int size) {
    r_render_error_check("ro_batchrefract_updateBEGIN");
    glBindBuffer(GL_ARRAY_BUFFER, self->L.vbo);

    offset = isca_clamp(offset, 0, self->num - 1);
    size = isca_clamp(size, 1, self->num);

    if (offset + size > self->num) {
        int to_end = self->num - offset;
        int from_start = size - to_end;
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * sizeof(rRect_s),
                        to_end * sizeof(rRect_s),
                        self->rects + offset);

        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        from_start * sizeof(rRect_s),
                        self->rects);
    } else {
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * sizeof(rRect_s),
                        size * sizeof(rRect_s),
                        self->rects + offset);

    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    r_render_error_check("ro_batchrefract_update");
}


void ro_batchrefract_render_sub(const RoBatchRefract *self, int num, const mat4 *camera_mat, float scale,
                                const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer,
                                bool update_sub) {
    num = isca_clamp(num, 1, self->num);

    if (update_sub)
        ro_batchrefract_update_sub(self, 0, num);
    r_render_error_check("ro_batchrefract_renderBEGIN");

    if (!opt_view_aabb)
        opt_view_aabb = &VIEW_AABB_FULLSCREEN;
    if (!opt_framebuffer) {
        opt_framebuffer = &r_render.framebuffer_tex;

    }

    glUseProgram(self->L.program);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"),
                       1, GL_FALSE, &camera_mat->m00);

    vec2 sprites = vec2_cast_from_int(&self->tex_main.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);

    // fragment shader
    glUniform1f(glGetUniformLocation(self->L.program, "scale"), scale);

    glUniform4fv(glGetUniformLocation(self->L.program, "view_aabb"), 1, opt_view_aabb->v);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_main"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex_main.tex);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_refraction"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex_refraction.tex);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_framebuffer"), 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, opt_framebuffer->tex);

    {
        glBindVertexArray(self->L.vao);
        // r_program_validate(self->L.program); // debug test
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_batchrefract_render");
}

void ro_batchrefract_set_texture_main(RoBatchRefract *self, rTexture tex_main_sink) {
    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    self->tex_main = tex_main_sink;
}

void ro_batchrefract_set_texture_refraction(RoBatchRefract *self, rTexture tex_refraction_sink) {
    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    self->tex_refraction = tex_refraction_sink;
}
