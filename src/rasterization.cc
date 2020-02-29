// Source:
// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

#include <math/AABB2.h>
#include <math/intersection.h>
#include <math/rasterization.h>

#include <algorithm>
#include <functional>

using namespace kx;

/// Map the point from normalised texture coordinates to image coordinates.
Texel kx::image_coordinates(const vec2& p, int width, int height) {
  int x = (int)(p.x * (R)width);
  int y = height - (int)(p.y * (R)height);
  return Texel(x, y);
}

/// Map the point from image coordinates to normalised texture coordinates.
vec2 kx::texture_coordinates(const Texel& t, int width, int height) {
  R x = t.x / (R)width;
  R y = 1.0 - (t.y / (R)height);
  return vec2(x, y);
}

namespace {

// Walk over the texels covered by the box given in texture space.
//
// The function maps the box from texture space to image space using the given
// image dimensions (width, height) and then evaluates the 'visit' function on
// the texels covered by the box.
//
// The 'visit' function takes two arguments:
//   1. The texel being visited (coordinates correspond to its top-left corner
//   in image space).
//   2. The center of the texel being visited, in texture space.
void walk(const AABB2& box, int width, int height,
          const std::function<void(const Texel&, const vec2&)>& visit) {
  // Map box from texture space to image space.
  Texel bmin = image_coordinates(box.pmin, width, height);
  Texel bmax = image_coordinates(box.pmax, width, height);
  std::swap(bmin.y, bmax.y);

  // Walk over the AABB's texels and evaluate the visit function on their
  // centers.
  vec2 texel_size = vec2(1.0 / (R)width, 1.0 / (R)height);
  vec2 offset_to_center(texel_size.x, -texel_size.y);
  std::vector<Texel> points;
  Texel p;
  for (p.y = bmin.y; p.y < bmax.y; ++p.y) {
    for (p.x = bmin.x; p.x < bmax.x; ++p.x) {
      vec2 texel_center =
          texture_coordinates(p, width, height) + offset_to_center;
      visit(p, texel_center);
    }
  }
}

}  // namespace

std::vector<Texel> kx::rasterize_triangle_contained(const Triangle2& triangle,
                                                    int width, int height) {
  // Construct the AABB around the triangle.
  AABB2 box;
  box.add(triangle.p0);
  box.add(triangle.p1);
  box.add(triangle.p2);

  std::vector<Texel> points;
  walk(box, width, height, [&](const Texel& p, const vec2& texel_center) {
    if (contains(triangle, texel_center)) points.push_back(p);
  });

  return points;
}

std::vector<Texel> kx::rasterize_quad_contained(const Quad2& quad, int width,
                                                int height) {
  // Construct the AABB around the triangle.
  AABB2 box;
  box.add(quad.p0);
  box.add(quad.p1);
  box.add(quad.p2);
  box.add(quad.p3);

  std::vector<Texel> points;
  walk(box, width, height, [&](const Texel& p, const vec2& texel_center) {
    if (contains(quad, texel_center)) points.push_back(p);
  });

  return points;
}

std::vector<Texel> kx::rasterize_aabb_overlapping(const AABB2& box, int width,
                                                  int height) {
  // Stretch the box so that its vertices match the vertices of the grid
  // spanned by the texels of the image when mapping the box to image space.
  AABB2 _box;
  vec2 texel_size = vec2(1.0 / (R)width, 1.0 / (R)height);
  _box.pmin = box.pmin;
  _box.pmax = box.pmax + texel_size;

  std::vector<Texel> points;
  walk(_box, width, height,
       [&](const Texel& p, const vec2&) { points.push_back(p); });

  return points;
}
