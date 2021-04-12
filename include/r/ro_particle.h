#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"
#include "rect.h"


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
} RoParticle;

void ro_particle_init(RoParticle *self, int num, const float *vp, GLuint tex_sink);

void ro_particle_kill(RoParticle *self);

void ro_particle_update_sub(RoParticle *self, int offset, int size);

void ro_particle_render_sub(RoParticle *self, float time, int num);

void ro_particle_set_texture(RoParticle *self, GLuint tex_sink);


static void ro_particle_update(RoParticle *self) {
    ro_particle_update_sub(self, 0, self->num);
}

static void ro_particle_render(RoParticle *self, float time) {
    ro_particle_render_sub(self, time, self->num);
}

#endif //R_RO_PARTICLE_H
