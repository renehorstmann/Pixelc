#ifndef R_RO_BATCH_H
#define R_RO_BATCH_H

//
// class to render multiple rects with a single draw call
//

#include "rhc/alloc.h"
#include "ro_types.h"

RoBatch ro_batch_new_a(int num, rTexture tex_sink, Allocator_s alloc);

static RoBatch ro_batch_new(int num, rTexture tex_sink) {
    return ro_batch_new_a(num, tex_sink, rhc_allocator_new());
}


void ro_batch_kill(RoBatch *self);

// updates a subset of the batch into the gpu
void ro_batch_update_sub(RoBatch *self, int offset, int size);

// renders a subset of the batch
void ro_batch_render_sub(RoBatch *self, int num, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_batch_set_texture(RoBatch *self, rTexture tex_sink);


static void ro_batch_update(RoBatch *self) {
    ro_batch_update_sub(self, 0, self->num);
}

static void ro_batch_render(RoBatch *self, const mat4 *camera_mat) {
    ro_batch_render_sub(self, self->num, camera_mat);
}


#endif //R_RO_BATCH_H
