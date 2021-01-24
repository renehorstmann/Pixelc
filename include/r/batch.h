#ifndef R_BATCH_H
#define R_BATCH_H

#include <stdbool.h>
#include "core.h"
#include "rect.h"


typedef struct rBatch {
    rRect_s *rects;
    int num;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    bool owns_tex;
} rBatch;

void r_batch_init(rBatch *self, int num, const float *vp, GLuint tex_sink);

void r_batch_kill(rBatch *self);

void r_batch_update(rBatch *self, int offset, int size);

void r_batch_render(rBatch *self);

void r_batch_set_texture(rBatch *self, GLuint tex);

#endif //R_BATCH_H
