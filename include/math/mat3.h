#pragma once

#include <math/vec3.h>

namespace kx {

class mat4;

/// A column-major 3x3 matrix.
class mat3 {
  R val[3][3];

 public:
  /// Construct the identity matrix.
  KX_MATH_API mat3();

  /// Construct a matrix from 9 values.
  KX_MATH_API mat3(R m00, R m10, R m20, R m01, R m11, R m21, R m02, R m12,
                   R m22);

  /// Construct a matrix from 3 column vectors.
  KX_MATH_API mat3(const vec3& v0, const vec3& v1, const vec3& v2);

  /// Construct a transformation matrix from 3 vectors.
  KX_MATH_API mat3(const vec2& right, const vec2& up, const vec2& position);

  /// Construct a 3x3 matrix by taking the upper 3x3 part of the 4x4 matrix.
  KX_MATH_API mat3(const mat4&);

  /// Return a mutable reference to the specified value.
  KX_MATH_API R& operator()(int row, int col);

  /// Access the value at the specified position.
  KX_MATH_API R operator()(int row, int col) const;

  /// Return a mutable reference to the matrix's first column.
  KX_MATH_API vec2& v0();

  /// Return a mutable reference to the matrix's second column.
  KX_MATH_API vec2& v1();

  /// Return a mutable reference to the matrix's third column.
  KX_MATH_API vec2& v2();

  /// Return the matrix's first column.
  KX_MATH_API const vec2& v0() const;

  /// Return the matrix's second column.
  KX_MATH_API const vec2& v1() const;

  /// Return the matrix's third column.
  KX_MATH_API const vec2& v2() const;

  /// Multiply two matrices.
  /// \return A * B = AB
  KX_MATH_API mat3 operator*(const mat3&);

  /// Multiply two matrices and accumulate the result in the first operand.
  /// A *= B === A = AB
  KX_MATH_API void operator*=(const mat3&);

  /// Return a const R pointer to the matrix's data.
  KX_MATH_API operator const R*() const { return (R*)val; }

  /// Return the translation component of the matrix.
  KX_MATH_API mat3 transl() const;

  /// Return the rotation component of the matrix.
  KX_MATH_API mat3 rot() const;

  /// Create a rotation matrix.
  /// The angle of rotation is in degrees.
  KX_MATH_API static mat3 rot(R angle);

  /// Create a scale matrix.
  KX_MATH_API static mat3 scale(vec3 s);

  /// Create a scale matrix.
  KX_MATH_API static mat3 scale(R x, R y, R z);

  /// Create a translation matrix.
  KX_MATH_API static mat3 transl(vec2 offset);

  /// Create a translation matrix.
  KX_MATH_API static mat3 transl(R x, R y);

  /// Return the X-axis reflection matrix.
  KX_MATH_API static mat3 reflectx();

  /// Return the Y-axis reflection matrix.
  KX_MATH_API static mat3 reflecty();

  /// Return the Z-axis reflection matrix.
  KX_MATH_API static mat3 reflectz();

  /// Return the identity matrix.
  KX_MATH_API static mat3 id();
};

/// Invert the matrix.
KX_MATH_API mat3 inverse(const mat3&);

/// Transpose the matrix.
KX_MATH_API mat3 transpose(const mat3&);

/// Return the vector multipled by the matrix.
KX_MATH_API vec3 operator*(const mat3&, vec3);

}  // namespace kx
