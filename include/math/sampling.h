#pragma once

#include <math/vec2.h>
#include <math/vec3.h>

#include <vector>
#include <random>

/** @defgroup sampling Sampling Functions
 * This module provides various sampling functions.
 *
 * For functions sampling the unit hemisphere, the following
 * coordinate system is used:
 *
 *     w = z
 *     |
 *     |
 *     |
 *     |
 *     ---------- v = y
 *    /
 *   /
 *  /
 * u = x
 *
 * These functions also take a skew factor e >= 1. The skew factor determines
 * whether the resulting samples are uniformly distributed or whether they
 * are skewed towards the tip of the hemisphere:
 *
 * e = 1 generates a uniform distribution.
 * e > 1 skews samples towards z.
 *
 * @{
 */

namespace kx
{

using RandGen = std::mt19937;

//
// Functions relying on the client for random number generation
//

/// Sample the consine-weighted, unit Z-oriented hemisphere (tangent space).
/// (u,v) are two random numbers in [0,1].
/// e >= 1 is the skew factor.
vec3 sample_hemisphere (R u, R v, R e = 1);

/// Sample the consine-weighted, normal-oriented unit hemisphere (object space).
/// (u,v) are two random numbers in [0,1].
/// e >= 1 is the skew factor.
vec3 sample_hemisphere (const vec3& n, R u, R v, R e = 1);

/// Sample the consine-weighted, Z-oriented hemisphere (tangent space).
/// This function maps samples in the unit square to samples in the unit hemisphere.
/// The resulting distribution has the same properties as the input one (for e=1),
/// so if the square samples are uniformly distributed, the hemisphere samples are
/// also uniformly distributed.
std::vector<vec3> sample_hemisphere (const std::vector<vec2>& square_samples, R e = 1);

/// Uniformly sample the unit sphere.
vec3 sample_sphere (R u, R v);

//
// Functions using a random number generator
//

/// Sample the cosine-weighted, unit Z-oriented hemisphere.
vec3 sample_hemisphere (RandGen&, R e = 1);

/// Sample the unit sphere.
vec3 sample_sphere (RandGen&);

/// Sample the unit disk.
vec2 sample_disk (RandGen&);

/// Sample the unit circle.
vec2 sample_circle (RandGen&);

/// Sample the unit circle.
vec2 sample_semicircle (RandGen&);

/// Sample the unity square.
vec2 sample_square (RandGen&);

//
// Functions using a random number generator, vector version
//

/// Sample the cosine-weighted, unit Z-oriented hemisphere (tangent space).
std::vector<vec3> sample_hemisphere (RandGen&, int num_samples, R e = 1);

/// Sample the unit sphere.
std::vector<vec3> sample_sphere (RandGen&, int num_samples);

/// Sample the unit disk.
std::vector<vec2> sample_disk (RandGen&, int num_samples);

/// Sample the unit circle.
/// This produces 'num_samples' uniformly distributed samples by walking
/// along the perimeter of the unit circle taking steps of a fixed size.
std::vector<vec2> sample_circle (int num_samples);

/// Sample the unit circle.
/// Like the above, but computes a random permutation of the samples to break
/// the angular correlation between them.
std::vector<vec2> sample_circle (RandGen&, int num_samples);

/// Sample the unit semicircle.
std::vector<vec2> sample_semicircle (int num_samples);

/// Sample the unit semicircle.
/// Like the above, but computes a random permutation of the samples to break
/// the angular correlation between them.
std::vector<vec2> sample_semicircle (RandGen&, int num_samples);

/// Sample the unit square.
std::vector<vec2> sample_square (RandGen&, int num_samples);

/// Poisson disk, 64 samples.
extern const vec2 poisson_disk_64[64];

/// Poisson disk, 32 samples.
extern const vec2 poisson_disk_32[32];

/// Poisson disk, 16 samples.
extern const vec2 poisson_disk_16[16];

/// Poisson disk, 8 samples.
extern const vec2 poisson_disk_8[8];

/// Poisson disk, 4 samples.
extern const vec2 poisson_disk_4[4];

} // namespace kx

/** @} */
