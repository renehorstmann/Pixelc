#ifndef PIXELC_FEEDBACK_H
#define PIXELC_FEEDBACK_H

#include "s/s.h"
#include "m/types/float.h"

void feedback_init();

void feedback_update(float dtime);

void feedback_render(const mat4 *camera_mat);

void feedback_longpress(vec2 pos, vec4 color);

void feedback_flash(vec4 color, float time);

#endif //PIXELC_FEEDBACK_H
