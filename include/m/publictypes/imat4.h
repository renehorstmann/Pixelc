#ifndef M_PUBLICTYPES_IMAT4_H
#define M_PUBLICTYPES_IMAT4_H

#include <assert.h>     // for static_assert


#include "ivec4.h"

typedef union {
    int v[4 * 4];
    int m[4][4];
    m_ivec4 col[4];
    struct {
        int v0, v1, v2, v3;
        int v4, v5, v6, v7;
        int v8, v9, v10, v11;
        int v12, v13, v14, v15;
    };
    struct {
        int m00, m01, m02, m03;
        int m10, m11, m12, m13;
        int m20, m21, m22, m23;
        int m30, m31, m32, m33;
    };
} m_imat4;


static_assert(sizeof(m_imat4) == sizeof(int) * 4 * 4, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat4 */
#define M_AS_IMAT4(mat) (*(m_imat4 *) (mat))

#endif //M_PUBLICTYPES_IMAT4_H
