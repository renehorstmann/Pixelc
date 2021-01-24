#ifndef R_PARTICLE_H
#define R_PARTICLE_H

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"

typedef struct rParticleRect_s {
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

typedef struct rParticle {
    rParticleRect_s *rects;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    bool owns_tex;
} rParticle;

void r_particle_init(rParticle *self, int num, const float *vp, GLuint tex_sink);

void r_particle_kill(rParticle *self);

void r_particle_update(rParticle *self, int offset, int size);

void r_particle_render(rParticle *self, float time);

void r_particle_set_texture(rParticle *self, GLuint tex);

#endif //R_PARTICLE_H
