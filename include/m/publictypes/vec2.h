#ifndef M_PUBLICTYPES_VEC2_H
#define M_PUBLICTYPES_VEC2_H

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
} m_vec2;


static_assert(sizeof(m_vec2) == sizeof(float) * 2, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec2 */
#define M_AS_VEC2(vec) (*(m_vec2 *) (vec))

#endif //M_PUBLICTYPES_VEC2_H
