#pragma once

#include <math/defs.h>
#include <math/vec3.h>

namespace kx {

/// A quaternion.
struct quat {
  R w, x, y, z;

  quat() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

  quat(R _w, R _x, R _y, R _z) : w(_w), x(_x), y(_y), z(_z) {}
};

/// Multiply two quaternions.
quat operator*(quat q1, quat q2);

/// Construct a rotation quaternion.
quat qrot(R angle, R x, R y, R z);

/// Invert the quaternion.
quat inv(quat q);

/// Return the quaternion's conjugate.
quat conj(quat q);

/// Rotate the given vector by the given unit quaternion.
vec3 rot(const quat& q, const vec3& v);

/// Rotate the given vector by the given unit quaternion.
void rot(const quat& q, vec3& v);

}  // namespace kx
