#pragma once

#include <math/vec2.h>

namespace kx {

/// A 2D quad.
struct Quad2 {
  vec2 p0;
  vec2 p1;
  vec2 p2;
  vec2 p3;

  Quad2() {}

  Quad2(const vec2& p0, const vec2& p1, const vec2& p2, const vec2& p3)
      : p0(p0), p1(p1), p2(p2), p3(p3) {}
};

}  // namespace kx
