#pragma once

#include <math/vec3.h>

namespace kx {

/// A 3D quad.
struct Quad3 {
  vec3 p0;
  vec3 p1;
  vec3 p2;
  vec3 p3;

  Quad3() {}

  Quad3(const vec3& p0, const vec3& p1, const vec3& p2, const vec3& p3)
      : p0(p0), p1(p1), p2(p2), p3(p3) {}
};

}  // namespace kx
