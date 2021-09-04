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

#include "rhc/allocator.h"
#include "ro_types.h"


RoBatchRefract ro_batchrefract_new_a(int num,
                                     const float *scale_ptr,
                                     rTexture tex_main_sink, rTexture tex_refraction_sink,
                                     Allocator_s alloc);

static RoBatchRefract ro_batchrefract_new(int num,
                                          const float *scale_ptr,
                                          rTexture tex_main_sink, rTexture tex_refraction_sink) {
    return ro_batchrefract_new_a(num, scale_ptr, tex_main_sink, tex_refraction_sink,
                                 allocator_new_default()
    );
}


void ro_batchrefract_kill(RoBatchRefract *self);

// updates a subset of the batch into the gpu
void ro_batchrefract_update_sub(RoBatchRefract *self, int offset, int size);

// renders a subset of the batch
void ro_batchrefract_render_sub(RoBatchRefract *self, int num, const mat4 *camera_mat);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_batchrefract_set_texture_main(RoBatchRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_batchrefract_set_texture_refraction(RoBatchRefract *self, rTexture tex_refraction_sink);


static void ro_batchrefract_update(RoBatchRefract *self) {
    ro_batchrefract_update_sub(self, 0, self->num);
}

static void ro_batchrefract_render(RoBatchRefract *self, const mat4 *camera_mat) {
    ro_batchrefract_render_sub(self, self->num, camera_mat);
}


#endif //R_RO_BATCHREFRACT_H
