#pragma once

#include <math/defs.h>

namespace kx {

struct vec3;

/// A 4D vector.
struct vec4 {
  R x;
  R y;
  R z;
  R w;

  /// Construct the 0 vector.
  KX_MATH_API vec4() : x(0), y(0), z(0), w(0) {}

  /// Construct a vector from 4 coordinates.
  KX_MATH_API vec4(R _x, R _y, R _z, R _w) : x(_x), y(_y), z(_z), w(_w) {}

  /// Construct a vector from a value.
  /// x = y = z = w = val
  KX_MATH_API vec4(R val) : x(val), y(val), z(val), w(val) {}

  /// Construct a vector from a 3d vector and a w-coordinate.
  KX_MATH_API vec4(const vec3&, R w);

  /// Normalise the vector.
  KX_MATH_API void normalise();

  /// Return a const R pointer to the given vector's values.
  KX_MATH_API operator const R*() const { return (R*)this; }
};

KX_MATH_API vec4 normalise(const vec4&);

/// Negate the given vector.
KX_MATH_API vec4 operator-(vec4);

/// Add two vectors.
KX_MATH_API vec4 operator+(vec4, vec4);

/// Subtract two vectors.
KX_MATH_API vec4 operator-(vec4, vec4);

/// Modulate two vectors (component-wise multiplication).
KX_MATH_API vec4 operator*(vec4, vec4);

/// Divide two vectors component-wise.
KX_MATH_API vec4 operator/(vec4, vec4);

/// Add two vectors.
KX_MATH_API void operator+=(vec4&, vec4);

/// Subtract two vectors.
KX_MATH_API void operator-=(vec4&, vec4);

/// Modulate two vectors (component-wise multiplication).
KX_MATH_API void operator*=(vec4&, vec4);

/// Divide two vectors component-wise.
KX_MATH_API void operator/=(vec4&, vec4);

/// Return the given vector divided by its magnitude.
KX_MATH_API vec4 normalise(const vec4& v);

/// Return the vector's magnitude.
KX_MATH_API R norm(vec4 v);

/// Return the vector's squared magnitude.
KX_MATH_API R norm2(vec4 v);

/// Swap the two vectors.
inline void swap(vec4& a, vec4& b) {
  vec4 tmp = a;
  a = b;
  b = tmp;
}

}  // namespace kx
