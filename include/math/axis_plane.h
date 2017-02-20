#pragma once

#include <math/defs.h>

namespace kx {

/// A 3D axis-aligned plane, defined as x = d, y = d, or z = d.
struct AxisPlane
{
    enum Axis
    {
        X = 0,
        Y = 1,
        Z = 2
    };

    Axis axis;
    R ct;

    /// Construct a plane perpendicular to the X axis and containing the origin.
    KX_MATH_API AxisPlane ()
        : axis(Axis::X), ct(0) {}

    /// Construct an axis-aligned plane.
    /// \param axis Axis to which the plane is perpendicular (0 = x, 1 = y, 2 = z).
    /// \param ct The constant in the plane equation x = ct, y = ct, or z = ct.
    KX_MATH_API AxisPlane (Axis axis, R ct)
        : axis(axis), ct(ct) {}
};

} // namespace kx
