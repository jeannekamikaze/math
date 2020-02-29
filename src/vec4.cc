#include <math/vec3.h>
#include <math/vec4.h>

using namespace kx;
using namespace std;

KX_MATH_API vec4::vec4(const vec3& v, R w) : x(v.x), y(v.y), z(v.z), w(w) {}

KX_MATH_API void vec4::normalise() {
  R n = sqrt(x * x + y * y + z * z + w * w);
  n = n == 0.0f ? 1.0f : n;
  x /= n;
  y /= n;
  z /= n;
  w /= n;
}

KX_MATH_API vec4 kx::operator-(vec4 a) { return vec4(-a.x, -a.y, -a.z, -a.w); }

KX_MATH_API vec4 kx::operator+(vec4 a, vec4 b) {
  return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

KX_MATH_API vec4 kx::operator-(vec4 a, vec4 b) {
  return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

KX_MATH_API vec4 kx::operator*(vec4 a, vec4 b) {
  return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

KX_MATH_API vec4 kx::operator/(vec4 a, vec4 b) {
  return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

KX_MATH_API void kx::operator+=(vec4& a, vec4 b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
}

KX_MATH_API void kx::operator-=(vec4& a, vec4 b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
}

KX_MATH_API void kx::operator*=(vec4& a, vec4 b) {
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  a.w *= b.w;
}

KX_MATH_API void kx::operator/=(vec4& a, vec4 b) {
  a.x /= b.x;
  a.y /= b.y;
  a.z /= b.z;
  a.w /= b.w;
}

KX_MATH_API vec4 kx::normalise(const vec4& v) {
  R n = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
  n = n == 0.0 ? 1.0 : n;
  return vec4(v.x / n, v.y / n, v.z / n, v.w / n);
}

KX_MATH_API R kx::norm(vec4 v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

KX_MATH_API R kx::norm2(vec4 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}
