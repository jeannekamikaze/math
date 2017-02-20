#include <math/AABB3.h>

using namespace kx;
using namespace std;

KX_MATH_API AABB3::AABB3 (vec3* ps, unsigned n)
{
    vec3* p = ps;
    for (unsigned i = 0; i < n; ++i, ++p)
        add(*p);
}

KX_MATH_API void AABB3::add (const vec3& p)
{
    if (pmin == vec3(1) && pmax == vec3(-1)) // AABB uninitialised
    {
        pmin = p;
        pmax = p;
    }
    else
    {
        pmin.x = min(pmin.x, p.x);
        pmin.y = min(pmin.y, p.y);
        pmin.z = min(pmin.z, p.z);
        pmax.x = max(pmax.x, p.x);
        pmax.y = max(pmax.y, p.y);
        pmax.z = max(pmax.z, p.z);
    }
}

KX_MATH_API void AABB3::add (const kx::AABB3& box)
{
    add(box.pmin);
    add(box.pmax);
}
