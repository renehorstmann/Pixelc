#ifndef R_RO_PARTICLE_H
#define R_RO_PARTICLE_H

//
// particle system
//

#include "rect.h"
#include "texture.h"

// Renders multiple particle rects in a draw call
typedef struct {
    rParticleRect_s *rects;
    int num;
    rTexture tex;       // used texture
    bool owns_tex;      // if true (default), tex will be killed by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
    } L;
} RoParticle;

// returns true if the particle systen seems to be in a valid state, GL errors ignored
static bool ro_particle_valid(const RoParticle *self) {
    return self->rects!=NULL && self->num;
}

// returns a new invalid particle system
static RoParticle ro_particle_new_invalid() {
    return (RoParticle) {0};
}

// creates a particle system with num rParticleRect's
// this class takes ownership of tex_sink (see .owns_tex)
// returns an invalid, for num<=0
RoParticle ro_particle_new(int num, rTexture tex_sink);

void ro_particle_kill(RoParticle *self);

// renders a subset of the particles
// particles delta_time are just read, not set
void ro_particle_render_raw_sub(const RoParticle *self, int num, const mat4 *camera_mat);

// renders a subset of the particles
// particles delta_time = (time_ms - start_time_ms) / 1000.0f
void ro_particle_render_sub(const RoParticle *self, su32 time_ms, int num, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_particle_set_texture(RoParticle *self, rTexture tex_sink);

// renders the particles into the gpu
// particles delta_time are just read, not set
static void ro_particle_render(const RoParticle *self, su32 time_ms, const mat4 *camera_mat) {
    ro_particle_render_sub(self, time_ms, self->num, camera_mat);
}

// renders the particles into the gpu
// particles delta_time = (time_ms - start_time_ms) / 1000.0f
static void ro_particle_render_raw(const RoParticle *self, const mat4 *camera_mat) {
    ro_particle_render_raw_sub(self, self->num, camera_mat);
}

#endif //R_RO_PARTICLE_H
