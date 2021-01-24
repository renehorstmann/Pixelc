#ifndef MATHC_TYPES_DOUBLE_H
#define MATHC_TYPES_DOUBLE_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef union dvec2 {
    double v[2];
    struct {
        double v0, v1;
    };
    struct {
        double x, y;
    };
} dvec2;
static_assert(sizeof(dvec2) == sizeof(double) * 2, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec2 */
#define DVec2(vec) (*(dvec2 *) (vec))

/** casts a double * to a dereferenced const dvec2 */
#define ConstDVec2(vec) (*(const dvec2 *) (vec))


typedef union dmat2 {
    double v[4];
    double m[2][2];
    dvec2 col[2];
    struct {
        double v0, v1;
        double v2, v3;
    };
    struct {
        double m00, m01;
        double m10, m11;
    };
} dmat2;
static_assert(sizeof(dmat2) == sizeof(double) * 4, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dmat2 */
#define DMat2(mat) (*(dmat2 *) (mat))

/** casts a double * to a dereferenced const dmat2 */
#define ConstDMat2(mat) (*(const dmat2 *) (mat))

typedef union dvec3 {
    double v[3];
    struct {
        double v0, v1, v2;
    };
    dvec2 xy;
    struct {
        double x;
        union {
            struct {
                double y, z;
            };
            dvec2 yz;
        };
    };
} dvec3;
static_assert(sizeof(dvec3) == sizeof(double) * 3, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec3 */
#define DVec3(vec) (*(dvec3 *) (vec))

/** casts a double * to a dereferenced const dvec3 */
#define ConstDVec3(vec) (*(const dvec3 *) (vec))


typedef union dmat3 {
    double v[9];
    double m[3][3];
    dvec3 col[3];
    struct {
        double v0, v1, v2;
        double v3, v4, v5;
        double v6, v7, v8;
    };
    struct {
        double m00, m01, m02;
        double m10, m11, m12;
        double m20, m21, m22;
    };
} dmat3;
static_assert(sizeof(dmat3) == sizeof(double) * 9, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dmat3 */
#define DMat3(mat) (*(dmat3 *) (mat))

/** casts a double * to a dereferenced const dmat3 */
#define ConstDMat3(mat) (*(const dmat3 *) (mat))


typedef union dvec4 {
    double v[4];
    struct {
        double v0, v1, v2, v3;
    };
    dvec2 xy;
    dvec3 xyz;
    struct {
        double x;
        union {
            struct {
                double y;
                union {
                    struct {
                        double z, w;
                    };
                    dvec2 zw;
                };
            };
            dvec2 yz;
            dvec3 yzw;
        };
    };
} dvec4;
static_assert(sizeof(dvec4) == sizeof(double) * 4, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec4 */
#define DVec4(vec) (*(dvec4 *) (vec))

/** casts a double * to a dereferenced const dvec4 */
#define ConstDVec4(vec) (*(const dvec4 *) (vec))


typedef union dmat4 {
    double v[16];
    double m[4][4];
    dvec4 col[4];
    struct {
        double v0, v1, v2, v3;
        double v4, v5, v6, v7;
        double v8, v9, v10, v11;
        double v12, v13, v14, v15;
    };
    struct {
        double m00, m01, m02, m03;
        double m10, m11, m12, m13;
        double m20, m21, m22, m23;
        double m30, m31, m32, m33;
    };
} dmat4;
static_assert(sizeof(dmat4) == sizeof(double) * 16, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dmat4 */
#define DMat4(mat) (*(dmat4 *) (mat))

/** casts a double * to a dereferenced const dmat4 */
#define ConstDMat4(mat) (*(const dmat4 *) (mat))



// quaternion type
typedef dvec4 dquat;
#define DQuat DVec4
#define ConstDQuat ConstDVec4

#endif //MATHC_TYPES_DOUBLE_H
