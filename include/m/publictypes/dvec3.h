#ifndef M_PUBLICTYPES_DVEC3_H
#define M_PUBLICTYPES_DVEC3_H

#include <assert.h>     // for static_assert


#include "dvec2.h"

typedef union {
    double v[3];
    struct {
        double v0, v1, v2;
    };
    m_dvec2 xy;
    struct {
        double x;
        union {
            struct {
                double y, z;
            };
            m_dvec2 yz;
        };
    };
    m_dvec2 rg;
    struct {
        double r;
        union {
            struct {
                double g, b;
            };
            m_dvec2 gb;
        };
    };
} m_dvec3;


static_assert(sizeof(m_dvec3) == sizeof(double) * 3, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec3 */
#define M_AS_DVEC3(vec) (*(m_dvec3 *) (vec))

#endif //M_PUBLICTYPES_DVEC3_H
