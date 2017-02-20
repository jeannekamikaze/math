#pragma once

#include <math/vec2.h>

namespace kx
{

/// A 2D triangle.
struct Triangle2
{
    vec2 p0;
    vec2 p1;
    vec2 p2;

    Triangle2 () {}

    Triangle2 (const vec2& p0, const vec2& p1, const vec2& p2)
        : p0(p0), p1(p1), p2(p2) {}
};

} // namespace kx
