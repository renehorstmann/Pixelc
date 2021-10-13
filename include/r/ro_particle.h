#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

//
// particle system
//

#include "rhc/alloc.h"
#include "ro_types.h"


RoParticle ro_particle_new_a(int num, rTexture tex_sink, Allocator_s alloc);

static RoParticle ro_particle_new(int num, rTexture tex_sink) {
    return ro_particle_new_a(num, tex_sink, rhc_allocator_new());
}

void ro_particle_kill(RoParticle *self);

// updates a subset of the particles into the gpu
void ro_particle_update_sub(const RoParticle *self, int offset, int size);

// renders a subset of the particles
void ro_particle_render_sub(const RoParticle *self, float time, int num, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_particle_set_texture(RoParticle *self, rTexture tex_sink);

static void ro_particle_update(const RoParticle *self) {
    ro_particle_update_sub(self, 0, self->num);
}

static void ro_particle_render(const RoParticle *self, float time, const mat4 *camera_mat) {
    ro_particle_render_sub(self, time, self->num, camera_mat);
}

#endif //R_RO_PARTICLE_H
