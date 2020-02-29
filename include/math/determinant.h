#pragma once

#include <math/vec2.h>

namespace kx {

/// Return the 2x2 determinant of the two vectors.
/// This returns the determinant:
///   | a.x b.x |
///   | a.y b.y |
inline R det(const vec2& a, const vec2& b) { return a.x * b.y - a.y * b.x; }

}  // namespace kx
