#pragma once

#include <math/vec3.h>

namespace kx {

/// A 3D ray.
struct Ray3 {
  vec3 pos;
  vec3 dir;

  /// Construct a degenerate ray, with position 0 and direction 0.
  KX_MATH_API Ray3() {}

  /// Construct a ray.
  /// pos The ray's position.
  /// dir The ray's direction.
  KX_MATH_API Ray3(const vec3& pos, const vec3& dir) : pos(pos), dir(dir) {}

  /// Evaluate the ray equation.
  /// ray(t) = ray.pos + ray.dir * t
  /// \param t The distance along the ray's direction from the ray's position.
  KX_MATH_API vec3 operator()(R t) const { return pos + dir * t; }
};

/// Return the ray parameter t such that p = ray(t).
/// Ray direction must be != vec3(0), otherwise 0 is returned.
inline KX_MATH_API R rayt(const Ray3& ray, const vec3& p) {
  if (ray.dir.x != 0) return (p.x - ray.pos.x) / ray.dir.x;
  if (ray.dir.y != 0) return (p.y - ray.pos.y) / ray.dir.y;
  if (ray.dir.z != 0) return (p.z - ray.pos.z) / ray.dir.z;
  return 0;
}

/// Advance the ray.
inline KX_MATH_API Ray3 operator+=(const Ray3& ray, const R& offset) {
  return Ray3(ray(offset), ray.dir);
}

}  // namespace kx
