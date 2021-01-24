#ifndef R_SINGLE_H
#define R_SINGLE_H

#include <stdbool.h>
#include "core.h"
#include "rect.h"

typedef struct rSingle {
    rRect_s rect;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint tex;
    bool owns_tex;
} rSingle;

void r_single_init(rSingle *self, const float *vp, GLuint tex_sink);

void r_single_kill(rSingle *self);

void r_single_render(rSingle *self);

void r_single_set_texture(rSingle *self, GLuint tex);

#endif //R_SINGLE_H
