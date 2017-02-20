#pragma once

#include <math/defs.h>
#include <math/vec4.h>

namespace kx {

struct vec3;

/// A 4x4 column-major matrix.
class mat4
{
    R val[4][4];

public:

    /// Construct the identity matrix.
    KX_MATH_API mat4 ();

    /// Construct a matrix from 16 values.
    KX_MATH_API mat4 (R m00, R m10, R m20, R m30,
                      R m01, R m11, R m21, R m31,
                      R m02, R m12, R m22, R m32,
                      R m03, R m13, R m23, R m33);

    /// Construct a matrix from 4 column vectors.
    KX_MATH_API mat4 (const vec4& v0,
                      const vec4& v1,
                      const vec4& v2,
                      const vec4& v3);

    /// Construct a transformation matrix from 4 vectors.
    KX_MATH_API mat4 (const vec3& right, const vec3& up, const vec3& forward, const vec3& position);

    /// Return a mutable reference to the value at the specified position.
    KX_MATH_API R& operator () (int row, int col);

    /// Access the value at the specified position.
    KX_MATH_API R operator() (int row, int col) const;

    /// Return a mutable reference to the matrix's first column.
    KX_MATH_API vec3& v0 ();

    /// Return a mutable reference to the matrix's second column.
    KX_MATH_API vec3& v1 ();

    /// Return a mutable reference to the matrix's third column.
    KX_MATH_API vec3& v2 ();

    /// Return a mutable reference to the matrix's fourth column.
    KX_MATH_API vec3& v3 ();

    /// Return the matrix's first column.
    KX_MATH_API const vec3& v0 () const;

    /// Return the matrix's second column.
    KX_MATH_API const vec3& v1 () const;

    /// Return the matrix's third column.
    KX_MATH_API const vec3& v2 () const;

    ///  Return an immutable reference to the matrix's fourth column.
    KX_MATH_API const vec3& v3 () const;

    /// Return a mutable reference to the matrix's ith column.
    KX_MATH_API vec4& column (int i);

    /// Return the matrix's ith row.
    KX_MATH_API const vec4& column (int i) const;

    /// Return a mutable reference to the matrix's ith column.
    KX_MATH_API vec4 row (int i);

    /// Return the matrix's ith row.
    KX_MATH_API const vec4 row (int i) const;

    /// Multiply two matrices.
    /// A * B = AB
    KX_MATH_API mat4 operator* (const mat4&) const;

    /// Multiply two matrices and accumulate the result in the first operand.
    /// A *= B === A = AB
    KX_MATH_API void operator*= (const mat4&);

    /// Return a const R pointer to the matrix's data.
    KX_MATH_API operator const R* () const { return (R*) val; }

    /// Return the translation component of the matrix.
    KX_MATH_API mat4 transl () const;

    /// Return the rotation component of the matrix.
    KX_MATH_API mat4 rot () const;

    /// Create an X-axis rotation matrix.
    /// \param angle The angle of rotation in degrees.
    KX_MATH_API static mat4 rotx (R angle);

    /// Create a Y-axis rotation matrix.
    /// \param angle The angle of rotation in degrees.
    KX_MATH_API static mat4 roty (R angle);

    /// Create a Z-axis rotation matrix.
    /// \param angle The angle of rotation in degrees.
    KX_MATH_API static mat4 rotz (R angle);

    /// Create a rotation matrix.
    /// angle The angle of rotation in degrees.
    /// axis  The axis of rotation.
    KX_MATH_API static mat4 rot (R angle, const vec3& axis);

    /// Create a rotation matrix.
    /// \param angle The angle of rotation in degrees.
    /// \param x     X component of the rotation axis.
    /// \param y     Y component of the rotation axis.
    /// \param z     Z component of the rotation axis.
    KX_MATH_API static mat4 rot (R angle, R x, R y, R z);

    /// Create a scale matrix.
    /// \þaram s Scale vector.
    KX_MATH_API static mat4 scale (const vec3& s);

    /// Create a scale matrix.
    /// \param sx X axis scale factor.
    /// \param sy Y axis scale factor.
    /// \param sz Z axis scale factor.
    KX_MATH_API static mat4 scale (R sx, R sy, R sz);

    /// Create a translation matrix.
    /// \param offset Translation offset.
    KX_MATH_API static mat4 transl (const vec3& offset);

    /// Create a translation matrix.
    /// \param x Translation offset along the X axis.
    /// \param y Translation offset along the Y axis.
    /// \param z Translation offset along the Z axis.
    KX_MATH_API static mat4 transl (R x, R y, R z);

    /// The X-axis reflection matrix.
    KX_MATH_API static mat4 reflectx ();

    /// The Y-axis reflection matrix.
    KX_MATH_API static mat4 reflecty ();

    /// The Z-axis reflection matrix.
    KX_MATH_API static mat4 reflectz ();

    /// The identity matrix.
    KX_MATH_API static mat4 id ();

    /// Create a transformation matrix from the given forward vector.
    KX_MATH_API static mat4 transform (vec3 forward);

    /// Create a transformation matrix.
    /// \param position The object's position.
    /// \param target   The point the object is looking at.
    KX_MATH_API static mat4 lookAt (const vec3& position, const vec3& target);

    /// Create an orthographic projection matrix.
    /// \param left   The coordinate for the left vertical clipping plane.
    /// \param right  The coordinate for the right vertical clipping plane.
    /// \param bottom The coordinate for the bottom horizontal clipping plane.
    /// \param top    The coordinate for the top horizontal clipping plane.
    /// \param near   The distance to the near clipping plane.
    /// \param far    The distance to the far clipping plane.
    KX_MATH_API static mat4 ortho (R left, R right, R bottom, R top, R near, R far);

    /// Create a perspective projection matrix.
    /// \param fovy   The vertical field of view angle in degrees.
    /// \param aspect The aspect ratio that determines the field of view in the x-direction.
    /// \param near   Distance to the near clipping plane.
    /// \param far    Distance to the far clipping plane.
    KX_MATH_API static mat4 perspective (R fovy, R aspect, R near, R far);

    /// Create the inverse of a perspective projection matrix.
    /// \param fovy   The vertical field of view angle in degrees.
    /// \param aspect The aspect ratio that determines the field of view in the x-direction.
    /// \param near   Distance to the near clipping plane.
    /// \param far    Distance to the far clipping plane.
    KX_MATH_API static mat4 perspectiveInverse (R fovy, R aspect, R near, R far);
};

/// Return the matrix's determinant.
KX_MATH_API R det (const mat4& m);

/// Invert the matrix.
KX_MATH_API mat4 inverse (const mat4& m);

/// Invert the transformation matrix.
/// This is much faster than the more general inverse() function,
/// but assumes that the matrix is of the form TR, where T is a
/// translation and R a rotation.
KX_MATH_API mat4 inverse_transform (const mat4& m);

/// Transpose the matrix.
KX_MATH_API mat4 transpose (const mat4& m);

/// Transform the vector with the matrix.
KX_MATH_API vec3 transform (const mat4&, const vec3&, R w);

/// Return the vector multiplied by the matrix.
KX_MATH_API vec4 operator* (const mat4&, const vec4&);

} // namespace kx
