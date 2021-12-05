#ifndef R_RO_BATCHREFRACT_H
#define R_RO_BATCHREFRACT_H

//
// class to render multiple rects with a single draw call.
// its like ro_batch, but with additional reflection / refraction support.
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

#include "ro_types.h"

// creates a new batch with refraction enabled and num rRect's
// this class takes ownership of tex_*_sink (see .owns_*_tex)
RoBatchRefract ro_batchrefract_new(int num,
        rTexture tex_main_sink, rTexture tex_refraction_sink);


void ro_batchrefract_kill(RoBatchRefract *self);

// updates a subset of the batch into the gpu
void ro_batchrefract_update_sub(const RoBatchRefract *self, int offset, int size);

// renders a subset of the batch with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
void ro_batchrefract_render_sub(const RoBatchRefract *self, int num, const mat4 *camera_mat, float scale, 
        const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_batchrefract_set_texture_main(RoBatchRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_batchrefract_set_texture_refraction(RoBatchRefract *self, rTexture tex_refraction_sink);

// updates the natch into the gpu
static void ro_batchrefract_update(const RoBatchRefract *self) {
    ro_batchrefract_update_sub(self, 0, self->num);
}

// rensers the batch with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
static void ro_batchrefract_render(const RoBatchRefract *self, const mat4 *camera_mat, float scale, 
        const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer) {
    ro_batchrefract_render_sub(self, self->num, camera_mat, scale, 
            opt_view_aabb, opt_framebuffer);
}


#endif //R_RO_BATCHREFRACT_H
