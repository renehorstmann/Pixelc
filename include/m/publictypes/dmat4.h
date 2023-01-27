#ifndef M_PUBLICTYPES_DMAT4_H
#define M_PUBLICTYPES_DMAT4_H

#include <assert.h>     // for static_assert







#include "dvec4.h"
typedef union {
    double v[4*4];
    double m[4][4];
    m_dvec4 col[4];
    struct {
        double v0, v1, v2, v3;
        double v4, v5, v6, v7;
        double v8, v9, v10, v11;
        double v12, v13, v14, v15;
    };
    struct {
        double m00, m01, m02, m03;
        double m10, m11, m12, m13;
        double m20, m21, m22, m23;
        double m30, m31, m32, m33;
    };
} m_dmat4;




static_assert(sizeof(m_dmat4) == sizeof(double) * 4 * 4, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dmat4 */
#define M_AS_DMAT4(mat) (*(m_dmat4 *) (mat))

#endif //M_PUBLICTYPES_DMAT4_H
