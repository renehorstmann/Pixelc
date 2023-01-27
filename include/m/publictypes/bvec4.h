#ifndef M_PUBLICTYPES_BVEC4_H
#define M_PUBLICTYPES_BVEC4_H

#include <assert.h>     // for static_assert


#include <stdbool.h>







#include "bvec2.h"
#include "bvec3.h"
typedef union {
    bool v[4];
    struct {
        bool v0, v1, v2, v3;
    };
    m_bvec2 xy;
    m_bvec3 xyz;
    struct {
        bool x;
        union {
            struct {
                bool y;
                union {
                    struct {
                        bool z, w;
                    };
                    m_bvec2 zw;
                };
            };
            m_bvec2 yz;
            m_bvec3 yzw;
        };
    };
    m_bvec2 rg;
    m_bvec3 rgb;
    struct {
        bool r;
        union {
            struct {
                bool g;
                union {
                    struct {
                        bool b, a;
                    };
                    m_bvec2 ba;
                };
            };
            m_bvec2 gb;
            m_bvec3 gba;
        };
    };
} m_bvec4;




static_assert(sizeof(m_bvec4) == sizeof(bool) * 4, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec4 */
#define M_AS_BVEC4(vec) (*(m_bvec4 *) (vec))

#endif //M_PUBLICTYPES_BVEC4_H
