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

#include "rect.h"
#include "texture.h"
#include "texture2d.h"

// Like RoParticle, but with refraction
typedef struct {
    rParticleRect_s *rects;
    int num;
    rTexture tex_main;          // used main texture
    rTexture tex_refraction;    // used refraction texture
    bool owns_tex_main;         // if true (default), tex_main will be killed by this class
    bool owns_tex_refraction;   // if true (default), tex_refraction will be killer by this clasd

    struct {
        GLuint program;         // shader
        GLuint vao;             // internal vertex array object
        GLuint vbo;             // internal vertex buffer object
    } L;
} RoParticleRefract;

// returns true if the particle systen seems to be in a valid state, GL errors ignored
static bool ro_particlerefract_valid(const RoParticleRefract *self) {
    return self->rects!=NULL && self->num;
}

// returns a new invalid particle system
static RoParticleRefract ro_particlerefract_new_invalid() {
    return (RoParticleRefract) {0};
}

// creates a particle system with refraction enabled and num rParticleRect's
// this class takes ownership of tex_*_sink (see .owns_*_tex)
// returns an invalid, for num<=0
RoParticleRefract ro_particlerefract_new(int num,
                                         rTexture tex_main_sink, rTexture tex_refraction_sink);


void ro_particlerefract_kill(RoParticleRefract *self);


// renders a subset of the particles with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
// if update is true, update is called before rendering
void ro_particlerefract_render_sub(const RoParticleRefract *self, su32 time_ms, int num, const mat4 *camera_mat,
                                   float scale, const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_particlerefract_set_texture_main(RoParticleRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_particlerefract_set_texture_refraction(RoParticleRefract *self, rTexture tex_refraction_sink);

// renders the particles with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
static void ro_particlerefract_render(const RoParticleRefract *self, su32 time_ms, const mat4 *camera_mat,
                                      float scale, const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer) {
    ro_particlerefract_render_sub(self, time_ms, self->num, camera_mat, scale, opt_view_aabb, opt_framebuffer);
}

#endif //R_RO_PARTICLEREFRACT_H
