#pragma once

#include <math/mat4.h>
#include <math/vec3.h>

namespace kx {

/// An object in 3D space.
class Spatial {
  vec3 r;
  vec3 u;
  vec3 f;
  vec3 p;

 public:
  /// Construct a degenerate spatial with position 0 and direction vectors 0.
  KX_MATH_API Spatial();

  /// Construct a spatial.
  /// \param position The spatial's position.
  /// \param target   The point where the spatial is look at.
  KX_MATH_API Spatial(const vec3& position, const vec3& target);

  KX_MATH_API virtual ~Spatial() {}

  /// Displace the spatial by the given vector.
  KX_MATH_API void move(const vec3& vec);

  /// Displace the spatial by the vector (dx, dy, dz).
  KX_MATH_API void move(R dx, R dy, R dz);

  /// Move the spatial along its forward vector.
  KX_MATH_API void moveForwards(R speed);

  /// Move the spatial along its backwards vector.
  KX_MATH_API void moveBackwards(R speed);

  /// Move the spatial along its left vector.
  KX_MATH_API void moveLeft(R speed);

  /// Move the spatial along its right vector.
  KX_MATH_API void moveRight(R speed);

  /// Move the spatial along the global up vector.
  KX_MATH_API void moveUp(R speed);

  /// Move the spatial along the global down vector.
  KX_MATH_API void moveDown(R speed);

  /// Rotate the spatial about the given axis in world space.
  /// \param angle The angle of rotation in degrees.
  /// \param x     The x coordinate of the axis of rotation.
  /// \param y     The y coordinate of the axis of rotation.
  /// \param z     The z coordinate of the axis of rotation.
  KX_MATH_API void rotate(R angle, R x, R y, R z);

  /// Rotate the spatial about the given axis in world space.
  /// \param angle The angle of rotation in degrees.
  /// \param axis  The axis of rotation.
  KX_MATH_API void rotate(R angle, vec3 axis) {
    rotate(angle, axis.x, axis.y, axis.z);
  }

  /// Rotate the spatial about its local y axis.
  /// \param angle The angle of rotation in degrees.
  KX_MATH_API void yaw(const R angle);

  /// Rotate the spatial about its local x axis.
  /// \param angle The angle of rotation in degrees.
  KX_MATH_API void pitch(const R angle);

  /// Rotate the spatial about its local z axis.
  /// \param angle The angle of rotation in degrees.
  KX_MATH_API void roll(const R angle);

  /// Set the spatial's x coordinate.
  KX_MATH_API void setx(R x);

  /// Set the spatial's y coordinate.
  KX_MATH_API void sety(R y);

  /// Set the spatial's y coordinate.
  KX_MATH_API void setz(R z);

  /// Set the spatial's position.
  KX_MATH_API void setPosition(R x, R y, R z);

  /// Set the spatial's position.
  KX_MATH_API void setPosition(const vec3& v);

  /// Set the spatial's forward vector.
  KX_MATH_API void setForward(R x, R y, R z);

  /// Set the spatial's forward vector.
  KX_MATH_API void setForward(const vec3& forward);

  /// Set the spatial's transformation matrix.
  KX_MATH_API void setTransform(const mat4& transform);

  /// Make the spatial look at the given target.
  KX_MATH_API void lookAt(R x, R y, R z);

  /// Make the spatial look at the given target.
  KX_MATH_API void lookAt(const vec3& target);

  /// Make the spatial look at the given target.
  KX_MATH_API void lookAt(const Spatial&);

  /// Make the spatial orbit around the given target.
  /// \param x       Target x coordinate.
  /// \param y       Target y coordinate.
  /// \param z       Target z coordinate.
  /// \param radius  Radial distance.
  /// \param azimuth Azimuthal (horizontal) angle.
  /// \param zenith  Polar (vertical) angle.
  KX_MATH_API void orbit(R x, R y, R z, R radius, R azimuth, R zenith);

  /// Make the spatial orbit around the given target.
  /// \param target  Target position.
  /// \param radius  Radial distance.
  /// \param azimuth Azimuthal (horizontal) angle.
  /// \param zenith  Polar (vertical) angle.
  KX_MATH_API void orbit(const vec3& target, R radius, R azimuth, R zenith);

  /// Make the spatial orbit around the given target.
  /// \param target  Target spatial.
  /// \param radius  Radial distance.
  /// \param azimuth Azimuthal (horizontal) angle.
  /// \param zenith  Polar (vertical) angle.
  KX_MATH_API void orbit(const Spatial& target, R radius, R azimuth, R zenith);

  /// Return the spatial's position.
  KX_MATH_API const vec3& pos() const;

  /// Return the spatial's forward vector.
  KX_MATH_API const vec3& fwd() const;

  /// Return the spatial's right vector.
  KX_MATH_API const vec3& right() const;

  /// Return the spatial's up vector.
  KX_MATH_API const vec3& up() const;

  /// Return the spatial's transformation matrix (from spatial to world
  /// coordinates).
  KX_MATH_API mat4 transform() const;

  /// Return the spatial's inverse transformation matrix (from world to spatial
  /// coordinates).
  KX_MATH_API mat4 inverseTransform() const;
};

}  // namespace kx
