#ifndef M_PUBLICTYPES_DVEC4_H
#define M_PUBLICTYPES_DVEC4_H

#include <assert.h>     // for static_assert









#include "dvec2.h"
#include "dvec3.h"
typedef union {
    double v[4];
    struct {
        double v0, v1, v2, v3;
    };
    m_dvec2 xy;
    m_dvec3 xyz;
    struct {
        double x;
        union {
            struct {
                double y;
                union {
                    struct {
                        double z, w;
                    };
                    m_dvec2 zw;
                };
            };
            m_dvec2 yz;
            m_dvec3 yzw;
        };
    };
    m_dvec2 rg;
    m_dvec3 rgb;
    struct {
        double r;
        union {
            struct {
                double g;
                union {
                    struct {
                        double b, a;
                    };
                    m_dvec2 ba;
                };
            };
            m_dvec2 gb;
            m_dvec3 gba;
        };
    };
} m_dvec4;




static_assert(sizeof(m_dvec4) == sizeof(double) * 4, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec4 */
#define M_AS_DVEC4(vec) (*(m_dvec4 *) (vec))

#endif //M_PUBLICTYPES_DVEC4_H
