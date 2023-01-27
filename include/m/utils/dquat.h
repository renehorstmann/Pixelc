#ifndef M_UTILS_DQUAT_H
#define M_UTILS_DQUAT_H


#include <math.h>
#include "../types/double.h"
#include "../sca/double.h"
#include "../vec/dvec3.h"
#include "../vec/dvec4.h"
#include "../mat/dmat4.h"


/** dvec4 = [0, 0, 0, 1] */
static dvec4 dquat_eye() {
    dvec4 self;
    self.x = 0;
    self.y = 0;
    self.z = 0;
    self.w = 1;
    return self;
}


/** dst = -x, -y, -z, w */
static dvec4 dquat_conj(dvec4 q) {
    dvec4 self;
    self.x = -q.x;
    self.y = -q.y;
    self.z = -q.z;
    self.w = q.w;
    return self;
}

/** dst = inv(dvec4) */
static dvec4 dquat_inv(dvec4 q) {
    dvec4 conj = dquat_conj(q);
    return dvec4_scale(conj, 1.0f / dvec4_dot(q, q));
}


/** dst = a @ b Hamilton Product */
static dvec4 dquat_mul(dvec4 q_a, dvec4 q_b) {
    // from cglm/dvec4/glm_quat_mul
    dvec4 res;
    res.v[0] = q_a.v[3] * q_b.v[0] + q_a.v[0] * q_b.v[3] + q_a.v[1] * q_b.v[2] - q_a.v[2] * q_b.v[1];
    res.v[1] = q_a.v[3] * q_b.v[1] - q_a.v[0] * q_b.v[2] + q_a.v[1] * q_b.v[3] + q_a.v[2] * q_b.v[0];
    res.v[2] = q_a.v[3] * q_b.v[2] + q_a.v[0] * q_b.v[1] - q_a.v[1] * q_b.v[0] + q_a.v[2] * q_b.v[3];
    res.v[3] = q_a.v[3] * q_b.v[3] - q_a.v[0] * q_b.v[0] - q_a.v[1] * q_b.v[1] - q_a.v[2] * q_b.v[2];
    return res;
}


/** angle_axis = xyz + w=angle in rad */
static dvec4 dquat_from_angle_axis(dvec4 angle_axis) {
    // from cglm/dvec4/glm_quatv
    double a = angle_axis.w * 0.5f;
    double c = dsca_cos(a);
    double s = dsca_sin(a);

    dvec3 axis = dvec3_normalize(angle_axis.xyz);

    dvec4 res;
    res.xyz = dvec3_scale(axis, s);
    res.w = c;
    return res;
}


/** angle_axis = xyz + w=angle in rad */
static dvec4 dquat_to_angle_axis(dvec4 q) {
    // from cglm/dvec4/glm_quat_angle
    /*
     sin(theta / 2) = length(x*x + y*y + z*z)
     cos(theta / 2) = w
     theta          = 2 * atan(sin(theta / 2) / cos(theta / 2))
     */
    double imag_len = dvec3_norm(q.xyz);
    double angle = (double) 2 * dsca_atan2(imag_len, q.w);

    dvec4 angle_axis;
    angle_axis.xyz = dvec3_normalize(q.xyz);
    angle_axis.w = angle;
    return angle_axis;
}

/** returns the orientation of dvec4 as 3*3 rotation matrix */
static dmat3 dquat_to_rotation_matrix(dvec4 q) {
    // from cglm/dvec4/glm_quat_mat3
    double norm = dvec4_norm(q);
    double s = norm > 0 ? (double) 2 / norm : 0;

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
    res.m[0][0] = (double) 1 - yy - zz;
    res.m[1][1] = (double) 1 - xx - zz;
    res.m[2][2] = (double) 1 - xx - yy;

    res.m[0][1] = xy + wz;
    res.m[1][2] = yz + wx;
    res.m[2][0] = xz + wy;

    res.m[1][0] = xy - wz;
    res.m[2][1] = yz - wx;
    res.m[0][2] = xz - wy;
    return res;
}


/** returns the orientation of a 3*3 rotation matrix as dvec4 */
static dvec4 dquat_from_rotation_matrix(dmat3 mat) {
    // from cglm/dmat3/glm_mat3_quat
    dvec4 res;
    double trace, r, rinv;
    trace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];
    if (trace >= 0) {
        r = dsca_sqrt((double) 1 + trace);
        rinv = (double) 0.5 / r;

        res.v[0] = rinv * (mat.m[1][2] - mat.m[2][1]);
        res.v[1] = rinv * (mat.m[2][0] - mat.m[0][2]);
        res.v[2] = rinv * (mat.m[0][1] - mat.m[1][0]);
        res.v[3] = r * (double) 0.5;
    } else if (mat.m[0][0] >= mat.m[1][1] && mat.m[0][0] >= mat.m[2][2]) {
        r = dsca_sqrt((double) 1 - mat.m[1][1] - mat.m[2][2] + mat.m[0][0]);
        rinv = (double) 0.5 / r;

        res.v[0] = r * (double) 0.5;
        res.v[1] = rinv * (mat.m[0][1] + mat.m[1][0]);
        res.v[2] = rinv * (mat.m[0][2] + mat.m[2][0]);
        res.v[3] = rinv * (mat.m[1][2] - mat.m[2][1]);
    } else if (mat.m[1][1] >= mat.m[2][2]) {
        r = dsca_sqrt((double) 1 - mat.m[0][0] - mat.m[2][2] + mat.m[1][1]);
        rinv = (double) 0.5 / r;

        res.v[0] = rinv * (mat.m[0][1] + mat.m[1][0]);
        res.v[1] = r * (double) 0.5;
        res.v[2] = rinv * (mat.m[1][2] + mat.m[2][1]);
        res.v[3] = rinv * (mat.m[2][0] - mat.m[0][2]);
    } else {
        r = dsca_sqrt((double) 1 - mat.m[0][0] - mat.m[1][1] + mat.m[2][2]);
        rinv = (double) 0.5 / r;

        res.v[0] = rinv * (mat.m[0][2] + mat.m[2][0]);
        res.v[1] = rinv * (mat.m[1][2] + mat.m[2][1]);
        res.v[2] = r * (double) 0.5;
        res.v[3] = rinv * (mat.m[0][1] - mat.m[1][0]);
    }

    return res;
}

/** returns the orientation of a 3*3 rotation matrix as dvec4 */
static void dquat_pose_from_pose_matrix(dvec3 *out_pose_pos, dvec4 *out_pose_quat, dmat4 mat_pose) {
    *out_pose_pos = mat_pose.col[3].xyz;
    *out_pose_quat = dquat_from_rotation_matrix(dmat4_get_upper_left3(mat_pose));
}

/** returns the orientation of a 3*3 rotation matrix as dvec4 */
static dmat4 dquat_pose_to_pose_matrix(dvec3 pose_pos, dvec4 pose_quat) {
    dmat4 pose = dmat4_eye();
    pose.col[3].xyz = pose_pos;
    dmat4_set_this_upper_left3(&pose, dquat_to_rotation_matrix(pose_quat));
    return pose;
}


/** returns the rotated position pos with the rotation of q */
static dvec3 dquat_rotate_pos(dvec4 q, dvec3 pos) {
    dvec4 p;
    p.xyz = pos;
    p.w = 0;
    // res = q @ pos(w=0) @ conj(q)
    return dquat_mul(q, dquat_mul(p, dquat_conj(q))).xyz;
}


/**
 * Inverts the given pose (position + orientation)
 * Same as inverting a dmat4 pose
 */
static void dquat_pose_inv(dvec3 *out_pose_inv_pos, dvec4 *out_pose_inv_quat, dvec3 pose_pos, dvec4 pose_quat) {
    *out_pose_inv_quat = dquat_inv(pose_quat);
    *out_pose_inv_pos = dvec3_neg(dquat_rotate_pos(*out_pose_inv_quat, pose_pos));
}


/** returns pos transform by pose a @ b */
static dvec3 dquat_pose_transform_pos(dvec3 a_pos, dvec4 a_quat, dvec3 pos_b) {
    return dvec3_add_vec(a_pos, dquat_rotate_pos(a_quat, pos_b));
}


/** returns pose transform of a @ b */
static void dquat_pose_transform_pose(dvec3 *out_pos, dvec4 *out_quat,
                                     dvec3 a_pos, dvec4 a_quat,
                                     dvec3 b_pos, dvec4 b_quat) {
    *out_pos = dquat_pose_transform_pos(a_pos, a_quat, b_pos);
    *out_quat = dquat_mul(a_quat, b_quat);
}


/** spherical linear interpolation between a and b, t in [0 : 1] */
static dvec4 dquat_slerp(dvec4 q_a, dvec4 q_b, double t) {
    // from cglm/dvec4/glm_quat_slerp
    double cos_theta = dvec4_dot(q_a, q_b);

    if (dsca_abs(cos_theta) >= 1)
        return q_a;

    if (cos_theta < 0) {
        q_a = dvec4_neg(q_a);
        cos_theta = -cos_theta;
    }

    double sin_theta = dsca_sqrt((double) 1 - cos_theta * cos_theta);

    /* LERP q_b avoid zero division */
    if (dsca_abs(sin_theta) < (double) 0.001)
        return dvec4_mix(q_a, q_b, t);

    /* SLERP */
    double angle = dsca_acos(cos_theta);
    dvec4 q1 = dvec4_scale(q_a, dsca_sin(((double) 1 - t) * angle));
    dvec4 q2 = dvec4_scale(q_b, dsca_sin(t * angle));

    q1 = dvec4_add_vec(q1, q2);
    return dvec4_scale(q1, (double) 1 / sin_theta);
}


#endif //M_UTILS_DQUAT_H
