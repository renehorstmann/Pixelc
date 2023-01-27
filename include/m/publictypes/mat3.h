#ifndef M_PUBLICTYPES_MAT3_H
#define M_PUBLICTYPES_MAT3_H

#include <assert.h>     // for static_assert





#include "vec3.h"
typedef union {
    float v[3*3];
    float m[3][3];
    m_vec3 col[3];
    struct {
        float v0, v1, v2;
        float v3, v4, v5;
        float v6, v7, v8;
    };
    struct {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
} m_mat3;






static_assert(sizeof(m_mat3) == sizeof(float) * 3 * 3, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced mat3 */
#define M_AS_MAT3(mat) (*(m_mat3 *) (mat))

#endif //M_PUBLICTYPES_MAT3_H
