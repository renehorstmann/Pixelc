#ifndef R_RO_SINGLE_H
#define R_RO_SINGLE_H

//
// class to render a single rect with a draw call
//

#include "rhc/alloc.h"
#include "ro_types.h"


RoSingle ro_single_new(rTexture tex_sink);

void ro_single_kill(RoSingle *self);

void ro_single_render(RoSingle *self, const mat4 *camera_mat);

// resets the texture, if .owns_tex is true, it will delete the old texture
void ro_single_set_texture(RoSingle *self, rTexture tex_sink);


#endif //R_RO_SINGLE_H
