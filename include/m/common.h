#ifndef M_COMMON_H
#define M_COMMON_H

//
// some macros to make life easies
//


#define m_min(a, b) ((a)<(b)?(a):(b))
#define m_max(a, b) ((a)>(b)?(a):(b))

#define m_sign(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))
#define m_clamp(x, min, max) (x) < (min) ? (min) : ((x) > (max) ? (max) : (x))
#define m_step(x, edge) (x) < (edge) ? 0 : 1;


// unpack arrays (and matrices 3x3=9, 4x4=16)
#define m_u2(x) (x).v0, (x).v1
#define m_u3(x) (x).v0, (x).v1, (x).v2
#define m_u4(x) (x).v0, (x).v1, (x).v2, (x).v3
#define m_u9(x) (x).v0, (x).v1, (x).v2, (x).v3, (x).v4, (x).v5, (x).v6, (x).v7, (x).v8
#define m_u16(x) (x).v0, (x).v1, (x).v2, (x).v3, (x).v4, (x).v5, (x).v6, (x).v7, \
(x).v8, (x).v9, (x).v10, (x).v11, (x).v12, (x).v13, (x).v14, (x).v15

#endif //M_COMMON_H
