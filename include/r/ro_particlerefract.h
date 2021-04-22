#ifndef R_RO_PARTICLEREFRACT_H
#define R_RO_PARTICLEREFRACT_H

//
// particle system
// its like ro_particle, but with additional reflection / refraction support.
//
//// uses 3 textures in total
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
//

#include "mathc/types/float.h"
#include "rhc/allocator.h"
#include "core.h"
#include "rect.h"
#include "texture.h"
#include "texture2d.h"


typedef struct {
    rParticleRect_s *rects;
    int num;
    const float *vp;                    // mat4
    const float *scale;                 // float
    const float *view_aabb;             // vec4
    GLuint program;                     // shader
    GLuint vao;                         // internal vertex array object
    GLuint vbo;                         // internal vertex buffer object
    rTexture tex_main;                  // used main texture
    rTexture tex_refraction;              // used refraction texture
    const rTexture2D *tex_framebuffer_ptr;  // init as &r_render.framebuffer_tex
    bool owns_tex_main;                 // if true, the textures will be deleted by this class
    bool owns_tex_refraction;
    
    Allocator_s allocator;
} RoParticleRefract;

RoParticleRefract ro_particlerefract_new_a(int num,
        const float *vp, const float *scale_ptr,
        rTexture tex_main_sink, 
        rTexture tex_refraction_sink, 
        Allocator_s alloc);                              

static RoParticleRefract ro_particlerefract_new(int num,
        const float *vp, const float *scale_ptr,
        rTexture tex_main_sink, 
        rTexture tex_refraction_sink) {
    return ro_particlerefract_new_a(num, vp, scale_ptr,
            tex_main_sink, tex_refraction_sink,
            allocator_new_default());
}
 

void ro_particlerefract_kill(RoParticleRefract *self);

// updates a subset of the particles into the gpu
void ro_particlerefract_update_sub(RoParticleRefract *self, int offset, int size);

// renders a subset of the particles
void ro_particlerefract_render_sub(RoParticleRefract *self, float time, int num);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_particlerefract_set_texture_main(RoParticleRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_particlerefract_set_texture_refraction(RoParticleRefract *self, rTexture tex_refraction_sink);


static void ro_particlerefract_update(RoParticleRefract *self) {
    ro_particlerefract_update_sub(self, 0, self->num);
}

static void ro_particlerefract_render(RoParticleRefract *self, float time) {
    ro_particlerefract_render_sub(self, time, self->num);
}

#endif //R_RO_PARTICLEREFRACT_H
