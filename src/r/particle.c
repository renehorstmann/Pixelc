#include "mathc/float.h"
#include "utilc/alloc.h"
#include "utilc/assume.h"
#include "r/r.h"
#include "r/particle.h"


static void init_rects(rParticleRect_s *instances, int num) {
    for (int i = 0; i < num; i++) {
        rParticleRect_s *r = &instances[i];
        r->pose = mat4_eye();
        r->uv = mat4_eye();
        r->speed = vec4_set(0);
        r->acc = vec4_set(0);
        r->axis_angle = (vec4) {0, 0, 1, 0};
        r->color = vec4_set(1);
        r->color_speed = vec4_set(0);
        r->uv_step = vec2_set(0);
        r->uv_time = FLT_MAX;
        r->start_time = 0;
    }
}

void r_particle_init(rParticle *self, int num, const float *vp, GLuint tex_sink) {
    self->rects = New(rParticleRect_s, num);
    init_rects(self->rects, num);

    self->num = num;
    self->vp = vp;

    self->program = r_compile_glsl_from_files((char *[]) {
            "res/shader/r/particle.vsh",
            "res/shader/r/particle.fsh",
            NULL});
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_speed = 8;
    const int loc_acc = 9;
    const int loc_axis_angle = 10;
    const int loc_color = 11;
    const int loc_color_speed = 12;
    const int loc_uv_step = 13;
    const int loc_uv_time = 14;
    const int loc_start_time = 15;

    self->tex = tex_sink;
    self->owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // texture (using only unit 0)
        glUniform1i(glGetUniformLocation(self->program, "tex"), 0);

        // vbo
        {
            glGenBuffers(1, &self->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rParticleRect_s),
                         self->rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self->vao);

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

            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            // color_speed
            glEnableVertexAttribArray(loc_color_speed);
            glVertexAttribPointer(loc_color_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color_speed));
            glVertexAttribDivisor(loc_color_speed, 1);

            // uv_step
            glEnableVertexAttribArray(loc_uv_step);
            glVertexAttribPointer(loc_uv_step, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, uv_step));
            glVertexAttribDivisor(loc_uv_step, 1);

            // uv_time
            glEnableVertexAttribArray(loc_uv_time);
            glVertexAttribPointer(loc_uv_time, 1, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, uv_time));
            glVertexAttribDivisor(loc_uv_time, 1);

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
}

void r_particle_kill(rParticle *self) {
    free(self->rects);
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    if (self->owns_tex)
        glDeleteTextures(1, &self->tex);
    *self = (rParticle) {0};
}

static int clamp_range(int i, int begin, int end) {
	if(i < begin)
	    i = begin;
	if(i >= end)
	    i = end - 1;
	return i;
}

void r_particle_update(rParticle *self, int offset, int size) {
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
    
    offset = clamp_range(offset, 0, self->num);
    size = clamp_range(size, 1, self->num+1);
    
    if(offset + size > self->num) {
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
}

void r_particle_render(rParticle *self, float time) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

    glUniform1f(glGetUniformLocation(self->program, "time"), time);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self->tex);

    {
        glBindVertexArray(self->vao);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, self->num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void r_particle_set_texture(rParticle *self, GLuint tex) {
    if (self->owns_tex)
        glDeleteTextures(1, &self->tex);
    self->tex = tex;
}

