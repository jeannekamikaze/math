#pragma once

#include <math/vec3.h>

namespace kx {

/// A 3D triangle.
struct Triangle3 {
  vec3 p0;
  vec3 p1;
  vec3 p2;

  Triangle3() {}

  Triangle3(const vec3& p0, const vec3& p1, const vec3& p2)
      : p0(p0), p1(p1), p2(p2) {}
};

}  // namespace kx
