#pragma once

#include <math/AABB2.h>
#include <math/quad2.h>
#include <math/texel.h>
#include <math/triangle2.h>

#include <vector>

namespace kx {

/// Map the point from normalised texture coordinates to image coordinates.
Texel image_coordinates(const vec2& p, int width, int height);

/// Map the point from image coordinates to normalised texture coordinates.
vec2 texture_coordinates(const Texel& t, int width, int height);

// Rasterization
//
// Conventions:
//
// - The input geometry's points must be in normalised textured coordinates:
// [0,1]
//
// - The origin in normalised texture coordinates (input) is in the bottom-left
// corner.
//
// - The origin in image space (output) is in the top-left corner.
//
// - For 'contained' algorithms: the rasterization returns all texels that have
//   their center contained in the input geometry.
//
// - For 'overlapping' algorithms: the rasterization returns all texels that
//   are overlapped by the input geometry.

/// Rasterize the triangle using the barycentric algorithm.
std::vector<Texel> rasterize_triangle_contained(const Triangle2&, int width,
                                                int height);

/// Rasterize the quad using the barycentric algorithm.
std::vector<Texel> rasterize_quad_contained(const Quad2&, int width,
                                            int height);

/// Rasterize the AABB.
std::vector<Texel> rasterize_aabb_overlapping(const AABB2&, int width,
                                              int height);

}  // namespace kx
