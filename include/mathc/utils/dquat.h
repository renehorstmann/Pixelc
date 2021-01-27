#ifndef MATHC_QUAT_DQUAT_H
#define MATHC_QUAT_DQUAT_H

#include <math.h>
#include "../initializer.h"
#include "../types/double.h"
#include "../vec/dvec3.h"
#include "../vec/dvec4.h"


/** dquat = [0, 0, 0, 1] */
static dquat dquat_eye() {
    return (dquat) QUAT4_INIT_EYE;
}


/** dst = -x, -y, -z, w */
static dquat dquat_conj(dquat q) {
    return (dquat) {{-q.x, -q.y, -q.z, q.w}};
}
/** dst = -x, -y, -z, w */
static dquat dquat_conj_v(const double *q) {
    return dquat_conj(DQuat(q));
}


/** dst = inv(dquat) */
static dquat dquat_inv(dquat q) {
    dquat conj = dquat_conj(q);
    return dvec4_scale(conj, 1.0 / dvec4_dot(q, q));
}
/** dst = inv(dquat) */
static dquat dquat_inv_v(const double *q) {
    return dquat_inv(DQuat(q));
}


/** dst = a @ b Hamilton Product */
static dquat dquat_mul(dquat q_a, dquat q_b) {
    // from cglm/dquat/glm_dquat_mul
    dquat res;
    res.v[0] = q_a.v[3] * q_b.v[0] + q_a.v[0] * q_b.v[3] + q_a.v[1] * q_b.v[2] - q_a.v[2] * q_b.v[1];
    res.v[1] = q_a.v[3] * q_b.v[1] - q_a.v[0] * q_b.v[2] + q_a.v[1] * q_b.v[3] + q_a.v[2] * q_b.v[0];
    res.v[2] = q_a.v[3] * q_b.v[2] + q_a.v[0] * q_b.v[1] - q_a.v[1] * q_b.v[0] + q_a.v[2] * q_b.v[3];
    res.v[3] = q_a.v[3] * q_b.v[3] - q_a.v[0] * q_b.v[0] - q_a.v[1] * q_b.v[1] - q_a.v[2] * q_b.v[2];
    return res;
}
/** dst = a @ b Hamilton Product */
static dquat dquat_mul_v(const double *q_a, const double *q_b) {
    return dquat_mul(DQuat(q_a), DQuat(q_b));
}


/** angle_axis = xyz + w=angle in rad */
static dquat dquat_from_angle_axis(dvec4 angle_axis) {
    // from cglm/dquat/glm_dquatv
    double a = angle_axis.w * 0.5f;
    double c = cos(a);
    double s = sin(a);

    dvec3 axis = dvec3_normalize(angle_axis.xyz);

    dquat res;
    res.xyz = dvec3_scale(axis, s);
    res.w = c;
    return res;
}
/** angle_axis = xyz + w=angle in rad */
static dquat dquat_from_angle_axis_v(const double *angle_axis) {
    return dquat_from_angle_axis(DQuat(angle_axis));
}


/** angle_axis = xyz + w=angle in rad */
static dvec4 dquat_to_angle_axis(dquat q) {
    // from cglm/dquat/glm_dquat_angle
    /*
     sin(theta / 2) = length(x*x + y*y + z*z)
     cos(theta / 2) = w
     theta          = 2 * atan(sin(theta / 2) / cos(theta / 2))
     */
    double imag_len = dvec3_norm(q.xyz);
    double angle = 2.0 * atan2f(imag_len, q.w);

    dvec4 angle_axis;
    angle_axis.xyz = dvec3_normalize(q.xyz);
    angle_axis.w = angle;
    return angle_axis;
}
/** angle_axis = xyz + w=angle in rad */
static dvec4 dquat_to_angle_axis_v(const double *q) {
    return dquat_to_angle_axis(DQuat(q));
}


static dmat3 dquat_to_rotation_matrix(dquat q) {
    // from cglm/dquat/glm_dquat_mat3
    double norm = dvec4_norm(q);
    double s = norm > 0.0 ? 2.0 / norm : 0.0;

    double x = q.x;
    double y = q.y;
    double z = q.z;
    double w = q.w;

    double xx, xy, wx;
    double yy, yz, wy;
    double zz, xz, wz;
    xx = s * x * x;
    xy = s * x * y;
    wx = s * w * x;
    yy = s * y * y;
    yz = s * y * z;
    wy = s * w * y;
    zz = s * z * z;
    xz = s * x * z;
    wz = s * w * z;

    dmat3 res;
    res.m[0][0] = 1.0 - yy - zz;
    res.m[1][1] = 1.0 - xx - zz;
    res.m[2][2] = 1.0 - xx - yy;

    res.m[0][1] = xy + wz;
    res.m[1][2] = yz + wx;
    res.m[2][0] = xz + wy;

    res.m[1][0] = xy - wz;
    res.m[2][1] = yz - wx;
    res.m[0][2] = xz - wy;
    return res;
}
static dmat3 dquat_to_rotation_matrix_v(const double *q) {
    return dquat_to_rotation_matrix(DQuat(q));
}


static dquat dquat_from_rotation_matrix(dmat3 mat) {
    // from cglm/mat3/glm_mat3_dquat
    dquat res;
    double trace, r, rinv;
    trace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];
    if (trace >= 0.0) {
        r = sqrtf(1.0 + trace);
        rinv = 0.5f / r;

        res.v[0] = rinv * (mat.m[1][2] - mat.m[2][1]);
        res.v[1] = rinv * (mat.m[2][0] - mat.m[0][2]);
        res.v[2] = rinv * (mat.m[0][1] - mat.m[1][0]);
        res.v[3] = r * 0.5;
    } else if (mat.m[0][0] >= mat.m[1][1] && mat.m[0][0] >= mat.m[2][2]) {
        r = sqrtf(1.0 - mat.m[1][1] - mat.m[2][2] + mat.m[0][0]);
        rinv = 0.5f / r;

        res.v[0] = r * 0.5;
        res.v[1] = rinv * (mat.m[0][1] + mat.m[1][0]);
        res.v[2] = rinv * (mat.m[0][2] + mat.m[2][0]);
        res.v[3] = rinv * (mat.m[1][2] - mat.m[2][1]);
    } else if (mat.m[1][1] >= mat.m[2][2]) {
        r = sqrtf(1.0 - mat.m[0][0] - mat.m[2][2] + mat.m[1][1]);
        rinv = 0.5 / r;

        res.v[0] = rinv * (mat.m[0][1] + mat.m[1][0]);
        res.v[1] = r * 0.5;
        res.v[2] = rinv * (mat.m[1][2] + mat.m[2][1]);
        res.v[3] = rinv * (mat.m[2][0] - mat.m[0][2]);
    } else {
        r = sqrtf(1.0 - mat.m[0][0] - mat.m[1][1] + mat.m[2][2]);
        rinv = 0.5 / r;

        res.v[0] = rinv * (mat.m[0][2] + mat.m[2][0]);
        res.v[1] = rinv * (mat.m[1][2] + mat.m[2][1]);
        res.v[2] = r * 0.5;
        res.v[3] = rinv * (mat.m[0][1] - mat.m[1][0]);
    }

    return res;
}
static dquat dquat_from_rotation_matrix_v(const double *mat_3) {
    return dquat_from_rotation_matrix(DMat3(mat_3));
}


static dquat dquat_slerp(dquat q_a, dquat q_b, double t) {
    // q_a cglm/dquat/glm_dquat_slerp
    double cos_theta = dvec4_dot(q_a, q_b);

    if (fabs(cos_theta) >= 1.0)
        return q_a;

    if (cos_theta < 0.0) {
        q_a = dvec4_neg(q_a);
        cos_theta = -cos_theta;
    }

    double sin_theta = sqrtf(1.0 - cos_theta * cos_theta);

    /* LERP q_b avoid zero division */
    if (fabs(sin_theta) < 0.001)
        return dvec4_mix(q_a, q_b, t);

    /* SLERP */
    double angle = acos(cos_theta);
    dquat q1 = dvec4_scale(q_a, sin((1.0 - t) * angle));
    dquat q2 = dvec4_scale(q_b, sin(t * angle));

    q1 = dvec4_add_vec(q1, q2);
    return dvec4_scale(q1, 1.0 / sin_theta);
}
static dquat dquat_slerp_v(const double *q_a, const double *q_b, double t) {
    return dquat_slerp(DQuat(q_a), DQuat(q_b), t);
}


#endif //MATHC_QUAT_DQUAT_H
