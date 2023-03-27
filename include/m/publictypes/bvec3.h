#ifndef M_PUBLICTYPES_BVEC3_H
#define M_PUBLICTYPES_BVEC3_H

#include <assert.h>     // for static_assert


#include <stdbool.h>


#include "bvec2.h"

typedef union {
    bool v[3];
    struct {
        bool v0, v1, v2;
    };
    m_bvec2 xy;
    struct {
        bool x;
        union {
            struct {
                bool y, z;
            };
            m_bvec2 yz;
        };
    };
    m_bvec2 rg;
    struct {
        bool r;
        union {
            struct {
                bool g, b;
            };
            m_bvec2 gb;
        };
    };
} m_bvec3;


static_assert(sizeof(m_bvec3) == sizeof(bool) * 3, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec3 */
#define M_AS_BVEC3(vec) (*(m_bvec3 *) (vec))

#endif //M_PUBLICTYPES_BVEC3_H
