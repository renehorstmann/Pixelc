#ifndef MATHC_PUBLICTYPES_VEC4_H
#define MATHC_PUBLICTYPES_VEC4_H

#include <assert.h>     // for static_assert


#include "vec2.h"
#include "vec3.h"

typedef union {
    float v[4];
    struct {
        float v0, v1, v2, v3;
    };
    mathc_vec2 xy;
    mathc_vec3 xyz;
    struct {
        float x;
        union {
            struct {
                float y;
                union {
                    struct {
                        float z, w;
                    };
                    mathc_vec2 zw;
                };
            };
            mathc_vec2 yz;
            mathc_vec3 yzw;
        };
    };
    mathc_vec2 rg;
    mathc_vec3 rgb;
    struct {
        float r;
        union {
            struct {
                float g;
                union {
                    struct {
                        float b, a;
                    };
                    mathc_vec2 ba;
                };
            };
            mathc_vec2 gb;
            mathc_vec3 gba;
        };
    };
} mathc_vec4;


static_assert(sizeof(mathc_vec4) == sizeof(float) * 4, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec4 */
#define MATHC_AS_VEC4(vec) (*(mathc_vec4 *) (vec))

#endif //MATHC_PUBLICTYPES_VEC4_H
