#ifndef M_PUBLICTYPES_MAT4_H
#define M_PUBLICTYPES_MAT4_H

#include <assert.h>     // for static_assert







#include "vec4.h"
typedef union {
    float v[4*4];
    float m[4][4];
    m_vec4 col[4];
    struct {
        float v0, v1, v2, v3;
        float v4, v5, v6, v7;
        float v8, v9, v10, v11;
        float v12, v13, v14, v15;
    };
    struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
} m_mat4;




static_assert(sizeof(m_mat4) == sizeof(float) * 4 * 4, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced mat4 */
#define M_AS_MAT4(mat) (*(m_mat4 *) (mat))

#endif //M_PUBLICTYPES_MAT4_H
