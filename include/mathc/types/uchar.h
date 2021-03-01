#ifndef MATHC_TYPES_UCHAR_H
#define MATHC_TYPES_UCHAR_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef unsigned char uchar;

typedef union {
    uchar v[2];
    struct {
        uchar v0, v1;
    };
    struct {
        uchar x, y;
    };
    struct {
        uchar r, g;
    };
} ucvec2;
static_assert(sizeof(ucvec2) == sizeof(uchar) * 2, "[Mathc] wrong expected size");

/** casts a uchar * to a dereferenced ucvec2 */
#define UCVec2(vec) (*(ucvec2 *) (vec))

/** casts a uchar * to a dereferenced const ucvec2 */
#define ConstUCVec2(vec) (*(const ucvec2 *) (vec))


typedef union {
    uchar v[4];
    uchar m[2][2];
    ucvec2 col[2];
    struct {
        uchar v0, v1;
        uchar v2, v3;
    };
    struct {
        uchar m00, m01;
        uchar m10, m11;
    };
} ucmat2;
static_assert(sizeof(ucmat2) == sizeof(uchar) * 4, "[Mathc] wrong expected size");

/** casts a uchar * to a dereferenced ucmat2 */
#define UCMat2(mat) (*(ucmat2 *) (mat))

/** casts a uchar * to a dereferenced const ucmat2 */
#define ConstUCMat2(mat) (*(const ucmat2 *) (mat))

typedef union {
    uchar v[3];
    struct {
        uchar v0, v1, v2;
    };
    ucvec2 xy;
    struct {
        uchar x;
        union {
            struct {
                uchar y, z;
            };
            ucvec2 yz;
        };
    };
    ucvec2 rg;
    struct {
        uchar r;
        union {
            struct {
                uchar g, b;
            };
            ucvec2 gb;
        };
    };
} ucvec3;
static_assert(sizeof(ucvec3) == sizeof(uchar) * 3, "[Mathc] wrong expected size");

/** casts a uchar * to a dereferenced ucvec3 */
#define UCVec3(vec) (*(ucvec3 *) (vec))

/** casts a uchar * to a dereferenced const ucvec3 */
#define ConstUCVec3(vec) (*(const ucvec3 *) (vec))


typedef union {
    uchar v[9];
    uchar m[3][3];
    ucvec3 col[3];
    struct {
        uchar v0, v1, v2;
        uchar v3, v4, v5;
        uchar v6, v7, v8;
    };
    struct {
        uchar m00, m01, m02;
        uchar m10, m11, m12;
        uchar m20, m21, m22;
    };
} ucmat3;
static_assert(sizeof(ucmat3) == sizeof(uchar) * 9, "[Mathc] wrong expected size");

/** casts a uchar * to a dereferenced ucmat3 */
#define UCMat3(mat) (*(ucmat3 *) (mat))

/** casts a uchar * to a dereferenced const ucmat3 */
#define ConstUCMat3(mat) (*(const ucmat3 *) (mat))


typedef union {
    uchar v[4];
    struct {
        uchar v0, v1, v2, v3;
    };
    ucvec2 xy;
    ucvec3 xyz;
    struct {
        uchar x;
        union {
            struct {
                uchar y;
                union {
                    struct {
                        uchar z, w;
                    };
                    ucvec2 zw;
                };
            };
            ucvec2 yz;
            ucvec3 yzw;
        };
    };
    ucvec2 rg;
    ucvec3 rgb;
    struct {
        uchar r;
        union {
            struct {
                uchar g;
                union {
                    struct {
                        uchar b, a;
                    };
                    ucvec2 ba;
                };
            };
            ucvec2 gb;
            ucvec3 gba;
        };
    };
} ucvec4;
static_assert(sizeof(ucvec4) == sizeof(uchar) * 4, "[Mathc] wrong expected size");

/** casts a uchar * to a dereferenced ucvec4 */
#define UCVec4(vec) (*(ucvec4 *) (vec))

/** casts a uchar * to a dereferenced const ucvec4 */
#define ConstUCVec4(vec) (*(const ucvec4 *) (vec))


typedef union {
    uchar v[16];
    uchar m[4][4];
    ucvec4 col[4];
    struct {
        uchar v0, v1, v2, v3;
        uchar v4, v5, v6, v7;
        uchar v8, v9, v10, v11;
        uchar v12, v13, v14, v15;
    };
    struct {
        uchar m00, m01, m02, m03;
        uchar m10, m11, m12, m13;
        uchar m20, m21, m22, m23;
        uchar m30, m31, m32, m33;
    };
} ucmat4;
static_assert(sizeof(ucmat4) == sizeof(uchar) * 16, "[Mathc] wrong expected size");

/** casts a uchar * to a dereferenced ucmat4 */
#define UCMat4(mat) (*(ucmat4 *) (mat))

/** casts a uchar * to a dereferenced const ucmat4 */
#define ConstUCMat4(mat) (*(const ucmat4 *) (mat))


#endif //MATHC_TYPES_UCHAR_H
