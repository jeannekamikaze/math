#include <math/utils.h>
#include <cstdlib> // to resolve ambiguous std::abs() when using llvm

using namespace kx;
using namespace std;

union Floating {
    R f;
    int i;

    Floating (R _f) : f (_f) {}

    bool positive () const { return i >= 0; }
};

KX_MATH_API bool kx::R_eq (R a, R b, R eps, int ULPs)
{
    if (a == b) return true;
    else if (a*b == 0.0f) return fabs(a-b) <= eps;
    else {
        Floating x (a);
        Floating y (b);
        if (x.positive() != y.positive()) return false;
        int diff = std::abs (x.i - y.i);
        return diff <= ULPs;
    }
}

KX_MATH_API mat3 kx::qmat3 (const quat& q)
{
    R x = q.x;
    R y = q.y;
    R z = q.z;
    R w = q.w;
    R xx = x*x;
    R xy = x*y;
    R xz = x*z;
    R yy = y*y;
    R yz = y*z;
    R zz = z*z;
    R wx = w*x;
    R wy = w*y;
    R wz = w*z;

    return mat3
        ( 1- 2*yy - 2*zz, 2*xy + 2*wz    , 2*xz - 2*wy
        , 2*xy - 2*wz,    1 - 2*xx - 2*zz, 2*yz + 2*wx
        , 2*xz + 2*wy,    2*yz - 2*wx    , 1 - 2*xx - 2*yy);
}

KX_MATH_API mat4 kx::qmat4 (const quat& q)
{
    R x = q.x;
    R y = q.y;
    R z = q.z;
    R w = q.w;
    R xx = x*x;
    R xy = x*y;
    R xz = x*z;
    R yy = y*y;
    R yz = y*z;
    R zz = z*z;
    R wx = w*x;
    R wy = w*y;
    R wz = w*z;

    return mat4
        ( 1- 2*yy - 2*zz, 2*xy + 2*wz    , 2*xz - 2*wy    , 0.0f
        , 2*xy - 2*wz,    1 - 2*xx - 2*zz, 2*yz + 2*wx    , 0.0f
        , 2*xz + 2*wy,    2*yz - 2*wx    , 1 - 2*xx - 2*yy, 0.0f
        , 0.0f       ,    0.0f           , 0.0f           , 1.0f);
}

KX_MATH_API R kx::pitch_from_fwd (vec3 forward)
{
    vec3 f = vec3 (0.0f, forward.y, forward.z);
    f.normalise();
    return acos (dot(f, forward3())) * TO_DEG;
}

KX_MATH_API R kx::yaw_from_fwd (vec3 forward)
{
    vec3 f = vec3 (forward.x, 0.0, forward.z);
    f.normalise();
    return acos(dot(f, forward3())) * TO_DEG;
}
