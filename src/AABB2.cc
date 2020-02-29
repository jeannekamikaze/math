#include <math/AABB2.h>

using namespace kx;

KX_MATH_API AABB2::AABB2(vec2* ps, unsigned n) {
  vec2* p = ps;
  for (unsigned i = 0; i < n; ++i, ++p) add(*p);
}

KX_MATH_API void AABB2::add(const vec2& p) {
  if (pmin == vec2(1) && pmax == vec2(-1))  // AABB uninitialised
  {
    pmin = p;
    pmax = p;
  } else {
    pmin.x = min(pmin.x, p.x);
    pmin.y = min(pmin.y, p.y);
    pmax.x = max(pmax.x, p.x);
    pmax.y = max(pmax.y, p.y);
  }
}

KX_MATH_API void AABB2::add(const kx::AABB2& box) {
  add(box.pmin);
  add(box.pmax);
}
