#include <math/camera.h>
#include <math/frustum.h>
#include <math/mat4.h>
#include <math/vec4.h>

using namespace kx;

KX_MATH_API static Plane normalise_plane(R a, R b, R c, R d) {
  R n = norm(a, b, c);
  return Plane(-a / n, -b / n, -c / n, -d / n);
}

// See:
// http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
KX_MATH_API Frustum::Frustum(const Camera& cam) {
  mat4 M = cam.projection() * cam.inverseTransform();
  left = normalise_plane(M(3, 0) + M(0, 0), M(3, 1) + M(0, 1),
                         M(3, 2) + M(0, 2), M(3, 3) + M(0, 3));
  right = normalise_plane(M(3, 0) - M(0, 0), M(3, 1) - M(0, 1),
                          M(3, 2) - M(0, 2), M(3, 3) - M(0, 3));
  bottom = normalise_plane(M(3, 0) + M(1, 0), M(3, 1) + M(1, 1),
                           M(3, 2) + M(1, 2), M(3, 3) + M(1, 3));
  top = normalise_plane(M(3, 0) - M(1, 0), M(3, 1) - M(1, 1), M(3, 2) - M(1, 2),
                        M(3, 3) - M(1, 3));
  near = normalise_plane(M(3, 0) + M(2, 0), M(3, 1) + M(2, 1),
                         M(3, 2) + M(2, 2), M(3, 3) + M(2, 3));
  far = normalise_plane(M(3, 0) - M(2, 0), M(3, 1) - M(2, 1), M(3, 2) - M(2, 2),
                        M(3, 3) - M(2, 3));
}
