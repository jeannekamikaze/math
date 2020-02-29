#pragma once

#include <math/quad2.h>
#include <math/quad3.h>
#include <math/triangle2.h>
#include <math/triangle3.h>

namespace kx {

/// Interpolate the triangle's vertices using the given barycentric coordinates.
/// s = parameter along triangle's p0p1 edge.
/// t = parameter along triangle's p0p2 edge.
inline vec3 interpolate(const vec3& p0, const vec3& p1, const vec3& p2,
                        const vec2& st) {
  return p0 + st.x * (p1 - p0) + st.y * (p2 - p0);
}

/// Interpolate the triangle's vertices using the given barycentric coordinates.
/// s = parameter along triangle's p0p1 edge.
/// t = parameter along triangle's p0p2 edge.
inline vec3 interpolate(const Triangle3& t, const vec2& st) {
  return interpolate(t.p0, t.p1, t.p2, st);
}

/// Interpolate the quad's vertices using the given barycentric coordinates.
/// The algorithm splits the quad into two triangles, identifies which of the
/// two triangles contains the point, and then performs a triangle interpolation
/// using the two edges of the triangle sharing the quad's p0 point.
/// u = >0: use triangle p0p1p2, <0: use triangle p0p2p3
/// s = u>0: parameter along p0p1 edge, u<0: parameter along p0p2 edge.
/// t = u>0: parameter along p0p2 edge, u<0: parameter along p0p3 edge.
inline vec3 interpolate(const vec3& p0, const vec3& p1, const vec3& p2,
                        const vec3& p3, const vec3& stu) {
  if (stu.z > 0)
    return interpolate(p0, p1, p2, vec2(stu.x, stu.y));
  else
    return interpolate(p0, p2, p3, vec2(stu.x, stu.y));
}

/// Interpolate the quad's vertices using the given barycentric coordinates.
/// The algorithm splits the quad into two triangles, identifies which of the
/// two triangles contains the point, and then performs a triangle interpolation
/// using the two edges of the triangle sharing the quad's p0 point.
/// u = >0: use triangle p0p1p2, <0: use triangle p0p2p3
/// s = u>0: parameter along p0p1 edge, u<0: parameter along p0p2 edge.
/// t = u>0: parameter along p0p2 edge, u<0: parameter along p0p3 edge.
inline vec3 interpolate(const Quad3& q, const vec3& st) {
  return interpolate(q.p0, q.p1, q.p2, q.p3, st);
}

/// Return the barycentric coordinates of the point with respect to the
/// triangle.
vec2 barycentric_coordinates(const Triangle2&, const vec2&);

/// Return the barycentric coordinates of the point with respect to the
/// triangle.
vec2 barycentric_coordinates(const vec2& p0, const vec2& p1, const vec2& p2,
                             const vec2&);

/// Return the barycentric coordinates of the point with respect to the quad.
/// Since barycentric coordinates are not uniquely defined for a quad, the
/// algorithm splits the quad into two triangles, determines which of the two
/// triangles contains the point, and returns the barycentric coordiantes of
/// the point with respect to that triangle. The third coordinate of the
/// resulting coordinates determines which of the two triangles was used.
/// u = >0: use triangle p0p1p2, <0: use triangle p0p2p3
/// s = u>0: parameter along p0p1 edge, u<0: parameter along p0p2 edge.
/// t = u>0: parameter along p0p2 edge, u<0: parameter along p0p3 edge.
vec3 barycentric_coordinates(const Quad2&, const vec2&);

/// Return the barycentric coordinates of the point with respect to the quad.
/// Since barycentric coordinates are not uniquely defined for a quad, the
/// algorithm splits the quad into two triangles, determines which of the two
/// triangles contains the point, and returns the barycentric coordiantes of
/// the point with respect to that triangle. The third coordinate of the
/// resulting coordinates determines which of the two triangles was used.
/// u = >0: use triangle p0p1p2, <0: use triangle p0p2p3
/// s = u>0: parameter along p0p1 edge, u<0: parameter along p0p2 edge.
/// t = u>0: parameter along p0p2 edge, u<0: parameter along p0p3 edge.
vec3 barycentric_coordinates(const vec2& p0, const vec2& p1, const vec2& p2,
                             const vec2& p3, const vec2&);

}  // namespace kx
