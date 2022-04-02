#ifndef MATHC_PUBLICTYPES_DVEC4_H
#define MATHC_PUBLICTYPES_DVEC4_H

#include <assert.h>     // for static_assert









#include "dvec2.h"
#include "dvec3.h"
typedef union {
    double v[4];
    struct {
        double v0, v1, v2, v3;
    };
    mathc_dvec2 xy;
    mathc_dvec3 xyz;
    struct {
        double x;
        union {
            struct {
                double y;
                union {
                    struct {
                        double z, w;
                    };
                    mathc_dvec2 zw;
                };
            };
            mathc_dvec2 yz;
            mathc_dvec3 yzw;
        };
    };
    mathc_dvec2 rg;
    mathc_dvec3 rgb;
    struct {
        double r;
        union {
            struct {
                double g;
                union {
                    struct {
                        double b, a;
                    };
                    mathc_dvec2 ba;
                };
            };
            mathc_dvec2 gb;
            mathc_dvec3 gba;
        };
    };
} mathc_dvec4;




static_assert(sizeof(mathc_dvec4) == sizeof(double) * 4, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec4 */
#define MATHC_AS_DVEC4(vec) (*(mathc_dvec4 *) (vec))

#endif //MATHC_PUBLICTYPES_DVEC4_H
