#ifndef R_RO_BATCH_H
#define R_RO_BATCH_H

#include <stdbool.h>
#include "core.h"
#include "rect.h"

// Renders multiple rects with a single draw call
typedef struct {
    rRect_s *rects;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    bool owns_tex;
} RoBatch;

void ro_batch_init(RoBatch *self, int num, const float *vp, GLuint tex_sink);

void ro_batch_kill(RoBatch *self);

void ro_batch_update_sub(RoBatch *self, int offset, int size);

void ro_batch_render_sub(RoBatch *self, int num);

void ro_batch_set_texture(RoBatch *self, GLuint tex_sink);


static void ro_batch_update(RoBatch *self) {
    ro_batch_update_sub(self, 0, self->num);
}

static void ro_batch_render(RoBatch *self) {
    ro_batch_render_sub(self, self->num);
}


#endif //R_RO_BATCH_H
