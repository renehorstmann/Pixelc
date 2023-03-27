#ifndef M_UTILS_DINTERSECTION_H
#define M_UTILS_DINTERSECTION_H


#include <stdbool.h>
#include "../sca/double.h"
#include "../vec/dvec2.h"
#include "../vec/dvec3.h"
#include "../vec/dvec4.h"
#include "../mat/dmat3.h"

#ifndef DINTERSECTION_EPSILON
#define DINTERSECTION_EPSILON (double) 0.01
#endif

/** returns false if planes are parallel */
static bool dintersection_plane_plane(dvec3 *out_pos, dvec3 *out_dir,
                                      dvec4 plane_hessian_a, dvec4 plane_hessian_b) {
    *out_pos = *out_dir = dvec3_set(NAN);

    // parallel check
    if (dvec3_dot(plane_hessian_a.xyz, plane_hessian_b.xyz) > ((double) 1 - DINTERSECTION_EPSILON))
        return false;

    // line dir is orthogonal to both plane orthogonals (nx ny nz)
    dvec3 dir = dvec3_cross(plane_hessian_a.xyz, plane_hessian_b.xyz);
    dir = dvec3_normalize(dir);

    // hessian: (nx, ny, nz, d)
    // distance point to plane = x*nx + y*ny + z*nz + 1*d

    dmat3 A = {{0}};
    A = dmat3_set_row(A, plane_hessian_a.xyz, 0);
    A = dmat3_set_row(A, plane_hessian_b.xyz, 1);
    A = dmat3_set_row(A, dir, 2);

    // distance to planes should be 0, so -1*d
    dvec3 B = {{-plane_hessian_a.w, -plane_hessian_b.w, 0}};

    // solve A * X = B
    // X = A^-1 * B
    dvec3 X = dmat3_mul_vec(dmat3_inv(A), B);

    *out_pos = X;
    *out_dir = dir;

    return true;
}


/** returns false if plane and line are parallel */
static bool dintersection_plane_line(dvec3 *out_pos, dvec4 plane_hessian,
                                     dvec3 line_pos, dvec3 line_dir) {
    *out_pos = dvec3_set(NAN);

    double plane_line_dot = dvec3_dot(plane_hessian.xyz, line_dir);

    // parallel check
    if (dsca_abs(plane_line_dot) < DINTERSECTION_EPSILON)
        return false;

    dvec3 plane_point = dvec3_scale(plane_hessian.xyz, -plane_hessian.w);
    dvec3 w = dvec3_sub_vec(line_pos, plane_point);
    double si = -dvec3_dot(plane_hessian.xyz, w) / plane_line_dot;

    dvec3 si_dir = dvec3_scale(line_dir, si);

    // pos = w + si_dir + plane_point
    *out_pos = dvec3_add_vec(dvec3_add_vec(w, si_dir), plane_point);
    return true;
}


/** returns t (line_pos + line_dir * t), or NAN if not intersecting */
static double dintersection_triangle_line(dvec3 v0, dvec3 v1, dvec3 v2,
                                          dvec3 line_pos, dvec3 line_dir,
                                          bool culling) {
    dvec3 v0v1 = dvec3_sub_vec(v1, v0);
    dvec3 v0v2 = dvec3_sub_vec(v2, v0);
    dvec3 pvec = dvec3_cross(line_dir, v0v2);
    double det = dvec3_dot(v0v1, pvec);

    if (culling) {
        if (det < DINTERSECTION_EPSILON)
            return NAN;
    } else {
        if (dsca_abs(det) < DINTERSECTION_EPSILON)
            return NAN;
    }

    double inv_det = (double) 1 / det;

    dvec3 tvec = dvec3_sub_vec(line_pos, v0);
    double u = dvec3_dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1)
        return NAN;

    dvec3 qvec = dvec3_cross(tvec, v0v1);
    double v = dvec3_dot(line_dir, qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return NAN;

    return dvec3_dot(v0v2, qvec) * inv_det;
}


/** returns false if lines are parallel, searches for the nearest distance points */
static bool dintersection_line_line(double *out_tau_a, double *out_tau_b,
                                    dvec3 line_a_pos, dvec3 line_a_dir,
                                    dvec3 line_b_pos, dvec3 line_b_dir) {
    *out_tau_a = *out_tau_b = NAN;

    // Book: Real Time Collision Detection: section 5.1.8 Closest Point of Two Lines
    dvec3 r = dvec3_sub_vec(line_a_pos, line_b_pos);

    double a = dvec3_dot(line_a_dir, line_a_dir);
    double b = dvec3_dot(line_a_dir, line_b_dir);
    double c = dvec3_dot(line_a_dir, r);
    double e = dvec3_dot(line_b_dir, line_b_dir);
    double f = dvec3_dot(line_b_dir, r);

    double d = a * e - b * b;

    // parallel check
    if (dsca_abs(d) < DINTERSECTION_EPSILON)
        return false;

    *out_tau_a = (b * f - c * e) / d;
    *out_tau_b = (a * f - b * c) / d;
    return true;
}


/** returns the projection point on the line by tau. searches for the nearest distance points */
static double dintersection_line_point(dvec3 line_pos, dvec3 line_dir, dvec3 point) {
    return dvec3_dot(dvec3_sub_vec(point, line_pos), line_dir)
           / dvec3_dot(line_dir, line_dir);
}


//
// dvec2 versions:
//


/** returns false if lines are parallel */
static bool dintersection2_line_line(double *out_tau_a, double *out_tau_b,
                                     dvec2 line_a_pos, dvec2 line_a_dir,
                                     dvec2 line_b_pos, dvec2 line_b_dir) {
    *out_tau_a = *out_tau_b = NAN;

    // stupid clone of the dvec2 version above:
    dvec2 r = dvec2_sub_vec(line_a_pos, line_b_pos);

    double a = dvec2_dot(line_a_dir, line_a_dir);
    double b = dvec2_dot(line_a_dir, line_b_dir);
    double c = dvec2_dot(line_a_dir, r);
    double e = dvec2_dot(line_b_dir, line_b_dir);
    double f = dvec2_dot(line_b_dir, r);

    double d = a * e - b * b;

    // parallel check
    if (dsca_abs(d) < DINTERSECTION_EPSILON)
        return false;

    *out_tau_a = (b * f - c * e) / d;
    *out_tau_b = (a * f - b * c) / d;
    return true;
}

/** returns the projection point on the line by tau. searches for the nearest distance points */
static double dintersection2_line_point(dvec2 line_pos, dvec2 line_dir, dvec2 point) {
    return dvec2_dot(dvec2_sub_vec(point, line_pos), line_dir)
           / dvec2_dot(line_dir, line_dir);
}

#endif //M_UTILS_DINTERSECTION_H
