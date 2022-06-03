#ifndef R_RO_SINGLE_H
#define R_RO_SINGLE_H

//
// class to render a single rect with a draw call
//

#include "rect.h"
#include "texture.h"

// Renders a single rect in a draw call
typedef struct {
    rRect_s rect;
    rTexture tex;       // used texture
    bool owns_tex;      // if true (default), tex will be killed by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
    } L;
} RoSingle;

// creates a single to draw one rRect
// this class takes ownership of tex_sink (see .owns_tex)
RoSingle ro_single_new(rTexture tex_sink);

void ro_single_kill(RoSingle *self);

// renders the single rRect
void ro_single_render(const RoSingle *self, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_single_set_texture(RoSingle *self, rTexture tex_sink);


#endif //R_RO_SINGLE_H
