#include <math/vec3.h>
#include <math/vec2.h>
#include <math/vec4.h>

using namespace kx;

KX_MATH_API vec3::vec3 (const vec2& v)
    : x(v.x), y(v.y), z(0.0f) {}

KX_MATH_API vec3::vec3 (const vec4& v)
    : x(v.x), y(v.y), z(v.z) {}
