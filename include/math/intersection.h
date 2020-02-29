#pragma once

#include <math/defs.h>

// Definitions:
//
// eps: a relatively big epsilon used to compare conservatively.
//   This is used to skew comparisons to be conservative, i.e. true or false
//   depending on the context.
//   example: a - eps < b
//
// tau: a small epsilon used to compare against 0
//   example: abs(a) < tau
//   If 'a' is a small number, the above expression evaluates to true.

namespace kx {

struct AABB3;
struct AxisPlane;
struct Frustum;
struct Plane;
struct Quad2;
struct Ray3;
struct Sphere;
struct Triangle2;
struct Triangle3;
struct vec3;
struct vec2;

enum class Side { front, back, zero };

enum class PlaneIntersection { front, back, intersecting, containing };

enum class VolumeIntersection { inside, outside, intersecting };

/// Return the distance from the point to the plane.
KX_MATH_API R distanceTo(const Plane&, const vec3&);

/// Return the distance from the point to the axis-aligned plane.
KX_MATH_API R distanceTo(const AxisPlane&, const vec3&);

/// Classify the point with respect to the plane.
KX_MATH_API Side classify(const Plane& p, const vec3& v);

/// Classify the point with respect to the axis-aligned plane.
KX_MATH_API Side classify(const AxisPlane& p, const vec3& v);

/// Perform a plane-AABB intersection test.
KX_MATH_API PlaneIntersection intersect(const Plane&, const AABB3&);

/// Perform a plane-triangle intersection test.
KX_MATH_API PlaneIntersection intersect(const Plane&, const Triangle3&);

/// Perform an axis-aligned plane-triangle intersection test.
KX_MATH_API PlaneIntersection intersect(const AxisPlane&, const Triangle3&);

/// Perform a frustum-AABB intersection test.
KX_MATH_API VolumeIntersection intersect(const Frustum&, const AABB3&);

/// Intersect a ray with a plane.
KX_MATH_API bool intersect(const Ray3&, const Plane&, vec3& point);

/// Intersect a ray and an axis-aligned plane.
KX_MATH_API bool intersect(const Ray3&, const AxisPlane&, R& t);

/// Intersect a ray and a plane.
KX_MATH_API bool intersect(const Ray3&, const Plane&, R& t);

/// Intersect a ray and an AABB.
KX_MATH_API bool intersect(const Ray3&, const AABB3&, R& tmin, R& tmax);

/// Intersect a ray and a sphere.
KX_MATH_API bool intersect(const Ray3&, const Sphere&, R& tmin, R& tmax);

/// Intersect a ray and a triangle.
///
/// eps is used in deciding whether intersection exists. Set this to a
/// relatively high value if we want to err on the side of detecting
/// intersections, or to a relatively low value if we want to err on the side of
/// skipping triangles.
///
/// tau is used in comparing against 0 and should be a relatively small value.
KX_MATH_API bool intersect(const Ray3&, const Triangle3&, R& t, R eps, R tau);

/// Intersect a ray and a triangle.
KX_MATH_API bool intersect(const Ray3&, const vec3&, const vec3&, const vec3&,
                           R& t, R eps, R tau);

// Boolean intersection tests

/// Test for intersection between a ray and a plane.
KX_MATH_API bool intersect(const Ray3&, const Plane&);

/// Test for intersection between a ray and an axis-aligned plane.
KX_MATH_API bool intersect(const Ray3&, const AxisPlane&);

/// Test for intersection between a ray and an AABB.
KX_MATH_API bool intersect(const Ray3&, const AABB3&);

/// Test for intersection between a ray and a sphere.
KX_MATH_API bool intersect(const Ray3&, const Sphere&);

/// Return true if the frustum contains the point, false otherwise.
KX_MATH_API bool contains(const Frustum&, const vec3& p);

/// Return true if the frustum contains the point (x,y,z), false otherwise.
KX_MATH_API bool contains(const Frustum&, R x, R y, R z);

/// Return true if the sphere contains the point, false otherwise.
KX_MATH_API bool contains(const Sphere&, const vec3&);

/// Return true if the triangle contains the point, false otherwise.
KX_MATH_API bool contains(const Triangle2&, const vec2&);

/// Return true if the triangle contains the point, false otherwise.
KX_MATH_API bool contains(const vec2& p0, const vec2& p1, const vec2& p2,
                          const vec2& p);

/// Return true if the quad contains the point, false otherwise.
KX_MATH_API bool contains(const Quad2&, const vec2&);

/// Return true if the quad contains the point, false otherwise.
KX_MATH_API bool contains(const vec2& p0, const vec2& p1, const vec2& p2,
                          const vec2& p3, const vec2& p);

}  // namespace kx
