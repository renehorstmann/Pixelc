#ifndef R_SINGLE_H
#define R_SINGLE_H

#include <stdbool.h>
#include "core.h"
#include "rect.h"

typedef struct {
    rRect_s rect;
    const float *vp;
    GLuint program;
    GLuint vao;
    GLuint tex;
    bool owns_tex;
} rRoSingle;

void r_ro_single_init(rRoSingle *self, const float *vp, GLuint tex_sink);

void r_ro_single_kill(rRoSingle *self);

void r_ro_single_render(rRoSingle *self);

void r_ro_single_set_texture(rRoSingle *self, GLuint tex);

#endif //R_SINGLE_H
