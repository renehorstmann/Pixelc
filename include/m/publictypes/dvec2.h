#ifndef M_PUBLICTYPES_DVEC2_H
#define M_PUBLICTYPES_DVEC2_H

#include <assert.h>     // for static_assert





typedef union {
    double v[2];
    struct {
        double v0, v1;
    };
    struct {
        double x, y;
    };
    struct {
        double r, g;
    };
} m_dvec2;








static_assert(sizeof(m_dvec2) == sizeof(double) * 2, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec2 */
#define M_AS_DVEC2(vec) (*(m_dvec2 *) (vec))

#endif //M_PUBLICTYPES_DVEC2_H
