#pragma once

//
// Configuration macros:
//
// KX_MATH_FLOAT
//   - Use floats instead of doubles for real types (R).
//
// NOMINMAX
//   - Necessary on Windows to disable min() and max() macros.
//

#ifndef __CUDA_ARCH__      // host code
#define _USE_MATH_DEFINES  // necessary on Windows for constants like M_PI
#include <cmath>
#endif

#include <cfloat>

namespace kx {

#ifdef KX_MATH_FLOAT
using R = float;
#else
using R = double;
#endif

// Cuda-specific macros
#ifdef __CUDACC__
#define KX_MATH_API __host__ __device__
#else
#define KX_MATH_API
#endif

#define PI 3.14159265359f
#define INV_PI 0.31830988618f

/// Radians per degree.
#define TO_RAD (PI / 180.0f)

/// Degrees per radian.
#define TO_DEG (180.0f / PI)

#ifndef __CUDA_ARCH__  // host code

// inline R sin (R x) { return std::sin(x); }
// inline R cos (R x) { return std::cos(x); }
// inline R tan (R x) { return std::tan(x); }
// inline R pow (R x, R e) { return std::pow(x,e); }
// inline R sqrt (R x) { return std::sqrt(x); }
#ifdef KX_MATH_FLOAT
inline R min(R a, R b) { return std::fminf(a, b); }
inline R max(R a, R b) { return std::fmaxf(a, b); }
#else   // doubles
inline R min(R a, R b) { return fmin(a, b); }
inline R max(R a, R b) { return fmax(a, b); }
#endif  // KX_MATH_FLOAT

#else  // device code

#ifdef KX_MATH_FLOAT
inline __device__ R sin(R x) { return sinf(x); }
inline __device__ R cos(R x) { return cosf(x); }
inline __device__ R tan(R x) { return tanf(x); }
inline __device__ R pow(R x, R e) { return powf(x, e); }
inline __device__ R sqrt(R x) { return sqrtf(x); }
inline __device__ R min(R a, R b) { return fminf(a, b); }
inline __device__ R max(R a, R b) { return fmaxf(a, b); }
#else   // doubles
inline __device__ R min(R a, R b) { return fmin(a, b); }
inline __device__ R max(R a, R b) { return fmax(a, b); }
#endif  // KX_MATH_FLOAT

#endif  // __CUDA_ARCH__

inline KX_MATH_API R abs(R x) { return x >= 0.0 ? x : -x; }
inline KX_MATH_API R clamp(R x, R low, R high) {
  return max(low, min(high, x));
}
inline KX_MATH_API R sq(R x) { return x * x; }
inline KX_MATH_API R sign(R x) {
  if (x < 0)
    return -1;
  else if (x > 0)
    return 1;
  else
    return 0;
}
inline KX_MATH_API R lerp(R a, R b, R t) { return a + (b - a) * t; }

#ifdef KX_MATH_FLOAT
#define R_MAX DBL_MAX
#define R_MIN DBL_MIN
#else  // doubles
#define R_MAX FLT_MAX
#define R_MIN FLT_MIN
#endif  // KX_MATH_FLOAT

}  // namespace kx
