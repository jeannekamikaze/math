#pragma once

#include <math/defs.h>
#include <math/mat3.h>
#include <math/mat4.h>
#include <math/quat.h>

namespace kx {

class mat3;
struct quat;

/// Compare two floating-point numbers for equality.
///
/// This function first tests a and b for equality: a == b.
/// If the plain equality test fails, the function checks if one of a or b is 0.
/// In that case, the function performs a comparison using an absolute error,
/// where the error is given by eps: |a-b| <= eps.
/// Otherwise an ULP comparison is made, where the maximum ULP distance is given by
/// the ULPs parameter: ULP (a-b) <= ULPs.
///
/// \param eps  The error used in the absolute comparison.
/// \param ULPs The maximum ULP distance used in the ULP comparison.
/// \return True if the given Rs are equal, false otherwise.
KX_MATH_API bool R_eq (R a, R b, R eps, int ULPs);

/// Construct a 3x3 matrix representing the same rotation as the given quaternion.
KX_MATH_API mat3 qmat3 (const quat& q);

/// Construct a 4x4 matrix representing the same rotation as the given quaternion.
KX_MATH_API mat4 qmat4 (const quat& q);

/// Return the sign of the given value.
KX_MATH_API R sign (R x);

/// Return the pitch formed by the given forward vector.
KX_MATH_API R pitch_from_fwd (vec3 forward);

/// Return the yaw formed by the given forward vector.
KX_MATH_API R yaw_from_fwd (vec3 forward);

} // namespace kx
