#ifndef M_PUBLICTYPES_UCMAT3_H
#define M_PUBLICTYPES_UCMAT3_H

#include <assert.h>     // for static_assert





#include "ucvec3.h"
typedef union {
    unsigned char v[3*3];
    unsigned char m[3][3];
    m_ucvec3 col[3];
    struct {
        unsigned char v0, v1, v2;
        unsigned char v3, v4, v5;
        unsigned char v6, v7, v8;
    };
    struct {
        unsigned char m00, m01, m02;
        unsigned char m10, m11, m12;
        unsigned char m20, m21, m22;
    };
} m_ucmat3;






static_assert(sizeof(m_ucmat3) == sizeof(unsigned char) * 3 * 3, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat3 */
#define M_AS_UCMAT3(mat) (*(m_ucmat3 *) (mat))

#endif //M_PUBLICTYPES_UCMAT3_H
