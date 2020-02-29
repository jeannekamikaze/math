#include <math/sampling.h>
#include <algorithm>

using namespace kx;

using Rand = std::uniform_real_distribution<R>;

//
// Functions relying on the client for random number generation
//

vec3 kx::sample_hemisphere(R u, R v, R e) {
  R cos_theta = ::pow(1.f - v, 1.0f / (e + 1.0f));
  R sin_theta = sqrt(1.f - cos_theta * cos_theta);
  R phi = 2.0f * PI * u;
  R pu = sin_theta * cos(phi);
  R pv = sin_theta * sin(phi);
  R pw = cos_theta;
  return vec3(pu, pv, pw);
}

vec3 kx::sample_hemisphere(const vec3& n, R u, R v, R e) {
  vec3 w = sample_hemisphere(u, v, e);

  // Compute TBN
  vec3 t = normalise(cross(vec3(0.0034f, 1.f, 0.0071f), n));
  vec3 b = normalise(cross(n, t));

  // Map to object space
  return w.x * t + w.y * b + w.z * n;
}

std::vector<vec3> kx::sample_hemisphere(const std::vector<vec2>& square_samples,
                                        R e) {
  std::vector<vec3> samples;
  samples.reserve(square_samples.size());
  for (const vec2& p : square_samples)
    samples.push_back(sample_hemisphere(p.x, p.y, e));
  return samples;
}

vec3 kx::sample_sphere(R u, R v) {
  R theta = 2 * PI * u;
  R phi = acos(2 * v - 1);
  return vec3(cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi));
}

//
// Functions using a random number generator
//

vec3 kx::sample_hemisphere(RandGen& gen, R e) {
  Rand rand;
  R u = rand(gen);
  R v = rand(gen);
  return sample_hemisphere(u, v, e);
}

vec3 kx::sample_sphere(RandGen& gen) {
  Rand rand;
  R u = rand(gen);
  R v = rand(gen);
  return sample_sphere(u, v);
}

vec2 kx::sample_disk(RandGen& gen) {
  // Using rejection sampling
  Rand rand(-1, 1);
  vec2 p(rand(gen), rand(gen));
  while (norm2(p) > 1)  // p not in unit circle
    p = vec2(rand(gen), rand(gen));
  return p;
}

vec2 kx::sample_circle(RandGen& gen) {
  Rand rand(0, 2 * PI);
  R angle = rand(gen);
  return vec2(cos(angle), sin(angle));
}

vec2 kx::sample_semicircle(RandGen& gen) {
  Rand rand(0, PI);
  R angle = rand(gen);
  return vec2(cos(angle), sin(angle));
}

vec2 kx::sample_square(RandGen& gen) {
  Rand rand;
  return vec2(rand(gen), rand(gen));
}

//
// Functions using a random number generator, vector version
//

std::vector<vec3> kx::sample_hemisphere(RandGen& gen, int num_samples, R e) {
  std::vector<vec2> square_samples = sample_square(gen, num_samples);
  return sample_hemisphere(square_samples, e);
}

std::vector<vec3> kx::sample_sphere(RandGen& gen, int num_samples) {
  std::vector<vec3> samples(num_samples);
  for (vec3& sample : samples) sample = sample_sphere(gen);
  return samples;
}

std::vector<vec2> kx::sample_disk(RandGen& gen, int num_samples) {
  std::vector<vec2> samples(num_samples);
  for (vec2& sample : samples) sample = sample_disk(gen);
  return samples;
}

std::vector<vec2> kx::sample_circle(int num_samples) {
  // Walk around the circle taking steps of a fixed size
  std::vector<vec2> samples(num_samples);
  R step = 2 * PI / (R)num_samples;
  R a = 0.0f;
  for (int i = 0; i < num_samples; ++i, a += step) {
    samples[i].x = cos(a);
    samples[i].y = sin(a);
  }
  return samples;
}

std::vector<vec2> kx::sample_circle(RandGen& gen, int num_samples) {
  std::vector<vec2> samples = kx::sample_circle(num_samples);
  // Compute a random permutation to break the angular
  // correlation between the samples
  std::shuffle(samples.begin(), samples.end(), gen);
  return samples;
}

std::vector<vec2> kx::sample_semicircle(int num_samples) {
  // Walk around the semicircle taking steps of a fixed size
  std::vector<vec2> samples(num_samples);
  R step = PI / (R)num_samples;
  R a = 0.0f;
  for (int i = 0; i < num_samples; ++i, a += step) {
    samples[i].x = cos(a);
    samples[i].y = sin(a);
  }
  return samples;
}

std::vector<vec2> kx::sample_semicircle(RandGen& gen, int num_samples) {
  std::vector<vec2> samples = sample_semicircle(num_samples);
  // Compute a random permutation to break the angular
  // correlation between the samples
  std::shuffle(samples.begin(), samples.end(), gen);
  return samples;
}

std::vector<vec2> kx::sample_square(RandGen& gen, int num_samples) {
  std::vector<vec2> samples(num_samples);
  for (int i = 0; i < num_samples; ++i) samples[i] = sample_square(gen);
  return samples;
}

const vec2 kx::poisson_disk_64[] = {
    vec2(-0.9513874f, -0.2572531f),  vec2(-0.7081226f, -0.2925284f),
    vec2(-0.8436754f, 0.07265603f),  vec2(-0.7361445f, -0.5300386f),
    vec2(-0.4641706f, -0.4989096f),  vec2(-0.5525125f, -0.8051156f),
    vec2(-0.5275754f, -0.3107731f),  vec2(-0.7102888f, -0.1115531f),
    vec2(-0.3507241f, -0.2749718f),  vec2(-0.4596497f, -0.06777957f),
    vec2(-0.2592802f, -0.09303893f), vec2(-0.3269215f, -0.7370512f),
    vec2(-0.1967628f, -0.4045115f),  vec2(-0.1576745f, -0.602447f),
    vec2(-0.05255998f, -0.8059599f), vec2(-0.2237102f, 0.1269211f),
    vec2(0.05620234f, 0.04552704f),  vec2(-0.01783457f, -0.3361599f),
    vec2(-0.01791586f, -0.1374219f), vec2(-0.6377217f, 0.2153173f),
    vec2(-0.8682323f, 0.3331691f),   vec2(-0.4682668f, 0.406311f),
    vec2(-0.7424924f, 0.5168823f),   vec2(-0.4310941f, 0.1879879f),
    vec2(0.004823341f, -0.5199288f), vec2(-0.2881597f, 0.5322707f),
    vec2(-0.216368f, 0.337567f),     vec2(-0.5569553f, 0.580784f),
    vec2(-0.5138384f, 0.7612493f),   vec2(-0.2905928f, 0.7876921f),
    vec2(0.1856931f, -0.3646466f),   vec2(0.2537658f, -0.5409983f),
    vec2(0.2522059f, -0.1557814f),   vec2(0.01755813f, 0.3362328f),
    vec2(-0.0237584f, 0.6334502f),   vec2(-0.3621303f, -0.9163787f),
    vec2(0.5234978f, -0.5937616f),   vec2(0.2064808f, -0.7797251f),
    vec2(0.4788987f, -0.7712453f),   vec2(0.4289224f, -0.2565495f),
    vec2(-0.07641014f, -0.9843845f), vec2(0.03121825f, 0.8384359f),
    vec2(-0.1270284f, 0.9283417f),   vec2(0.1492546f, 0.5786615f),
    vec2(0.2709966f, 0.7643254f),    vec2(0.2346445f, 0.2978307f),
    vec2(0.3416433f, 0.443035f),     vec2(0.4972726f, 0.7187986f),
    vec2(0.3893609f, 0.9035504f),    vec2(0.3319246f, 0.02210116f),
    vec2(0.6055115f, -0.3545263f),   vec2(0.6794177f, -0.1226148f),
    vec2(0.3164409f, -0.9227439f),   vec2(0.736238f, -0.5313706f),
    vec2(0.4185115f, 0.2695309f),    vec2(0.8704509f, -0.2409606f),
    vec2(0.5223626f, -0.02931137f),  vec2(0.6194539f, 0.3270517f),
    vec2(0.5733821f, 0.5036592f),    vec2(0.8006178f, 0.1628258f),
    vec2(0.9085125f, -0.02186077f),  vec2(0.4075871f, -0.447026f),
    vec2(0.9100426f, 0.340688f),     vec2(0.7329741f, 0.6350853f),
};

const vec2 kx::poisson_disk_32[] = {
    vec2(-0.2619089f, 0.5490727f),   vec2(-0.4559077f, 0.05460965f),
    vec2(-0.1364069f, 0.1247343f),   vec2(-0.6564749f, 0.7305732f),
    vec2(0.1114105f, 0.3608207f),    vec2(-0.04955356f, 0.9398816f),
    vec2(0.1126182f, 0.6443138f),    vec2(0.2464153f, 0.9610599f),
    vec2(-0.3416013f, 0.9145091f),   vec2(0.4016598f, 0.7243099f),
    vec2(-0.5291048f, 0.3880215f),   vec2(0.3829289f, 0.2302893f),
    vec2(0.3434067f, -0.0842148f),   vec2(-0.002778768f, -0.3043965f),
    vec2(-0.2444881f, -0.1361146f),  vec2(0.5450797f, 0.4763397f),
    vec2(-0.852717f, 0.211937f),     vec2(-0.6877054f, -0.1175301f),
    vec2(-0.4309482f, -0.4658188f),  vec2(-0.1307276f, -0.5704473f),
    vec2(0.2784778f, -0.527334f),    vec2(-0.9684337f, -0.187813f),
    vec2(-0.7409888f, -0.4390397f),  vec2(-0.3486479f, -0.8564078f),
    vec2(-0.05303789f, -0.9629612f), vec2(0.866951f, 0.004832779f),
    vec2(0.8629471f, 0.460784f),     vec2(0.3551344f, -0.8735148f),
    vec2(0.777998f, -0.6073249f),    vec2(0.6032057f, -0.236872f),
    vec2(0.6681956f, 0.2039291f),    vec2(0.9084376f, -0.3247856f)};

const vec2 kx::poisson_disk_16[] = {
    vec2(-0.9347774f, 0.1912229f),  vec2(-0.5724283f, 0.4960014f),
    vec2(-0.7785025f, -0.445543f),  vec2(-0.4788606f, 0.08546659f),
    vec2(-0.2924632f, -0.4198908f), vec2(-0.06280077f, 0.00913774f),
    vec2(-0.1057879f, 0.462665f),   vec2(-0.3630854f, 0.8242339f),
    vec2(-0.1966231f, -0.793602f),  vec2(0.4165555f, -0.6832738f),
    vec2(0.1373055f, -0.3643214f),  vec2(0.3036709f, 0.3064243f),
    vec2(0.6994917f, 0.05268941f),  vec2(0.8555422f, -0.4490918f),
    vec2(0.1510768f, 0.8342344f),   vec2(0.7667124f, 0.6416653f)};

const vec2 kx::poisson_disk_8[] = {
    vec2(-0.181375f, 0.06780703f),  vec2(-0.7135639f, -0.2347054f),
    vec2(0.7305085f, -0.01602699f), vec2(-0.5122069f, 0.5700766f),
    vec2(0.05539552f, 0.6230494f),  vec2(-0.2359187f, -0.7726508f),
    vec2(0.5458851f, -0.59454f),    vec2(0.6381865f, 0.6441305f)};

const vec2 kx::poisson_disk_4[] = {
    vec2(-0.8548036f, 0.1176181f), vec2(0.0141604f, -0.6810168f),
    vec2(0.1922343f, 0.5596046f), vec2(0.804924f, -0.2298881f)};
