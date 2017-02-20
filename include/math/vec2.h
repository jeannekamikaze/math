#pragma once

#include <math/defs.h>

namespace kx {

/// A 2D vector.
struct vec2
{
    R x;
    R y;

    /// Construct the 0 vector.
    KX_MATH_API vec2 () : x (0), y (0) {}

    /// Construct a vector from 2 coordinates.
    KX_MATH_API vec2 (R x, R y) : x(x), y(y) {}

    /// Construct a vector from a value.
    /// x = y = val
    KX_MATH_API vec2 (R val) : x (val), y (val) {}

    /// Normalise the vector.
    KX_MATH_API void normalise ()
    {
        R n = std::sqrt(x*x + y*y);
        n = n == 0.0f ? 1.0f : n;
        x /= n;
        y /= n;
    }

    /// Return a const R pointer to the given vector's values.
    KX_MATH_API operator const R* () const { return (R*) this; }
};

/// Negate the given vector.
inline KX_MATH_API vec2 operator- (vec2 a) {
    return vec2 (-a.x, -a.y);
}

/// Add two vectors.
inline KX_MATH_API vec2 operator+ (vec2 a, vec2 b) {
    return vec2 (a.x + b.x, a.y + b.y);
}

/// Subtract two vectors.
inline KX_MATH_API vec2 operator- (vec2 a, vec2 b) {
    return vec2 (a.x - b.x, a.y - b.y);
}

/// Modulate two vectors (component-wise multiplication).
inline KX_MATH_API vec2 operator* (vec2 a, vec2 b) {
    return vec2 (a.x * b.x, a.y * b.y);
}

/// Divide two vectors component-wise.
inline KX_MATH_API vec2 operator/ (vec2 a, vec2 b) {
    return vec2 (a.x / b.x, a.y / b.y);
}

/// Add two vectors.
inline KX_MATH_API void operator += (vec2& a, vec2 b) {
    a.x += b.x;
    a.y += b.y;
}

/// Subtract two vectors.
inline KX_MATH_API void operator -= (vec2& a, vec2 b) {
    a.x -= b.x;
    a.y -= b.y;
}

/// Modulate two vectors (component-wise multiplication).
inline KX_MATH_API void operator *= (vec2& a, vec2 b) {
    a.x *= b.x;
    a.y *= b.y;
}

/// Divide two vectors component-wise.
inline KX_MATH_API void operator /= (vec2& a, vec2 b) {
    a.x /= b.x;
    a.y /= b.y;
}

/// Compare two vectors.
inline KX_MATH_API bool operator != (vec2& a, const vec2& b) {
    return a.x != b.x || a.y != b.y;
}

/// Return the vector's magnitude.
inline KX_MATH_API R norm (vec2 v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

/// Return the vector's squared magnitude.
inline KX_MATH_API R norm2 (vec2 v) {
    return v.x * v.x + v.y * v.y;
}

/// Return the distance between two points.
inline KX_MATH_API R dist (vec2 a, vec2 b) {
    vec2 v = a-b;
    return std::sqrt(v.x * v.x + v.y * v.y);
}

/// Return the squared distance between two points.
inline KX_MATH_API R dist2 (vec2 a, vec2 b) {
    vec2 v = a-b;
    return v.x * v.x + v.y * v.y;
}

/// Return the vector divided by its magnitude.
inline KX_MATH_API vec2 normalise (vec2 v) {
    R n = sqrt(v.x*v.x + v.y*v.y);
    n = n == 0.0 ? 1.0 : n;
    return vec2 (v.x / n, v.y / n);
}

/// Return vectors' dot product.
inline KX_MATH_API R dot (vec2 a, vec2 b) {
    return a.x*b.x + a.y*b.y;
}

/// Reflect the vector about a normal.
inline KX_MATH_API vec2 reflect (vec2 v, vec2 n) {
    return (-2 * dot(v,n))*n + v;
}

/// Swap the two vectors.
inline void swap (vec2& a, vec2& b) {
    vec2 tmp = a;
    a = b;
    b = tmp;
}

} // namespace kx
