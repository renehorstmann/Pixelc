#ifndef M_PUBLICTYPES_VEC3_H
#define M_PUBLICTYPES_VEC3_H

#include <assert.h>     // for static_assert


#include "vec2.h"

typedef union {
    float v[3];
    struct {
        float v0, v1, v2;
    };
    m_vec2 xy;
    struct {
        float x;
        union {
            struct {
                float y, z;
            };
            m_vec2 yz;
        };
    };
    m_vec2 rg;
    struct {
        float r;
        union {
            struct {
                float g, b;
            };
            m_vec2 gb;
        };
    };
} m_vec3;


static_assert(sizeof(m_vec3) == sizeof(float) * 3, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec3 */
#define M_AS_VEC3(vec) (*(m_vec3 *) (vec))

#endif //M_PUBLICTYPES_VEC3_H
