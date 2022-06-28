#include "m/float.h"
#include "m/sca/int.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_particle.h"

// update needs to be called each time before rendering to update the time values
static void update_sub(const RoParticle *self, uint32_t time_ms, int num) {
    r_render_error_check("ro_particle_updateBEGIN");
    glBindBuffer(GL_ARRAY_BUFFER, self->L.vbo);

    for (int i = 0; i < num; i++) {
        rParticleRect_s *r = &self->rects[i];
        r->delta_time = (time_ms - r->start_time_ms) / 1000.0f;
    }

    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    num * sizeof(rParticleRect_s),
                    self->rects);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    r_render_error_check("ro_particle_update");
}

//
// public
//

RoParticle ro_particle_new(int num, rTexture tex_sink) {
    r_render_error_check("ro_particle_newBEGIN");
    RoParticle self;

    s_assume(num > 0, "particle needs atleast 1 particlerect");
    self.rects = s_malloc(sizeof *self.rects * num);
    for (int i = 0; i < num; i++) {
        self.rects[i] = r_particlerect_new();
    }

    self.num = num;

    self.L.program = r_program_new_file("res/r/particle.glsl");
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_color = 8;
    const int loc_sprite_and_sprite_speed = 9;

    const int loc_speed = 10;
    const int loc_acc = 11;
    const int loc_axis_angle = 12;
    const int loc_color_speed = 13;

    const int loc_delta_time = 14;

    self.tex = tex_sink;
    self.owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self.L.vao);
        glBindVertexArray(self.L.vao);

        // vbo
        {
            glGenBuffers(1, &self.L.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self.L.vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rParticleRect_s),
                         self.rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self.L.vao);

            // pose
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // uv
            for (int c = 0; c < 4; c++) {
                int loc = loc_uv + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s),
                                      (void *) (offsetof(rParticleRect_s, uv) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }


            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            // sprite_and_sprite_speed
            glEnableVertexAttribArray(loc_sprite_and_sprite_speed);
            glVertexAttribPointer(loc_sprite_and_sprite_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, sprite));
            glVertexAttribDivisor(loc_sprite_and_sprite_speed, 1);

            // speed
            glEnableVertexAttribArray(loc_speed);
            glVertexAttribPointer(loc_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, speed));
            glVertexAttribDivisor(loc_speed, 1);

            // acc
            glEnableVertexAttribArray(loc_acc);
            glVertexAttribPointer(loc_acc, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, acc));
            glVertexAttribDivisor(loc_acc, 1);

            // axis_angle
            glEnableVertexAttribArray(loc_axis_angle);
            glVertexAttribPointer(loc_axis_angle, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, axis_angle));
            glVertexAttribDivisor(loc_axis_angle, 1);

            // color_speed
            glEnableVertexAttribArray(loc_color_speed);
            glVertexAttribPointer(loc_color_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color_speed));
            glVertexAttribDivisor(loc_color_speed, 1);

            // start_time
            glEnableVertexAttribArray(loc_delta_time);
            glVertexAttribPointer(loc_delta_time, 1, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, delta_time));
            glVertexAttribDivisor(loc_delta_time, 1);


            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }

    r_render_error_check("ro_particle_new");
    return self;
}


void ro_particle_kill(RoParticle *self) {
    s_free(self->rects);
    glDeleteProgram(self->L.program);
    glDeleteVertexArrays(1, &self->L.vao);
    glDeleteBuffers(1, &self->L.vbo);
    if (self->owns_tex)
        r_texture_kill(&self->tex);
    *self = (RoParticle) {0};
}


void ro_particle_render_sub(const RoParticle *self, uint32_t time_ms, int num, const mat4 *camera_mat) {
    num = isca_clamp(num, 1, self->num);

    update_sub(self, time_ms, num);

    r_render_error_check("ro_particle_renderBEGIN");
    glUseProgram(self->L.program);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"),
                       1, GL_FALSE, &camera_mat->m00);

    vec2 sprites = vec2_cast_from_int(&self->tex.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);

    glUniform1i(glGetUniformLocation(self->L.program, "tex"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex.tex);

    {
        glBindVertexArray(self->L.vao);
        // r_program_validate(self->L.program); // debug test
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_particle_render");
}

void ro_particle_set_texture(RoParticle *self, rTexture tex_sink) {
    if (self->owns_tex)
        r_texture_kill(&self->tex);
    self->tex = tex_sink;
}
