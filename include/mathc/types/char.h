#ifndef MATHC_TYPES_CHAR_H
#define MATHC_TYPES_CHAR_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef union {
    char v[2];
    struct {
        char v0, v1;
    };
    struct {
        char x, y;
    };
    struct {
        char r, g;
    };
} cvec2;
static_assert(sizeof(cvec2) == sizeof(char) * 2, "[Mathc] wrong expected size");

/** casts a char * to a dereferenced cvec2 */
#define CVec2(vec) (*(cvec2 *) (vec))

/** casts a char * to a dereferenced const cvec2 */
#define ConstCVec2(vec) (*(const cvec2 *) (vec))


typedef union {
    char v[4];
    char m[2][2];
    cvec2 col[2];
    struct {
        char v0, v1;
        char v2, v3;
    };
    struct {
        char m00, m01;
        char m10, m11;
    };
} cmat2;
static_assert(sizeof(cmat2) == sizeof(char) * 4, "[Mathc] wrong expected size");

/** casts a char * to a dereferenced cmat2 */
#define CMat2(mat) (*(cmat2 *) (mat))

/** casts a char * to a dereferenced const cmat2 */
#define ConstCMat2(mat) (*(const cmat2 *) (mat))

typedef union {
    char v[3];
    struct {
        char v0, v1, v2;
    };
    cvec2 xy;
    struct {
        char x;
        union {
            struct {
                char y, z;
            };
            cvec2 yz;
        };
    };
    cvec2 rg;
    struct {
        char r;
        union {
            struct {
                char g, b;
            };
            cvec2 gb;
        };
    };
} cvec3;
static_assert(sizeof(cvec3) == sizeof(char) * 3, "[Mathc] wrong expected size");

/** casts a char * to a dereferenced cvec3 */
#define CVec3(vec) (*(cvec3 *) (vec))

/** casts a char * to a dereferenced const cvec3 */
#define ConstCVec3(vec) (*(const cvec3 *) (vec))


typedef union {
    char v[9];
    char m[3][3];
    cvec3 col[3];
    struct {
        char v0, v1, v2;
        char v3, v4, v5;
        char v6, v7, v8;
    };
    struct {
        char m00, m01, m02;
        char m10, m11, m12;
        char m20, m21, m22;
    };
} cmat3;
static_assert(sizeof(cmat3) == sizeof(char) * 9, "[Mathc] wrong expected size");

/** casts a char * to a dereferenced cmat3 */
#define CMat3(mat) (*(cmat3 *) (mat))

/** casts a char * to a dereferenced const cmat3 */
#define ConstCMat3(mat) (*(const cmat3 *) (mat))


typedef union {
    char v[4];
    struct {
        char v0, v1, v2, v3;
    };
    cvec2 xy;
    cvec3 xyz;
    struct {
        char x;
        union {
            struct {
                char y;
                union {
                    struct {
                        char z, w;
                    };
                    cvec2 zw;
                };
            };
            cvec2 yz;
            cvec3 yzw;
        };
    };
    cvec2 rg;
    cvec3 rgb;
    struct {
        char r;
        union {
            struct {
                char g;
                union {
                    struct {
                        char b, a;
                    };
                    cvec2 ba;
                };
            };
            cvec2 gb;
            cvec3 gba;
        };
    };
} cvec4;
static_assert(sizeof(cvec4) == sizeof(char) * 4, "[Mathc] wrong expected size");

/** casts a char * to a dereferenced cvec4 */
#define CVec4(vec) (*(cvec4 *) (vec))

/** casts a char * to a dereferenced const cvec4 */
#define ConstCVec4(vec) (*(const cvec4 *) (vec))


typedef union {
    char v[16];
    char m[4][4];
    cvec4 col[4];
    struct {
        char v0, v1, v2, v3;
        char v4, v5, v6, v7;
        char v8, v9, v10, v11;
        char v12, v13, v14, v15;
    };
    struct {
        char m00, m01, m02, m03;
        char m10, m11, m12, m13;
        char m20, m21, m22, m23;
        char m30, m31, m32, m33;
    };
} cmat4;
static_assert(sizeof(cmat4) == sizeof(char) * 16, "[Mathc] wrong expected size");

/** casts a char * to a dereferenced cmat4 */
#define CMat4(mat) (*(cmat4 *) (mat))

/** casts a char * to a dereferenced const cmat4 */
#define ConstCMat4(mat) (*(const cmat4 *) (mat))


#endif //MATHC_TYPES_CHAR_H
