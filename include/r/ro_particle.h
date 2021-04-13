#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

//
// particle system
//

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"
#include "rect.h"

typedef struct {
    rParticleRect_s *rects;
    int num;
    const float *vp;    // mat4 camera view perspective
    GLuint program;     // shader
    GLuint vao;         // internal vertex array object
    GLuint vbo;         // internal vertex buffer object
    GLuint tex;         // used texture
    bool owns_tex;      // if true, the texture will be deleted by this class
} RoParticle;

void ro_particle_init(RoParticle *self, int num, const float *vp, GLuint tex_sink);

void ro_particle_kill(RoParticle *self);

// updates a subset of the particles into the gpu
void ro_particle_update_sub(RoParticle *self, int offset, int size);

// renders a subset of the particles
void ro_particle_render_sub(RoParticle *self, float time, int num);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_particle_set_texture(RoParticle *self, GLuint tex_sink);

static void ro_particle_update(RoParticle *self) {
    ro_particle_update_sub(self, 0, self->num);
}

static void ro_particle_render(RoParticle *self, float time) {
    ro_particle_render_sub(self, time, self->num);
}

#endif //R_RO_PARTICLE_H
