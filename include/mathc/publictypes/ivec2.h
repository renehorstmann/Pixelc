#ifndef MATHC_PUBLICTYPES_IVEC2_H
#define MATHC_PUBLICTYPES_IVEC2_H

#include <assert.h>     // for static_assert





typedef union {
    int v[2];
    struct {
        int v0, v1;
    };
    struct {
        int x, y;
    };
    struct {
        int r, g;
    };
} mathc_ivec2;








static_assert(sizeof(mathc_ivec2) == sizeof(int) * 2, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec2 */
#define MATHC_AS_IVEC2(vec) (*(mathc_ivec2 *) (vec))

#endif //MATHC_PUBLICTYPES_IVEC2_H
