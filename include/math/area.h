#pragma once

#include <math/quad3.h>
#include <math/triangle3.h>

namespace kx {

/// Return the area of the triangle.
R area (const Triangle3&);

/// Return the area of the triangle defined by p0,p1,p2.
R area (const vec3& p0, const vec3& p1, const vec3& p2);

/// Return the area of the quad.
R area (const Quad3&);

/// Return the area of the quad defined by p0,p1,p2,p3.
R area (const vec3& p0, const vec3& p1, const vec3& p2, const vec3& p3);

} // namespace kx
