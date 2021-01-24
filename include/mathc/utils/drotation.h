#ifndef MATHC_UTILS_DROTATION_H
#define MATHC_UTILS_DROTATION_H

#include "../vec/dvec3.h"
#include "../mat/dmat3.h"
#include "../mat/dmat4.h"


/** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
static dmat3 dmat3_rotation_from_angle_axis(dvec4 angle_axis) {
    // from cglm/affine/glm_rotate_make
    double c = cos(angle_axis.w);
    double s = sin(angle_axis.w);

    dvec3 axis = dvec3_normalize(angle_axis.xyz);
    dvec3 v = dvec3_scale(axis, 1.0 - c);
    dvec3 vs = dvec3_scale(axis, s);

    dmat3 res;
    res.col[0] = dvec3_scale(axis, v.x);
    res.col[1] = dvec3_scale(axis, v.y);
    res.col[2] = dvec3_scale(axis, v.z);

    res.m[0][0] += c;      res.m[1][0] -= vs.z;   res.m[2][0] += vs.y;
    res.m[0][1] += vs.z;   res.m[1][1] += c;      res.m[2][1] -= vs.x;
    res.m[0][2] -= vs.y;   res.m[1][2] += vs.x;   res.m[2][2] += c;
    return res;
}
/** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
static dmat3 dmat3_rotation_from_angle_axis_v(const double *angle_axis) {
    return dmat3_rotation_from_angle_axis(DVec4(angle_axis));
}


/** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
static dmat3 dmat3_rotation_from_dir_z(dvec3 dir_z) {
    dvec3 z = dvec3_normalize(dir_z);

    // align rotation x to unit x (if unit x ~= dir_z, align to unit y)
    dvec3 align_x = dvec3_unit_x();
    if(fabs(dvec3_dot(z, align_x)) > 0.9)
        align_x = dvec3_unit_y();

    dvec3 y = dvec3_normalize(dvec3_cross(z, align_x));

    dvec3 x = dvec3_cross(y, z);

    dmat3 res;
    res.col[0] = x;
    res.col[1] = y;
    res.col[2] = z;
    return res;
}
/** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
static dmat3 dmat3_rotation_from_dir_z_v(const double *dir_z) {
    return dmat3_rotation_from_dir_z(DVec3(dir_z));
}


/** uses dmat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
static dmat4 dmat4_pose_from_ray(dvec3 ray_start, dvec3 ray_dir) {
    dmat4 pose = dmat4_eye();
    pose = dmat4_set_upper_left3(pose, dmat3_rotation_from_dir_z(ray_dir));
    pose.col[3].xyz = ray_start;
    return pose;
}
/** uses dmat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
static dmat4 dmat4_pose_from_ray_v(const float *ray_start, const float *ray_dir) {
    return dmat4_pose_from_ray(DVec3(ray_start), DVec3(ray_dir));
}


#endif //MATHC_UTILS_DROTATION_H
