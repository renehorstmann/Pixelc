#ifndef M_PUBLICTYPES_IVEC4_H
#define M_PUBLICTYPES_IVEC4_H

#include <assert.h>     // for static_assert









#include "ivec2.h"
#include "ivec3.h"
typedef union {
    int v[4];
    struct {
        int v0, v1, v2, v3;
    };
    m_ivec2 xy;
    m_ivec3 xyz;
    struct {
        int x;
        union {
            struct {
                int y;
                union {
                    struct {
                        int z, w;
                    };
                    m_ivec2 zw;
                };
            };
            m_ivec2 yz;
            m_ivec3 yzw;
        };
    };
    m_ivec2 rg;
    m_ivec3 rgb;
    struct {
        int r;
        union {
            struct {
                int g;
                union {
                    struct {
                        int b, a;
                    };
                    m_ivec2 ba;
                };
            };
            m_ivec2 gb;
            m_ivec3 gba;
        };
    };
} m_ivec4;




static_assert(sizeof(m_ivec4) == sizeof(int) * 4, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec4 */
#define M_AS_IVEC4(vec) (*(m_ivec4 *) (vec))

#endif //M_PUBLICTYPES_IVEC4_H
