#ifndef PIXELC_BACKGROUND_H
#define PIXELC_BACKGROUND_H

#include "u/color.h"
#include "camera.h"

typedef struct Background Background;

Background *background_new(uColor_s a, uColor_s b);

void background_update(Background *self, const Camera_s *camera, float dtime);

void background_render(Background *self, const mat4 *camera_mat);

#endif //PIXELC_BACKGROUND_H
