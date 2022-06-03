#ifndef MATHC_PUBLICTYPES_VEC2_H
#define MATHC_PUBLICTYPES_VEC2_H

#include <assert.h>     // for static_assert


typedef union {
    float v[2];
    struct {
        float v0, v1;
    };
    struct {
        float x, y;
    };
    struct {
        float r, g;
    };
} mathc_vec2;


static_assert(sizeof(mathc_vec2) == sizeof(float) * 2, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec2 */
#define MATHC_AS_VEC2(vec) (*(mathc_vec2 *) (vec))

#endif //MATHC_PUBLICTYPES_VEC2_H
