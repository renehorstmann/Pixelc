#ifndef R_RO_REFRACT_PARTICLE_H
#define R_RO_REFRACT_PARTICLE_H

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"
#include "rect.h"


// Particle system, with refraction and reflection
////
//// Uses 3 textures in total
//// 1: default texture
//// 2: refraction map
////    r: 128+offset for x refraction
////    g: 128+offset for y
////    b: x_stretch_value + y_stretch_value * 16
////          normal: 12+12*16    (8+4)
////          mirror x: 4+12*16   (8-4)
////    a: refraction alpha
//// 3: framebuffer texture, to grab pixels for the refraction
////    defaults to r_render.framebuffer_tex
//// view_aabb is the screen space in which the rect is rendered
////    in texture space (origin is top left) [0:1]
////    as center_x, _y, radius_x, _y
////    defaults to fullscreen (0.5, 0.5, 0.5, 0.5)
typedef struct {
    rParticleRect_s *rects;
    int num;
    const float *vp; // mat4
    const float *scale; // float
    const float *view_aabb; // vec4
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex_main;
    GLuint tex_refraction;
    const GLuint *tex_framebuffer_ptr;  // init as &r_render.framebuffer_tex
    bool owns_tex_main;
    bool owns_tex_refraction;
} RoRefractParticle;

void ro_refract_particle_init(RoRefractParticle *self, int num,
        const float *vp, const float *scale_ptr,
        GLuint tex_main_sink, GLuint tex_refraction_sink);

void ro_refract_particle_kill(RoRefractParticle *self);

void ro_refract_particle_update_sub(RoRefractParticle *self, int offset, int size);

void ro_refract_particle_render_sub(RoRefractParticle *self, float time, int num);

void ro_refract_particle_set_texture_main(RoRefractParticle *self, GLuint tex_main_sink);

void ro_refract_particle_set_texture_refraction(RoRefractParticle *self, GLuint tex_refraction_sink);


static void ro_refract_particle_update(RoRefractParticle *self) {
    ro_refract_particle_update_sub(self, 0, self->num);
}

static void ro_refract_particle_render(RoRefractParticle *self, float time) {
    ro_refract_particle_render_sub(self, time, self->num);
}

#endif //R_RO_REFRACT_PARTICLE_H
