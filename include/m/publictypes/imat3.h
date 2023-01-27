#ifndef M_PUBLICTYPES_IMAT3_H
#define M_PUBLICTYPES_IMAT3_H

#include <assert.h>     // for static_assert





#include "ivec3.h"
typedef union {
    int v[3*3];
    int m[3][3];
    m_ivec3 col[3];
    struct {
        int v0, v1, v2;
        int v3, v4, v5;
        int v6, v7, v8;
    };
    struct {
        int m00, m01, m02;
        int m10, m11, m12;
        int m20, m21, m22;
    };
} m_imat3;






static_assert(sizeof(m_imat3) == sizeof(int) * 3 * 3, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat3 */
#define M_AS_IMAT3(mat) (*(m_imat3 *) (mat))

#endif //M_PUBLICTYPES_IMAT3_H
