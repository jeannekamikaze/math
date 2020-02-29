#pragma once

#include <math/mat4.h>
#include <math/spatial.h>

#undef near
#undef far

namespace kx {

/// Camera base class.
struct Camera : public Spatial {
  /// Return the camera's projection matrix.
  KX_MATH_API virtual mat4 projection() const = 0;

  /// Return the camera's inverse projection matrix.
  KX_MATH_API virtual mat4 inverseProjection() const = 0;

  /// Return the camera's near plane.
  KX_MATH_API virtual R getNear() const = 0;

  /// Return the camera's far plane.
  KX_MATH_API virtual R getFar() const = 0;
};

/// A perspective projection camera.
struct PerspectiveCamera : public Camera {
  R fovy;    ///< Vertical field of view angle.
  R aspect;  ///< Aspect ratio.
  R near;    ///< Near plane.
  R far;     ///< Far plane.

  KX_MATH_API PerspectiveCamera() : fovy(0), aspect(0), near(0), far(0) {}

  /// Construct a perspective camera.
  /// \param fovy   Vertical field of view angle.
  /// \param aspect Aspect ratio.
  /// \param near   Near plane.
  /// \param far    Far plane.
  KX_MATH_API PerspectiveCamera(R fovy, R aspect, R near, R far)
      : fovy(fovy), aspect(aspect), near(near), far(far) {}

  KX_MATH_API mat4 projection() const override {
    return mat4::perspective(fovy, aspect, near, far);
  }

  KX_MATH_API mat4 inverseProjection() const override {
    return mat4::perspectiveInverse(fovy, aspect, near, far);
  }

  KX_MATH_API R getNear() const override { return near; }

  KX_MATH_API R getFar() const override { return far; }
};

/// An orthographic projection camera.
struct OrthoCamera : public Camera {
  R left, right, bottom, top, near, far;

  KX_MATH_API OrthoCamera()
      : left(-1), right(1), bottom(-1), top(1), near(-1), far(1) {}

  KX_MATH_API OrthoCamera(R left, R right, R bottom, R top, R near, R far)
      : left(left),
        right(right),
        bottom(bottom),
        top(top),
        near(near),
        far(far) {}

  KX_MATH_API mat4 projection() const override {
    return mat4::ortho(left, right, bottom, top, near, far);
  }

  KX_MATH_API mat4 inverseProjection() const override {
    return inverse(projection());
  }

  KX_MATH_API R getNear() const override { return near; }

  KX_MATH_API R getFar() const override { return far; }
};

}  // namespace kx
