#ifndef M_PUBLICTYPES_IVEC2_H
#define M_PUBLICTYPES_IVEC2_H

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
} m_ivec2;


static_assert(sizeof(m_ivec2) == sizeof(int) * 2, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec2 */
#define M_AS_IVEC2(vec) (*(m_ivec2 *) (vec))

#endif //M_PUBLICTYPES_IVEC2_H
