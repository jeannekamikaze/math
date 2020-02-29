#pragma once

#include <math/vec3.h>

namespace kx {

/// A sphere.
struct Sphere {
  vec3 center; /**< The sphere's center. */
  R radius2;   /**< The sphere's radius squared. */

  /// Construct a degenerate sphere of radius 0 centered at the origin.
  KX_MATH_API Sphere() : radius2(0) {}

  /// Construct a sphere.
  /// \param center The sphere's center.
  /// \param radius The sphere's radius.
  KX_MATH_API Sphere(vec3 c, R r2) : center(c), radius2(r2) {}

  /// Construct a sphere.
  /// \param cx X coordinate of sphere's center.
  /// \param cy Y coordinate of sphere's center.
  /// \param cz Z coordinate of sphere's center.
  /// \param r2 Sphere's radius squared.
  KX_MATH_API Sphere(R cx, R cy, R cz, R r2)
      : center(cx, cy, cz), radius2(r2) {}

  /// Update the sphere to contain the given point.
  /// The sphere's center is not moved, only its radius may change.
  KX_MATH_API void add(vec3 p) { radius2 = max(radius2, norm2(p)); }

  /// Return the sphere's radius.
  KX_MATH_API R radius() const { return sqrt(radius2); }
};

}  // namespace kx
