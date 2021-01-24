#ifndef MATHC_INITIALIZER_H
#define MATHC_INITIALIZER_H

// initializer

#define VEC2_INIT_ZERO   {{0, 0}}
#define VEC2_INIT_ONE    {{1, 1}}
#define VEC2_INIT_UNIT_X {{1, 0}}
#define VEC2_INIT_UNIT_Y {{0, 1}}

#define VEC3_INIT_ZERO   {{0, 0, 0}}
#define VEC3_INIT_ONE    {{1, 1, 1}}
#define VEC3_INIT_UNIT_X {{1, 0, 0}}
#define VEC3_INIT_UNIT_Y {{0, 1, 0}}
#define VEC3_INIT_UNIT_Z {{0, 0, 1}}

#define VEC4_INIT_ZERO   {{0, 0, 0, 0}}
#define VEC4_INIT_ONE    {{1, 1, 1, 1}}
#define VEC4_INIT_UNIT_X {{1, 0, 0, 0}}
#define VEC4_INIT_UNIT_Y {{0, 1, 0, 0}}
#define VEC4_INIT_UNIT_Z {{0, 0, 1, 0}}
#define VEC4_INIT_UNIT_W {{0, 0, 0, 1}}

#define MAT2_INIT_ZERO   {{0, 0,  0, 0}}
#define MAT2_INIT_ONE    {{1, 1,  1, 1}}
#define MAT2_INIT_EYE    {{1, 0,  0, 1}}

#define MAT3_INIT_ZERO   {{0, 0, 0,  0, 0, 0,  0, 0, 0}}
#define MAT3_INIT_ONE    {{1, 1, 1,  1, 1, 1,  1, 1, 1}}
#define MAT3_INIT_EYE    {{1, 0, 0,  0, 1, 0,  0, 0, 1}}

#define MAT4_INIT_ZERO   {{0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}}
#define MAT4_INIT_ONE    {{1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1}}
#define MAT4_INIT_EYE    {{1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}}

// xyzw
#define QUAT4_INIT_EYE {{0, 0, 0, 1}}

#endif //MATHC_INITIALIZER_H
