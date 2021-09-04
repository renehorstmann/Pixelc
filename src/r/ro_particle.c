#include <float.h> // FLT_MAX
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "rhc/error.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_particle.h"


RoParticle ro_particle_new_a(int num, rTexture tex_sink, Allocator_s alloc) {
    r_render_error_check("ro_particle_newBEGIN");
    RoParticle self;
    self.L.allocator = alloc;
    
    assume(num>0, "particle needs atleast 1 particlerect");
    self.rects = alloc.malloc(alloc, num * sizeof(rParticleRect_s));
    assume(self.rects, "allocation failed");
    for(int i=0; i<num; i++) {
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
    
    const int loc_start_time = 14;

    self.L.tex = tex_sink;
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
            glEnableVertexAttribArray(loc_start_time);
            glVertexAttribPointer(loc_start_time, 1, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, start_time));
            glVertexAttribDivisor(loc_start_time, 1);


            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }
    
    r_render_error_check("ro_particle_new");
    return self;
}



void ro_particle_kill(RoParticle *self) {
    self->L.allocator.free(self->L.allocator, self->rects);
    glDeleteProgram(self->L.program);
    glDeleteVertexArrays(1, &self->L.vao);
    glDeleteBuffers(1, &self->L.vbo);
    if (self->owns_tex)
        r_texture_kill(&self->L.tex);
    *self = (RoParticle) {0};
}

void ro_particle_update_sub(RoParticle *self, int offset, int size) {
    r_render_error_check("ro_particle_updateBEGIN");
    glBindBuffer(GL_ARRAY_BUFFER, self->L.vbo);

    offset = isca_clamp(offset, 0, self->num-1);
    size = isca_clamp(size, 1, self->num);

    if (offset + size > self->num) {
        int to_end = self->num - offset;
        int from_start = size - to_end;
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * sizeof(rParticleRect_s),
                        to_end * sizeof(rParticleRect_s),
                        self->rects + offset);

        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        from_start * sizeof(rParticleRect_s),
                        self->rects);
    } else {
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * sizeof(rParticleRect_s),
                        size * sizeof(rParticleRect_s),
                        self->rects + offset);

    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    r_render_error_check("ro_particle_update");
}

void ro_particle_render_sub(RoParticle *self, float time, int num, const mat4 *camera_mat) {
    r_render_error_check("ro_particle_renderBEGIN");
    glUseProgram(self->L.program);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"),
                       1, GL_FALSE, &camera_mat->m00);

    vec2 sprites = vec2_cast_from_int(&self->L.tex.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);
    
    glUniform1f(glGetUniformLocation(self->L.program, "time"), time);

    glUniform1i(glGetUniformLocation(self->L.program, "tex"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->L.tex.tex);

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
        r_texture_kill(&self->L.tex);
    self->L.tex = tex_sink;
}
