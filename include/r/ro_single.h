#ifndef R_RO_SINGLE_H
#define R_RO_SINGLE_H

//
// class to render a single rect with a draw call
//

#include "rhc/alloc.h"
#include "ro_types.h"

// creates a single to draw one rRect
// this class takes ownership of tex_sink (see .owns_tex)
RoSingle ro_single_new(rTexture tex_sink);

void ro_single_kill(RoSingle *self);

// renders the single rRect
void ro_single_render(const RoSingle *self, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_single_set_texture(RoSingle *self, rTexture tex_sink);


#endif //R_RO_SINGLE_H
