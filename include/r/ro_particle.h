#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"

typedef struct {
    mat4 pose;
    mat4 uv;
    vec4 speed;
    vec4 acc;
    vec4 axis_angle;
    vec4 color;
    vec4 color_speed;
    vec2 uv_step;
    float uv_time;
    float start_time;
} rParticleRect_s;

// Particle system
typedef struct {
    rParticleRect_s *rects;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    bool owns_tex;
} rRoParticle;

void r_ro_particle_init(rRoParticle *self, int num, const float *vp, GLuint tex_sink);

void r_ro_particle_kill(rRoParticle *self);

void r_ro_particle_update_sub(rRoParticle *self, int offset, int size);

void r_ro_particle_render_sub(rRoParticle *self, float time, int num);

void r_ro_particle_set_texture(rRoParticle *self, GLuint tex_sink);


static void r_ro_particle_update(rRoParticle *self) {
	r_ro_particle_update_sub(self, 0, self->num);
}

static void r_ro_particle_render(rRoParticle *self, float time) {
	r_ro_particle_render_sub(self, time, self->num);
}

#endif //R_RO_PARTICLE_H
