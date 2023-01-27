#ifndef M_PUBLICTYPES_IVEC3_H
#define M_PUBLICTYPES_IVEC3_H

#include <assert.h>     // for static_assert







#include "ivec2.h"
typedef union {
    int v[3];
    struct {
        int v0, v1, v2;
    };
    m_ivec2 xy;
    struct {
        int x;
        union {
            struct {
                int y, z;
            };
            m_ivec2 yz;
        };
    };
    m_ivec2 rg;
    struct {
        int r;
        union {
            struct {
                int g, b;
            };
            m_ivec2 gb;
        };
    };
} m_ivec3;






static_assert(sizeof(m_ivec3) == sizeof(int) * 3, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec3 */
#define M_AS_IVEC3(vec) (*(m_ivec3 *) (vec))

#endif //M_PUBLICTYPES_IVEC3_H
