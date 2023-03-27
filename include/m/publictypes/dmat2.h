#ifndef M_PUBLICTYPES_DMAT2_H
#define M_PUBLICTYPES_DMAT2_H

#include <assert.h>     // for static_assert


#include "dvec2.h"

typedef union {
    double v[2 * 2];
    double m[2][2];
    m_dvec2 col[2];
    struct {
        double v0, v1;
        double v2, v3;
    };
    struct {
        double m00, m01;
        double m10, m11;
    };
} m_dmat2;


static_assert(sizeof(m_dmat2) == sizeof(double) * 2 * 2, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dmat2 */
#define M_AS_DMAT2(mat) (*(m_dmat2 *) (mat))

#endif //M_PUBLICTYPES_DMAT2_H
