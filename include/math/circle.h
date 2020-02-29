#pragma once

#include <math/vec2.h>

namespace kx {

/// A circle.
struct Circle {
  vec2 center;
  R radius2;

  /// Construct the unit circle centered at the origin.
  KX_MATH_API Circle() : radius2(1.0) {}

  /// Construct a circle.
  KX_MATH_API Circle(vec2 _center, R _radius)
      : center(_center), radius2(_radius * _radius) {}

  /// Update the circle to contain the point.
  /// The circle's center is not moved, only its radius may change.
  KX_MATH_API void add(vec2 p) { radius2 = max(radius2, norm2(p)); }

  /// Return the circle's radius.
  KX_MATH_API R radius() const { return sqrt(radius2); }
};

}  // namespace kx
