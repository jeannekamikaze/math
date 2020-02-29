#pragma once

#include <math/plane.h>

namespace kx {

struct Camera;

/// A viewing frustum.
struct Frustum {
  Plane left, right, bottom, top, near, far;

  /// Construct an empty viewing frustum.
  KX_MATH_API Frustum() {}

  /// Construct a viewing frustum.
  KX_MATH_API Frustum(const Plane& left, const Plane& right,
                      const Plane& bottom, const Plane& top, const Plane& near,
                      const Plane& far)
      : left(left),
        right(right),
        bottom(bottom),
        top(top),
        near(near),
        far(far) {}

  /// Extract a viewing frustum from the camera's view-projection matrix.
  KX_MATH_API Frustum(const Camera&);
};

}  // namespace kx
