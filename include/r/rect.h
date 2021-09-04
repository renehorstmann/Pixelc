#ifndef R_RECT_H
#define R_RECT_H

//
// rect pod structs, used by some renderobjects (ro)
//

#include "types.h"

              

// creates a new rect with:
// pose = uv = eye
// color = 1
// sprite = 0
rRect_s r_rect_new();

// as new, but xy=MAX, alpha=0
rRect_s r_rect_new_hidden();

// creates a new particle rect with:
// rect = rect_new
// sprite_speed, speed, acc, color_speed = 0
// axis_angle = 0, 0, 1, 0
// start_time = 0
rParticleRect_s r_particlerect_new();

// as new, but xy=MAX, alpha=0
rParticleRect_s r_particlerect_new_hidden();


#endif //R_RECT_H
