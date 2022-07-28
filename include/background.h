#ifndef PIXELC_BACKGROUND_H
#define PIXELC_BACKGROUND_H

//
// Just the background image/pattern
//

#include "u/color.h"
#include "m/types/float.h"

void background_init(uColor_s a, uColor_s b);

void background_update(float dtime);

void background_render(const mat4 *camera_mat);

#endif //PIXELC_BACKGROUND_H
