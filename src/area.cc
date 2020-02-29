#include <math/area.h>

using namespace kx;

R kx::area(const Triangle3& t) { return area(t.p0, t.p1, t.p2); }

R kx::area(const vec3& p0, const vec3& p1, const vec3& p2) {
  vec3 v1 = p1 - p0;
  vec3 v2 = p2 - p0;
  vec3 normal = cross(v1, v2);
  return norm(normal) / 2;
}

R kx::area(const Quad3& q) { return area(q.p0, q.p1, q.p2, q.p3); }

R kx::area(const vec3& p0, const vec3& p1, const vec3& p2, const vec3& p3) {
  return area(p0, p1, p2) + area(p0, p2, p3);
}
