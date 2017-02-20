#pragma once

#include <math/defs.h>

namespace kx {

struct vec2;
struct vec4;

/// A 3D vector.
struct vec3
{
    R x, y, z;

    /// Construct the 0 vector.
    KX_MATH_API vec3 ()
        : x (0), y (0), z (0) {}

    /// Construct a vector from 3 coordinates.
    KX_MATH_API vec3 (R _x, R _y, R _z)
        : x (_x), y (_y), z (_z) {}

    /// Construct a vector from a value.
    /// x = y = z = val
    KX_MATH_API vec3 (R val)
        : x (val), y (val), z (val) {}

    /// Construct a 3D vector from a 2D one, with z = 0.
    KX_MATH_API vec3 (const vec2&);

    /// Project a 4D vector onto w=0.
    KX_MATH_API vec3 (const vec4&);

    /// Normalise the vector.
    KX_MATH_API vec3& normalise () {
        R n = sqrt(x*x + y*y + z*z);
        n = n == 0.0f ? 1.0f : n;
        x /= n;
        y /= n;
        z /= n;
        return *this;
    }

    /// Return a const R pointer to the given vector's values.
    KX_MATH_API operator const R* () const { return (R*) this; }

    /// Return the vector's ith coordinate.
    KX_MATH_API R operator[] (int i) const {
        return ((R*)this)[i];
    }

    /// Return the vector's ith coordinate.
    KX_MATH_API R& operator[] (int i) {
        return ((R*)this)[i];
    }
};

/// Negate the given vector.
inline KX_MATH_API vec3 operator- (const vec3& v) {
    return vec3 (-v.x, -v.y, -v.z);
}

/// Add two vectors.
inline KX_MATH_API vec3 operator+ (const vec3& a, const vec3& b) {
    return vec3 (a.x + b.x, a.y + b.y, a.z + b.z);
}

/// Subtract two vectors.
inline KX_MATH_API vec3 operator- (vec3 a, vec3 b) {
    return vec3 (a.x - b.x, a.y - b.y, a.z - b.z);
}

/// Modulate two vectors (component-wise multiplication).
inline KX_MATH_API vec3 operator* (const vec3& a, const vec3& b) {
    return vec3 (a.x * b.x, a.y * b.y, a.z * b.z);
}

/// Divide two vectors component-wise.
inline KX_MATH_API vec3 operator/ (const vec3& a, const vec3& b) {
    return vec3 (a.x / b.x, a.y / b.y, a.z / b.z);
}

/// Add two vectors.
inline KX_MATH_API void operator += (vec3& a, const vec3& b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
}

/// Subtract two vectors.
inline KX_MATH_API void operator -= (vec3& a, const vec3& b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
}

/// Modulate two vectors (component-wise multiplication).
inline KX_MATH_API void operator *= (vec3& a, const vec3& b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
}

/// Divide two vectors component-wise.
inline KX_MATH_API void operator /= (vec3& a, const vec3& b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
}

/// Compare two vectors.
inline KX_MATH_API bool operator != (const vec3& a, const vec3& b) {
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

/// Compare two vectors.
inline KX_MATH_API bool operator == (const vec3& a, const vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

/// Compare two vectors.
inline KX_MATH_API bool operator< (const vec3& a, const vec3& b)
{
    return (a.x < b.x) || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z);
}

/// Return the sign of the vector.
inline KX_MATH_API vec3 sign (const vec3& a) {
    return vec3(sign(a.x), sign(a.y), sign(a.z));
}

/// Return the vector's magnitude.
inline KX_MATH_API R norm (const vec3& v) {
    return sqrt (v.x * v.x + v.y * v.y + v.z * v.z);
}

/// Return the vector's magnitude.
inline KX_MATH_API R norm (R x, R y, R z) {
    return sqrt (x*x + y*y + z*z);
}

/// Return the vector's squared magnitude.
inline KX_MATH_API R norm2 (const vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

/// Return the distance between two points.
inline KX_MATH_API R dist (const vec3& a, const vec3& b) {
    vec3 v = a-b;
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/// Return the squared distance between two points.
inline KX_MATH_API R dist2 (const vec3& a, const vec3& b) {
    vec3 v = a-b;
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

/// Return the given vector divided by its magnitude.
inline KX_MATH_API vec3 normalise (vec3 v) {
    R n = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    n = n == 0.0f ? 1.0f : n;
    return vec3 (v.x / n, v.y / n, v.z / n);
}

/// Return the given vector divided by its magnitude.
inline KX_MATH_API vec3 normalise (R x, R y, R z) {
    R n = sqrt(x*x + y*y + z*z);
    n = n == 0.0f ? 1.0f : n;
    return vec3 (x / n, y / n, z / n);
}

/// Return given vectors' dot product.
inline KX_MATH_API R dot (vec3 a, vec3 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/// Return the given vectors' cross product.
inline KX_MATH_API vec3 cross (vec3 a, vec3 b) {
    return vec3
            (a.y*b.z - a.z*b.y
             ,a.z*b.x - a.x*b.z
             ,a.x*b.y - a.y*b.x);
}

/// Reflect the vector about a normal.
inline KX_MATH_API vec3 reflect (vec3 v, vec3 n) {
    return v - 2*dot(v,n)*n;
}

/// Refract the vector about a normal.
inline KX_MATH_API vec3 refract (vec3 v, vec3 n, R e)
{
    R k = 1.0f - e * e * (1.0f - dot(n, v) * dot(n, v));
    if (k < 0.0)
        return vec3(0);
    else
        return e * v - (e * dot(n, v) + sqrt(k)) * n;
}

/// Elevate the vector to a power.
inline KX_MATH_API vec3 vpow (const vec3& a, R p)
{
    return vec3(::pow(a.x,p), ::pow(a.y,p), ::pow(a.z,p));
}

/// Return the component-wise minimum.
inline KX_MATH_API vec3 min (const vec3& a, const vec3& b)
{
    return vec3(min(a.x,b.x), min(a.y,b.y), min(a.z,b.z));
}

/// Return the component-wise maximum.
inline KX_MATH_API vec3 max (const vec3& a, const vec3& b)
{
    return vec3(max(a.x,b.x), max(a.y,b.y), max(a.z,b.z));
}

/// Swap the two vectors.
inline void swap (vec3& a, vec3& b) {
    vec3 tmp = a;
    a = b;
    b = tmp;
}

/// The (1, 0, 0) vector.
KX_MATH_API inline vec3 right3 () { return vec3 (1.0f, 0.0f, 0.0f); }

/// The (0, 1, 0) vector.
KX_MATH_API inline vec3 up3 () { return vec3 (0.0f, 1.0f, 0.0f); }

/// The (0, 0, -1) vector.
KX_MATH_API inline vec3 forward3 () { return vec3 (0.0f, 0.0f, -1.0f); }

/// The (0, 0, 0) vector.
KX_MATH_API inline vec3 zero3 () { return vec3 (0.0f, 0.0f, 0.0f); }

} // namespace kx
