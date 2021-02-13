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
} rRoBatch;

void r_ro_batch_init(rRoBatch *self, int num, const float *vp, GLuint tex_sink);

void r_ro_batch_kill(rRoBatch *self);

void r_ro_batch_update_sub(rRoBatch *self, int offset, int size);

void r_ro_batch_render_sub(rRoBatch *self, int num);

void r_ro_batch_set_texture(rRoBatch *self, GLuint tex_sink);


static void r_ro_batch_update(rRoBatch *self) {
	r_ro_batch_update_sub(self, 0, self->num);
}
static void r_ro_batch_render(rRoBatch *self) {
	r_ro_batch_render_sub(self, self->num);
}


#endif //R_RO_BATCH_H
