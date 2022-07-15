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

// creates a particle system with num rParticleRect's
// this class takes ownership of tex_sink (see .owns_tex)
RoParticle ro_particle_new(int num, rTexture tex_sink);

void ro_particle_kill(RoParticle *self);

// renders a subset of the particles
void ro_particle_render_sub(const RoParticle *self, su32 time_ms, int num, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_particle_set_texture(RoParticle *self, rTexture tex_sink);

// renders the particles into the gpu
static void ro_particle_render(const RoParticle *self, su32 time_ms, const mat4 *camera_mat) {
    ro_particle_render_sub(self, time_ms, self->num, camera_mat);
}

#endif //R_RO_PARTICLE_H
