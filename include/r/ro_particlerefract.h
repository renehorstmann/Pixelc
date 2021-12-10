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

#include "rhc/alloc.h"
#include "ro_types.h"

// creates a particle system with refraction enabled and num rParticleRect's
// this class takes ownership of tex_*_sink (see .owns_*_tex)
RoParticleRefract ro_particlerefract_new(int num,
        rTexture tex_main_sink, rTexture tex_refraction_sink);


void ro_particlerefract_kill(RoParticleRefract *self);

// updates a subset of the particles into the gpu
void ro_particlerefract_update_sub(const RoParticleRefract *self, int offset, int size);

// renders a subset of the particles with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
// if update is true, update is called before rendering
void ro_particlerefract_render_sub(const RoParticleRefract *self, float time, int num, const mat4 *camera_mat, float scale, 
        const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer,
        bool update_sub);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_particlerefract_set_texture_main(RoParticleRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_particlerefract_set_texture_refraction(RoParticleRefract *self, rTexture tex_refraction_sink);

// updates the particles into the gpu
static void ro_particlerefract_update(const RoParticleRefract *self) {
    ro_particlerefract_update_sub(self, 0, self->num);
}

// renders the particles with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
// if update is true, update is called before rendering
static void ro_particlerefract_render(const RoParticleRefract *self, float time, const mat4 *camera_mat, float scale, 
        const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer,
        bool update) {
    ro_particlerefract_render_sub(self, time, self->num, camera_mat, scale, opt_view_aabb, opt_framebuffer, update);
}

#endif //R_RO_PARTICLEREFRACT_H
