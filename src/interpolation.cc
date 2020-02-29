#include <math/determinant.h>
#include <math/interpolation.h>
#include <math/intersection.h>

using namespace kx;

kx::vec2 kx::barycentric_coordinates(const Triangle2& triangle, const vec2& p) {
  return barycentric_coordinates(triangle.p0, triangle.p1, triangle.p2, p);
}

kx::vec2 kx::barycentric_coordinates(const vec2& p0, const vec2& p1,
                                     const vec2& p2, const vec2& p) {
  vec2 v1 = p1 - p0;
  vec2 v2 = p2 - p0;
  R d = det(v1, v2);
  R s = (v2.y * (p.x - p0.x) - v2.x * (p.y - p0.y)) / d;
  R t = (v1.x * (p.y - p0.y) - v1.y * (p.x - p0.x)) / d;
  return vec2(s, t);
}

vec3 kx::barycentric_coordinates(const Quad2& q, const vec2& p) {
  return barycentric_coordinates(q.p0, q.p1, q.p2, q.p3, p);
}

vec3 kx::barycentric_coordinates(const vec2& p0, const vec2& p1, const vec2& p2,
                                 const vec2& p3, const vec2& p) {
  bool first_triangle = contains(p0, p1, p2, p);
  vec2 st = first_triangle ? barycentric_coordinates(p0, p1, p2, p)
                           : barycentric_coordinates(p0, p2, p3, p);
  return vec3(st.x, st.y, first_triangle ? 1 : -1);
}
