#ifndef M_MAT_UCMAT4_H
#define M_MAT_UCMAT4_H


#include "ucmatn.h"
#include "../types/ucmat4.h"
#include "../types/ucmat2.h"
#include "../types/ucmat3.h"
#include "../vec/ucvecn.h"


/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_float(const float *cast) {
    ucmat4 res;
    ucmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_double(const double *cast) {
    ucmat4 res;
    ucmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_int(const int *cast) {
    ucmat4 res;
    ucmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_uchar(const unsigned char *cast) {
    ucmat4 res;
    ucmatN_cast_into(res.v, cast, 4);
    return res;
}


/** dst = mat * 255 */
static ucmat4 ucmat4_cast_from_float_1(const float *cast) {
    ucmat4 res;
    ucmatN_cast_from_float_1(res.v, cast, 4);
    return res;
}

/** dst = mat * 255 */
static ucmat4 ucmat4_cast_from_double_1(const double *cast) {
    ucmat4 res;
    ucmatN_cast_from_double_1(res.v, cast, 4);
    return res;
}

/** dst = mat * 255 */
static ucmat4 ucmat4_cast_from_longdouble_1(const long double *cast) {
    ucmat4 res;
    ucmatN_cast_from_longdouble_1(res.v, cast, 4);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static ucmat4 ucmat4_eye() {
    ucmat4 res;
    ucmatN_eye(res.v, 4);
    return res;
}

/** a == b */
static bool ucmat4_cmp(ucmat4 a, ucmat4 b) {
    return ucvecN_cmp(a.v, b.v, 4 * 4);
}


/** dst = m[row][:] */
static ucvec4 ucmat4_get_row(ucmat4 m, int row) {
    ucvec4 res;
    ucmatN_get_row(res.v, m.v, row, 4);
    return res;
}


/** dst = m[:][col] */
static ucvec4 ucmat4_get_col(ucmat4 m, int col) {
    ucvec4 res;
    ucmatN_get_col(res.v, m.v, col, 4);
    return res;
}


/** dst = m; dst[row][:] = v */
static ucmat4 ucmat4_set_row(ucmat4 m, ucvec4 v, int row) {
    ucmatN_set_row(m.v, v.v, row, 4);
    return m;
}

/** m[row][:] = v; dst = m */
static ucmat4 ucmat4_set_this_row(ucmat4 *m, ucvec4 v, int row) {
    ucmatN_set_row(m->v, v.v, row, 4);
    return *m;
}

/** dst = m; dst[:][col] = v */
static ucmat4 ucmat4_set_col(ucmat4 m, ucvec4 v, int col) {
    ucmatN_set_col(m.v, v.v, col, 4);
    return m;
}

/** mat[:][col] = v; dst = m */
static ucmat4 ucmat4_set_this_col(ucmat4 *mat, ucvec4 v, int col) {
    ucmatN_set_col(mat->v, v.v, col, 4);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static ucmat4 ucmat4_set_row_sca(ucmat4 m, unsigned char s, int row) {
    ucmatN_set_row_sca(m.v, s, row, 4);
    return m;
}

/** m[row][:] = s; dst = m */
static ucmat4 ucmat4_set_this_row_sca(ucmat4 *m, unsigned char s, int row) {
    ucmatN_set_row_sca(m->v, s, row, 4);
    return *m;
}


/** dst = m; dst[:][col] = s */
static ucmat4 ucmat4_set_col_sca(ucmat4 m, unsigned char s, int col) {
    ucmatN_set_col_sca(m.v, s, col, 4);
    return m;
}

/** m[:][col] = s; dst = m */
static ucmat4 ucmat4_set_this_col_sca(ucmat4 *m, unsigned char s, int col) {
    ucmatN_set_col_sca(m->v, s, col, 4);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static unsigned char ucmat4_trace(ucmat4 m) {
    return ucmatN_trace(m.v, 4);
}


/** dst = m^t */
static ucmat4 ucmat4_transpose(ucmat4 m) {
    ucmat4 res;
    ucmatN_transpose_no_alias(res.v, m.v, 4);
    return res;
}


/** dst = a @ b */
static ucmat4 ucmat4_mul_mat(ucmat4 a, ucmat4 b) {
    ucmat4 res;
    ucmatN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static ucvec4 ucmat4_mul_vec(ucmat4 a, ucvec4 b) {
    ucvec4 res;
    ucmatN_mul_vec_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static ucvec4 ucvec4_mul_mat(ucvec4 a, ucmat4 b) {
    ucvec4 res;
    ucvecN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}



/** returns = determinant mm */
static unsigned char ucmat4_det(ucmat4 mm) {
    // from cglm/ucmat4.h/glm_mat4_det
    /* [square] det(A) = det(At) */
    unsigned char t[6];
    unsigned char a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3],
            e = mm.m[1][0], f = mm.m[1][1], g = mm.m[1][2], h = mm.m[1][3],
            i = mm.m[2][0], j = mm.m[2][1], k = mm.m[2][2], l = mm.m[2][3],
            m = mm.m[3][0], n = mm.m[3][1], o = mm.m[3][2], p = mm.m[3][3];

    t[0] = k * p - o * l;
    t[1] = j * p - n * l;
    t[2] = j * o - n * k;
    t[3] = i * p - m * l;
    t[4] = i * o - m * k;
    t[5] = i * n - m * j;

    return a * (f * t[0] - g * t[1] + h * t[2])
           - b * (e * t[0] - g * t[3] + h * t[4])
           + c * (e * t[1] - f * t[3] + h * t[5])
           - d * (e * t[2] - f * t[4] + g * t[5]);
}


/** dst = inverted mm */
static ucmat4 ucmat4_inv(ucmat4 mm) {
    // from cglm/ucmat4.h/glm_mat4_inv
    unsigned char t[6];
    unsigned char a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3];
    unsigned char e = mm.m[1][0], f = mm.m[1][1], g = mm.m[1][2], h = mm.m[1][3];
    unsigned char i = mm.m[2][0], j = mm.m[2][1], k = mm.m[2][2], l = mm.m[2][3];
    unsigned char m = mm.m[3][0], n = mm.m[3][1], o = mm.m[3][2], p = mm.m[3][3];

    t[0] = k * p - o * l;
    t[1] = j * p - n * l;
    t[2] = j * o - n * k;
    t[3] = i * p - m * l;
    t[4] = i * o - m * k;
    t[5] = i * n - m * j;

    ucmat4 res;
    res.m[0][0] = f * t[0] - g * t[1] + h * t[2];
    res.m[1][0] = -(e * t[0] - g * t[3] + h * t[4]);
    res.m[2][0] = e * t[1] - f * t[3] + h * t[5];
    res.m[3][0] = -(e * t[2] - f * t[4] + g * t[5]);

    res.m[0][1] = -(b * t[0] - c * t[1] + d * t[2]);
    res.m[1][1] = a * t[0] - c * t[3] + d * t[4];
    res.m[2][1] = -(a * t[1] - b * t[3] + d * t[5]);
    res.m[3][1] = a * t[2] - b * t[4] + c * t[5];

    t[0] = g * p - o * h;
    t[1] = f * p - n * h;
    t[2] = f * o - n * g;
    t[3] = e * p - m * h;
    t[4] = e * o - m * g;
    t[5] = e * n - m * f;

    res.m[0][2] = b * t[0] - c * t[1] + d * t[2];
    res.m[1][2] = -(a * t[0] - c * t[3] + d * t[4]);
    res.m[2][2] = a * t[1] - b * t[3] + d * t[5];
    res.m[3][2] = -(a * t[2] - b * t[4] + c * t[5]);

    t[0] = g * l - k * h;
    t[1] = f * l - j * h;
    t[2] = f * k - j * g;
    t[3] = e * l - i * h;
    t[4] = e * k - i * g;
    t[5] = e * j - i * f;

    res.m[0][3] = -(b * t[0] - c * t[1] + d * t[2]);
    res.m[1][3] = a * t[0] - c * t[3] + d * t[4];
    res.m[2][3] = -(a * t[1] - b * t[3] + d * t[5]);
    res.m[3][3] = a * t[2] - b * t[4] + c * t[5];

    unsigned char det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0] + d * res.m[3][0];
    ucvecN_div(res.v, res.v, det, 16);

    return res;
}

/** dst = m[col:col+2, row:row+2] */
static ucmat2 ucmat4_get_block2(ucmat4 m, int row, int col) {
    ucmat2 res;
    ucmatN_get_block(res.v, m.v, row, col, 2, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static ucmat4 ucmat4_set_block2(ucmat4 m, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(m.v, block_2.v, row, col, 2, 4);
    return m;
}


/** m[col:col+2, row:row+2] = block; dst = m */
static ucmat4 ucmat4_set_this_block2(ucmat4 *m, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(m->v, block_2.v, row, col, 2, 4);
    return *m;
}


/** dst = m[col:col+2, row:row+2] */
static ucmat3 ucmat4_get_block3(ucmat4 m, int row, int col) {
    ucmat3 res;
    ucmatN_get_block(res.v, m.v, row, col, 3, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static ucmat4 ucmat4_set_block3(ucmat4 m, ucmat3 block_3, int row, int col) {
    ucmatN_set_block(m.v, block_3.v, row, col, 3, 4);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static ucmat4 ucmat4_set_this_block3(ucmat4 *m, ucmat3 block_3, int row, int col) {
    ucmatN_set_block(m->v, block_3.v, row, col, 3, 4);
    return *m;
}


/** dst = m[:2, :2] */
static ucmat2 ucmat4_get_upper_left2(ucmat4 m) {
    return ucmat4_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static ucmat4 ucmat4_set_upper_left2(ucmat4 m, ucmat2 block_2) {
    return ucmat4_set_block2(m, block_2, 0, 0);
}

/** m[:2, :2] = block; dst = m */
static ucmat4 ucmat4_set_this_upper_left2(ucmat4 *m, ucmat2 block_2) {
    return ucmat4_set_this_block2(m, block_2, 0, 0);
}


/** dst = m[:3, :3] */
static ucmat3 ucmat4_get_upper_left3(ucmat4 m) {
    return ucmat4_get_block3(m, 0, 0);
}


/** dst = m; dst[:3, :3] = block */
static ucmat4 ucmat4_set_upper_left3(ucmat4 m, ucmat3 block_3) {
    return ucmat4_set_block3(m, block_3, 0, 0);
}

/** m[:3, :3] = block; dst = m */
static ucmat4 ucmat4_set_this_upper_left3(ucmat4 *m, ucmat3 block_3) {
    return ucmat4_set_this_block3(m, block_3, 0, 0);
}

#endif //M_MAT_UCMAT4_H
