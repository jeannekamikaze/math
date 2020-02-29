#pragma once

#include <math/vec2.h>

namespace kx {

/// A 2D axis-aligned bounding box.
struct AABB2 {
  vec2 pmin, pmax;

  KX_MATH_API AABB2() : pmin(1), pmax(-1) {}

  KX_MATH_API AABB2(vec2 pmin, vec2 pmax) : pmin(pmin), pmax(pmax) {}

  /// Construct an AABB2 from an array of points.
  /// \param ps The array of points.
  /// \param n  The number of points in the array.
  KX_MATH_API AABB2(vec2* ps, unsigned n);

  /// Update the AABB2 to contain the point.
  KX_MATH_API void add(const vec2& p);

  /// Update the AABB2 to contain the given AABB2.
  KX_MATH_API void add(const AABB2&);
};

}  // namespace kx
