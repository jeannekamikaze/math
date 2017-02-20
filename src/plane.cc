#include <math/plane.h>
#include <math/triangle3.h>
#include <math/vec4.h>

using namespace kx;

KX_MATH_API Plane::Plane (const kx::Triangle3& triangle)
{
    vec3 v1 = triangle.p1 - triangle.p0;
    vec3 v2 = triangle.p2 - triangle.p0;
    vec3 n  = normalise(cross(v1, v2));
    a = n.x;
    b = n.y;
    c = n.z;
    d = -dot(n, triangle.p0);
}

KX_MATH_API void Plane::operator= (const vec4& v)
{
    a = v.x;
    b = v.y;
    c = v.z;
    d = v.w;
}
