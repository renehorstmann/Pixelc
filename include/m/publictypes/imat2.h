#ifndef M_PUBLICTYPES_IMAT2_H
#define M_PUBLICTYPES_IMAT2_H

#include <assert.h>     // for static_assert


#include "ivec2.h"

typedef union {
    int v[2 * 2];
    int m[2][2];
    m_ivec2 col[2];
    struct {
        int v0, v1;
        int v2, v3;
    };
    struct {
        int m00, m01;
        int m10, m11;
    };
} m_imat2;


static_assert(sizeof(m_imat2) == sizeof(int) * 2 * 2, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat2 */
#define M_AS_IMAT2(mat) (*(m_imat2 *) (mat))

#endif //M_PUBLICTYPES_IMAT2_H
