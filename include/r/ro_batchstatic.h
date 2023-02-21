#ifndef R_RO_BATCHSTATIC_H
#define R_RO_BATCHSTATIC_H

//
// class to render multiple rects with a single draw call
// renders much faster than the default RoBatch, but the update call is more heavy
// so good to use it for large static batches, like tilemaps
//
#include "rect.h"
#include "texture.h"



// Renders multiple rects in a draw call
typedef struct {
    rRect_s *rects;
    int num;
    rTexture tex;       // used texture
    bool owns_tex;      // if true (default), text will be killed by this class

    struct {
        struct rRectStatic_s *srects;
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
    } L;
} RoBatchStatic;

// returns true if the batch seems to be in a valid state, GL errors ignored
static bool ro_batchstatic_valid(const RoBatchStatic *self) {
    return self->rects!=NULL && self->num;
}

// returns a new invalid batch
static RoBatchStatic ro_batchstatic_new_invalid() {
    return (RoBatchStatic) {0};
}

// creates a new batch with num rRect's
// this class takes ownership of tex_sink (see .owns_tex)
// returns an invalid, for num<=0
RoBatchStatic ro_batchstatic_new(int num, rTexture tex_sink);

void ro_batchstatic_kill(RoBatchStatic *self);

// updates a subset of the batch into the gpu
void ro_batchstatic_update_sub(const RoBatchStatic *self, int offset, int size);

// renders a subset of the batch
// if update is true, update is called before rendering
void ro_batchstatic_render_sub(const RoBatchStatic *self, int num, const mat4 *camera_mat, bool update_sub);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_batchstatic_set_texture(RoBatchStatic *self, rTexture tex_sink);

// updates the batch into the gpu
static void ro_batchstatic_update(const RoBatchStatic *self) {
    ro_batchstatic_update_sub(self, 0, self->num);
}

// renders the batch
// if update is true, update is called before rendering
static void ro_batchstatic_render(const RoBatchStatic *self, const mat4 *camera_mat, bool update) {
    ro_batchstatic_render_sub(self, self->num, camera_mat, update);
}


#endif //R_RO_BATCHSTATIC_H
