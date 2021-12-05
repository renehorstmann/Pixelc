#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

//
// particle system
//

#include "ro_types.h"

// creates a particle system with num rParticleRect's
// this class takes ownership of tex_sink (see .owns_tex)
RoParticle ro_particle_new(int num, rTexture tex_sink);

void ro_particle_kill(RoParticle *self);

// updates a subset of the particles into the gpu
void ro_particle_update_sub(const RoParticle *self, int offset, int size);

// renders a subset of the particles
void ro_particle_render_sub(const RoParticle *self, float time, int num, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_particle_set_texture(RoParticle *self, rTexture tex_sink);

// updates the particles into the gpu
static void ro_particle_update(const RoParticle *self) {
    ro_particle_update_sub(self, 0, self->num);
}

// renders the particles into the gpu
static void ro_particle_render(const RoParticle *self, float time, const mat4 *camera_mat) {
    ro_particle_render_sub(self, time, self->num, camera_mat);
}

#endif //R_RO_PARTICLE_H
