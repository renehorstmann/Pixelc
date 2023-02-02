#ifndef R_RO_BATCH_H
#define R_RO_BATCH_H

//
// class to render multiple rects with a single draw call
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
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
    } L;
} RoBatch;

// returns true if the batch seems to be in a valid state, GL errors ignored
static bool ro_batch_valid(const RoBatch *self) {
    return self->rects!=NULL && self->num;
}

// returns a new invalid batch
static RoBatch ro_batch_new_invalid() {
    return (RoBatch) {0};
}

// creates a new batch with num rRect's
// this class takes ownership of tex_sink (see .owns_tex)
// returns an invalid, for num<=0
RoBatch ro_batch_new(int num, rTexture tex_sink);

void ro_batch_kill(RoBatch *self);

// updates a subset of the batch into the gpu
void ro_batch_update_sub(const RoBatch *self, int offset, int size);

// renders a subset of the batch
// if update is true, update is called before rendering
void ro_batch_render_sub(const RoBatch *self, int num, const mat4 *camera_mat, bool update_sub);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_batch_set_texture(RoBatch *self, rTexture tex_sink);

// updates the batch into the gpu
static void ro_batch_update(const RoBatch *self) {
    ro_batch_update_sub(self, 0, self->num);
}

// renders the batch
// if update is true, update is called before rendering
static void ro_batch_render(const RoBatch *self, const mat4 *camera_mat, bool update) {
    ro_batch_render_sub(self, self->num, camera_mat, update);
}


#endif //R_RO_BATCH_H
