#ifndef M_PUBLICTYPES_UCMAT2_H
#define M_PUBLICTYPES_UCMAT2_H

#include <assert.h>     // for static_assert


#include "ucvec2.h"

typedef union {
    unsigned char v[2 * 2];
    unsigned char m[2][2];
    m_ucvec2 col[2];
    struct {
        unsigned char v0, v1;
        unsigned char v2, v3;
    };
    struct {
        unsigned char m00, m01;
        unsigned char m10, m11;
    };
} m_ucmat2;


static_assert(sizeof(m_ucmat2) == sizeof(unsigned char) * 2 * 2, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat2 */
#define M_AS_UCMAT2(mat) (*(m_ucmat2 *) (mat))

#endif //M_PUBLICTYPES_UCMAT2_H
