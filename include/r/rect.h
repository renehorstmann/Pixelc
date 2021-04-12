#ifndef R_RECT_H
#define R_RECT_H

#include <stddef.h> // offsetof
#include "mathc/types/float.h"

typedef struct {
    mat4 pose;
    mat4 uv;
    vec4 color;
} rRect_s;

typedef struct {
    mat4 pose;
    mat4 uv;
    vec4 speed;
    vec4 acc;
    vec4 axis_angle;
    vec4 color;
    vec4 color_speed;
    vec2 uv_step;
    float uv_time;
    float start_time;
} rParticleRect_s;

_Static_assert(offsetof(rParticleRect_s, uv_time)
               - offsetof(rParticleRect_s, uv_step)
               == 2 * sizeof(float),
               "uv_time must not be padded");



#endif //R_RECT_H
