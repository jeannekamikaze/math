#pragma once

#include <math/vec3.h>

namespace kx {

struct Triangle3;

/// A 3D plane, defined as ax + by + cz + d = 0.
struct Plane
{
    R a, b, c, d;

    /// Construct a degenerate plane with normal (0,0,0) and distance 0.
    KX_MATH_API Plane ()
        : a(0), b(0), c(0), d(0) {}

    /// Construct a new plane.
    /// \param normal The plane's normal.
    /// \param d      The perpendicular distance from the plane to the origin.
    KX_MATH_API Plane (const vec3& normal, R d)
        : a(normal.x), b(normal.y), c(normal.z), d(d) {}

    /// Construct a plane.
    /// \param a Plane's normal x component.
    /// \param b Plane's normal y component.
    /// \param c Plane's normal z component.
    /// \param d Perpendicular distance to the origin.
    KX_MATH_API Plane (R a, R b, R c, R d)
        : a(a), b(b), c(c), d(d) {}

    /// Construct a plane.
    /// \param point  A point in the plane.
    /// \param normal The plane's normal.
    KX_MATH_API Plane (const vec3& point, const vec3& normal)
        : a(normal.x), b(normal.y), c(normal.z), d(-dot(point,normal)) {}

    /// Construct the supporting plane of a triangle.
    /// The triangle's points must be given in counter-clockwise order.
    KX_MATH_API Plane (const Triangle3&);

    /// Set the plane's values to the vector's values.
    /// (A,B,C) = (x,y,z)
    /// D = w
    KX_MATH_API void operator= (const vec4& v);
};

} // namespace kx
