#ifndef M_PUBLICTYPES_UCVEC2_H
#define M_PUBLICTYPES_UCVEC2_H

#include <assert.h>     // for static_assert


typedef union {
    unsigned char v[2];
    struct {
        unsigned char v0, v1;
    };
    struct {
        unsigned char x, y;
    };
    struct {
        unsigned char r, g;
    };
} m_ucvec2;


static_assert(sizeof(m_ucvec2) == sizeof(unsigned char) * 2, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec2 */
#define M_AS_UCVEC2(vec) (*(m_ucvec2 *) (vec))

#endif //M_PUBLICTYPES_UCVEC2_H
