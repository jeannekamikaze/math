#pragma once

#include <math/vec3.h>

namespace kx {

/// A 3D axis-aligned bounding box.
struct AABB3
{
    vec3 pmin, pmax;

    /// Construct an AABB with pmin = 1 and pmax = -1.
    KX_MATH_API AABB3 ()
        : pmin(1), pmax(-1) {}

    /// Construct an AABB from two points.
    KX_MATH_API AABB3 (vec3 pmin, vec3 pmax)
        : pmin(pmin), pmax(pmax) {}

    /// Construct an AABB from two points.
    KX_MATH_API AABB3 (R xmin, R ymin, R zmin,
                       R xmax, R ymax, R zmax)
        : pmin(xmin, ymin, zmin),
          pmax(xmax, ymax, zmax) {}

    /// Construct an AABB from two points.
    KX_MATH_API AABB3 (const R val[6])
        : pmin(val[0], val[1], val[2]),
          pmax(val[3], val[4], val[5]) {}

    /// Construct an AABB from an array of points.
    /// \param ps The array of points.
    /// \param n  The number of points in the array.
    KX_MATH_API AABB3 (vec3* ps, unsigned n);

    /// Update the AABB to contain the point.
    KX_MATH_API void add (const vec3& p);

    /// Update the AABB to contain the given AABB3.
    KX_MATH_API void add (const AABB3&);
};

} // namespace kx
