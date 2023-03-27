#ifndef M_PUBLICTYPES_UCVEC4_H
#define M_PUBLICTYPES_UCVEC4_H

#include <assert.h>     // for static_assert


#include "ucvec2.h"
#include "ucvec3.h"

typedef union {
    unsigned char v[4];
    struct {
        unsigned char v0, v1, v2, v3;
    };
    m_ucvec2 xy;
    m_ucvec3 xyz;
    struct {
        unsigned char x;
        union {
            struct {
                unsigned char y;
                union {
                    struct {
                        unsigned char z, w;
                    };
                    m_ucvec2 zw;
                };
            };
            m_ucvec2 yz;
            m_ucvec3 yzw;
        };
    };
    m_ucvec2 rg;
    m_ucvec3 rgb;
    struct {
        unsigned char r;
        union {
            struct {
                unsigned char g;
                union {
                    struct {
                        unsigned char b, a;
                    };
                    m_ucvec2 ba;
                };
            };
            m_ucvec2 gb;
            m_ucvec3 gba;
        };
    };
} m_ucvec4;


static_assert(sizeof(m_ucvec4) == sizeof(unsigned char) * 4, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec4 */
#define M_AS_UCVEC4(vec) (*(m_ucvec4 *) (vec))

#endif //M_PUBLICTYPES_UCVEC4_H
