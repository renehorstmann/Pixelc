#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

//
// particle system
//

#include "mathc/types/float.h"
#include "rhc/allocator.h"
#include "core.h"
#include "rect.h"
#include "texture.h"

typedef struct {
    rParticleRect_s *rects;
    int num;
    const float *vp;    // mat4 camera view perspective
    GLuint program;     // shader
    GLuint vao;         // internal vertex array object
    GLuint vbo;         // internal vertex buffer object
    rTexture tex;         // used texture
    bool owns_tex;      // if true, the texture will be deleted by this class
    
    Allocator_s allocator;
} RoParticle;


RoParticle ro_particle_new_a(int num, const float *vp, rTexture tex_sink, Allocator_s alloc);

static RoParticle ro_particle_new(int num, const float *vp, rTexture tex_sink) {
    return ro_particle_new_a(num, vp, tex_sink, allocator_new_default());
}

void ro_particle_kill(RoParticle *self);

// updates a subset of the particles into the gpu
void ro_particle_update_sub(RoParticle *self, int offset, int size);

// renders a subset of the particles
void ro_particle_render_sub(RoParticle *self, float time, int num);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_particle_set_texture(RoParticle *self, rTexture tex_sink);

static void ro_particle_update(RoParticle *self) {
    ro_particle_update_sub(self, 0, self->num);
}

static void ro_particle_render(RoParticle *self, float time) {
    ro_particle_render_sub(self, time, self->num);
}

#endif //R_RO_PARTICLE_H
