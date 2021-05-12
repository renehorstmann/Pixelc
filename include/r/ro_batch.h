#ifndef R_RO_BATCH_H
#define R_RO_BATCH_H

//
// class to render multiple rects with a single draw call
//

#include "rhc/allocator.h"
#include "core.h"
#include "rect.h"
#include "texture.h"

typedef struct {
    rRect_s *rects;
    int num;
    const float *vp;    // mat4 camera view perspective
    bool owns_tex;      // if true, the texture will be deleted by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
        rTexture tex;       // used texture
        Allocator_s allocator;
    } L;
} RoBatch;

RoBatch ro_batch_new_a(int num, const float *vp, rTexture tex_sink, Allocator_s alloc);

static RoBatch ro_batch_new(int num, const float *vp, rTexture tex_sink) {
    return ro_batch_new_a(num, vp, tex_sink, allocator_new_default());
}


void ro_batch_kill(RoBatch *self);

// updates a subset of the batch into the gpu
void ro_batch_update_sub(RoBatch *self, int offset, int size);

// renders a subset of the batch
void ro_batch_render_sub(RoBatch *self, int num);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_batch_set_texture(RoBatch *self, rTexture tex_sink);


static void ro_batch_update(RoBatch *self) {
    ro_batch_update_sub(self, 0, self->num);
}

static void ro_batch_render(RoBatch *self) {
    ro_batch_render_sub(self, self->num);
}


#endif //R_RO_BATCH_H
