#include "m/float.h"
#include "m/sca/int.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_batchstaticrefract.h"

static const vec4 VERTICES[6] = {
        {{-0.5, -0.5, 0, 1}},
        {{+0.5, -0.5, 0, 1}},
        {{-0.5, +0.5, 0, 1}},
        {{-0.5, +0.5, 0, 1}},
        {{+0.5, -0.5, 0, 1}},
        {{+0.5, +0.5, 0, 1}}
};

// 0-1 may overlap, so using 0-0.9999999 instead
static const vec4 TEX_COORDS[6] = {
        {{0.0000000, 0.9999999, 0, 1}},
        {{0.9999999, 0.9999999, 0, 1}},
        {{0.0000000, 0.0000000, 0, 1}},
        {{0.0000000, 0.0000000, 0, 1}},
        {{0.9999999, 0.9999999, 0, 1}},
        {{0.9999999, 0.0000000, 0, 1}}
};


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


RoBatchStaticRefract ro_batchstaticrefract_new(int num,
                                   rTexture tex_main_sink, rTexture tex_refraction_sink) {
    if(num <= 0)
        return ro_batchstaticrefract_new_invalid();

    r_render_error_check("ro_batchstaticrefract_newBEGIN");
    RoBatchStaticRefract self;

    self.rects = s_malloc(sizeof *self.rects * num);
    for (int i = 0; i < num; i++) {
        self.rects[i] = r_rect_new();
    }

    self.L.srects = s_new(struct rRectStatic_s, num*6);

    self.num = num;

    self.L.program = r_program_new_file("res/r/batchstaticrefract.glsl");
    const int loc_pos = 0;
    const int loc_uv = 1;
    const int loc_color = 2;
    const int loc_sprite = 3;

    self.tex_main = tex_main_sink;
    self.tex_refraction = tex_refraction_sink;
    self.owns_tex_main = true;
    self.owns_tex_refraction = true;

    // L.vao scope
    {
        glGenVertexArrays(1, &self.L.vao);
        glBindVertexArray(self.L.vao);

        // L.vbo
        {
            glGenBuffers(1, &self.L.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self.L.vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * 6 * sizeof(struct rRectStatic_s),
                         self.L.srects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self.L.vao);

            // pos
            glEnableVertexAttribArray(loc_pos);
            glVertexAttribPointer(loc_pos, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(struct rRectStatic_s),
                                  (void *) offsetof(struct rRectStatic_s, pos));


            // uv
            glEnableVertexAttribArray(loc_uv);
            glVertexAttribPointer(loc_uv, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(struct rRectStatic_s),
                                  (void *) offsetof(struct rRectStatic_s, uv));

            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(struct rRectStatic_s),
                                  (void *) offsetof(struct rRectStatic_s, color));

            // sprite
            glEnableVertexAttribArray(loc_sprite);
            glVertexAttribPointer(loc_sprite, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(struct rRectStatic_s),
                                  (void *) offsetof(struct rRectStatic_s, sprite));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }

    r_render_error_check("ro_batchstaticrefract_new");
    return self;
}


void ro_batchstaticrefract_kill(RoBatchStaticRefract *self) {
    if(!ro_batchstaticrefract_valid(self))
        return;
    s_free(self->rects);
    s_free(self->L.srects);
    glDeleteProgram(self->L.program);
    glDeleteVertexArrays(1, &self->L.vao);
    glDeleteBuffers(1, &self->L.vbo);
    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    *self = (RoBatchStaticRefract) {0};
}

void ro_batchstaticrefract_update_sub(const RoBatchStaticRefract *self, int offset, int size) {
    if(!ro_batchstaticrefract_valid(self))
        return;

    for(int i=0; i<self->num*6; i++) {
        int r_i = i/6;
        int v_i = i%6;
        self->L.srects[i].pos =
                mat4_mul_vec(self->rects[r_i].pose, VERTICES[v_i]).xy;
        self->L.srects[i].uv =
                mat4_mul_vec(self->rects[r_i].uv, TEX_COORDS[v_i]).xy;
        self->L.srects[i].color = self->rects[r_i].color;
        self->L.srects[i].sprite = self->rects[r_i].sprite;
    }

    r_render_error_check("ro_batchstaticrefract_updateBEGIN");
    glBindBuffer(GL_ARRAY_BUFFER, self->L.vbo);

    offset = isca_clamp(offset, 0, self->num - 1);
    size = isca_clamp(size, 1, self->num);

    if (offset + size > self->num) {
        int to_end = self->num - offset;
        int from_start = size - to_end;
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * 6 * sizeof(struct rRectStatic_s),
                        to_end * 6 * sizeof(struct rRectStatic_s),
                        self->L.srects + offset * 6);

        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        from_start * 6 *sizeof(struct rRectStatic_s),
                        self->L.srects);
    } else {
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * 6 * sizeof(struct rRectStatic_s),
                        size * 6 * sizeof(struct rRectStatic_s),
                        self->L.srects + offset * 6);

    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    r_render_error_check("ro_batchstaticrefract_update");
}


void ro_batchstaticrefract_render_sub(const RoBatchStaticRefract *self, int num, const mat4 *camera_mat, float scale,
                                const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer,
                                bool update_sub) {
    if(!ro_batchstaticrefract_valid(self))
        return;

    num = isca_clamp(num, 1, self->num);

    if (update_sub)
        ro_batchstaticrefract_update_sub(self, 0, num);

    r_render_error_check("ro_batchstaticrefract_renderBEGIN");

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

    // camera_scale_2 = camera_scale*2
    glUniform1f(glGetUniformLocation(self->L.program, "camera_scale_2"), r_render.camera_scale*2);

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
        glDrawArrays(GL_TRIANGLES, 0, 6 * num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_batchstaticrefract_render");
}

void ro_batchstaticrefract_set_texture_main(RoBatchStaticRefract *self, rTexture tex_main_sink) {
    if(!ro_batchstaticrefract_valid(self))
        return;

    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    self->tex_main = tex_main_sink;
}

void ro_batchstaticrefract_set_texture_refraction(RoBatchStaticRefract *self, rTexture tex_refraction_sink) {
    if(!ro_batchstaticrefract_valid(self))
        return;

    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    self->tex_refraction = tex_refraction_sink;
}
