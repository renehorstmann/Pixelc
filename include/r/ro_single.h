#ifndef R_RO_SINGLE_H
#define R_RO_SINGLE_H

#include <stdbool.h>
#include "core.h"
#include "rect.h"

// Renders a single rect in a draw call
typedef struct {
    rRect_s rect;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint tex;
    bool owns_tex;
} RoSingle;

void ro_single_init(RoSingle *self, const float *vp, GLuint tex_sink);

void ro_single_kill(RoSingle *self);

void ro_single_render(RoSingle *self);

void ro_single_set_texture(RoSingle *self, GLuint tex_sink);


#endif //R_RO_SINGLE_H
