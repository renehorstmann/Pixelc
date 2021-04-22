#ifndef R_RO_SINGLE_H
#define R_RO_SINGLE_H

//
// class to render a single rect with a draw call
//

#include <stdbool.h>
#include "core.h"
#include "rect.h"
#include "texture.h"

// Renders a single rect in a draw call
typedef struct {
    rRect_s rect;
    const float *vp;    // mat4 camera view perspective
    GLuint program;     // shader
    GLuint vao;         // internal vertex array object
    rTexture tex;       // used texture
    bool owns_tex;      // if true, the texture will be deleted by this class
} RoSingle;

RoSingle ro_single_new(const float *vp, rTexture tex_sink);

void ro_single_kill(RoSingle *self);

void ro_single_render(RoSingle *self);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_single_set_texture(RoSingle *self, rTexture tex_sink);


#endif //R_RO_SINGLE_H
