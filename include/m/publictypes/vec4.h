#ifndef M_PUBLICTYPES_VEC4_H
#define M_PUBLICTYPES_VEC4_H

#include <assert.h>     // for static_assert


#include "vec2.h"
#include "vec3.h"

typedef union {
    float v[4];
    struct {
        float v0, v1, v2, v3;
    };
    m_vec2 xy;
    m_vec3 xyz;
    struct {
        float x;
        union {
            struct {
                float y;
                union {
                    struct {
                        float z, w;
                    };
                    m_vec2 zw;
                };
            };
            m_vec2 yz;
            m_vec3 yzw;
        };
    };
    m_vec2 rg;
    m_vec3 rgb;
    struct {
        float r;
        union {
            struct {
                float g;
                union {
                    struct {
                        float b, a;
                    };
                    m_vec2 ba;
                };
            };
            m_vec2 gb;
            m_vec3 gba;
        };
    };
} m_vec4;


static_assert(sizeof(m_vec4) == sizeof(float) * 4, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec4 */
#define M_AS_VEC4(vec) (*(m_vec4 *) (vec))

#endif //M_PUBLICTYPES_VEC4_H
