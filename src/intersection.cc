#include <math/intersection.h>
#include <math/AABB3.h>
#include <math/axis_plane.h>
#include <math/determinant.h>
#include <math/frustum.h>
#include <math/plane.h>
#include <math/quad2.h>
#include <math/ray3.h>
#include <math/sphere.h>
#include <math/triangle2.h>
#include <math/triangle3.h>

#include <limits>

using namespace kx;
using namespace std;

KX_MATH_API static int sgn0 (R x)
{
    if (x == 0) return 0;
    else if (x > 0) return 1;
    else return -1;
}

KX_MATH_API R kx::distanceTo (const Plane& p, const vec3& v)
{
    return p.a*v.x + p.b*v.y + p.c*v.z + p.d;
}

KX_MATH_API R kx::distanceTo (const AxisPlane& p, const vec3& v)
{
    return ((R*)&v)[p.axis] - p.ct;
}

KX_MATH_API Side kx::classify (const Plane& p, const vec3& v)
{
    R d = distanceTo(p,v);
    if (d > 0) return Side::front;
    else if (d < 0) return Side::back;
    else return Side::zero;
}

KX_MATH_API Side kx::classify (const AxisPlane& p, const vec3& v)
{
    R d = distanceTo(p,v);
    if (d > 0) return Side::front;
    else if (d < 0) return Side::back;
    else return Side::zero;
}

KX_MATH_API PlaneIntersection kx::intersect (const Plane& p, const AABB3& box)
{
    vec3 n = vec3(p.a, p.b, p.c);
    vec3 c = (box.pmax + box.pmin) / 2.0;
    vec3 h = (box.pmax - box.pmin) / 2.0;
    R e    = h.x * abs(n.x) + h.y * abs(n.y) + h.z * abs(n.z);
    R s    = dot(c,n) + p.d;
    if (s - e > 0) return PlaneIntersection::back;
    if (s + e < 0) return PlaneIntersection::front;
    return PlaneIntersection::intersecting;
}

KX_MATH_API PlaneIntersection kx::intersect (const Plane& p, const Triangle3& t)
{
    int s0 = sgn0(distanceTo(p, t.p0));
    int s1 = sgn0(distanceTo(p, t.p1));
    int s2 = sgn0(distanceTo(p, t.p2));
    int s  = s0+s1+s2;
    switch (s)
    {
    case  1: return PlaneIntersection::intersecting;
    case -1: return PlaneIntersection::intersecting;
    case -3: return PlaneIntersection::back;
    case  3: return PlaneIntersection::front;
    default: return s > 0 ? PlaneIntersection::front
                          : (s < 0 ? PlaneIntersection::back
                                   : PlaneIntersection::containing);
    }
}

KX_MATH_API PlaneIntersection kx::intersect (const AxisPlane& p, const Triangle3& t)
{
    int s0 = sgn0(distanceTo(p, t.p0));
    int s1 = sgn0(distanceTo(p, t.p1));
    int s2 = sgn0(distanceTo(p, t.p2));
    int s  = s0+s1+s2;
    switch (s)
    {
    case  1: return PlaneIntersection::intersecting;
    case -1: return PlaneIntersection::intersecting;
    case -3: return PlaneIntersection::back;
    case  3: return PlaneIntersection::front;
    default: return s > 0 ? PlaneIntersection::front
                          : (s < 0 ? PlaneIntersection::back
                                   : PlaneIntersection::containing);
    }
}

KX_MATH_API VolumeIntersection kx::intersect (const Frustum& f, const AABB3& box)
{
    bool is_intersecting = false;
    PlaneIntersection i;

    i = intersect(f.left, box);
    if (i == PlaneIntersection::back) return VolumeIntersection::outside;
    else if (i == PlaneIntersection::intersecting) is_intersecting = true;

    i = intersect(f.right, box);
    if (i == PlaneIntersection::back) return VolumeIntersection::outside;
    else if (i == PlaneIntersection::intersecting) is_intersecting = true;

    i = intersect(f.bottom, box);
    if (i == PlaneIntersection::back) return VolumeIntersection::outside;
    else if (i == PlaneIntersection::intersecting) is_intersecting = true;

    i = intersect(f.top, box);
    if (i == PlaneIntersection::back) return VolumeIntersection::outside;
    else if (i == PlaneIntersection::intersecting) is_intersecting = true;

    i = intersect(f.near, box);
    if (i == PlaneIntersection::back) return VolumeIntersection::outside;
    else if (i == PlaneIntersection::intersecting) is_intersecting = true;

    i = intersect(f.far, box);
    if (i == PlaneIntersection::back) return VolumeIntersection::outside;
    else if (i == PlaneIntersection::intersecting) is_intersecting = true;

    if (is_intersecting) return VolumeIntersection::intersecting;
    else return VolumeIntersection::inside;
}

KX_MATH_API bool kx::intersect (const Ray3& r, const Plane& p, vec3& point)
{
    vec3 N(p.a, p.b, p.c);
    R denom = dot(N, r.dir);
    if (denom == 0.0) return false;
    R t = (dot(-N, r.pos) - p.d) / denom;
    point = r(t);
    return true;
}

KX_MATH_API bool kx::intersect (const Ray3& r, const Plane& p, R& t)
{
    vec3 pnormal = vec3(p.a, p.b, p.c);
    R denom = dot (pnormal, r.dir);
    if (denom == 0.0f) return false;
    t = (dot(-pnormal, r.pos) - p.d) / denom;
    return t >= 0.0f;
}

KX_MATH_API bool kx::intersect (const Ray3& r, const AxisPlane& p, R& t)
{
    int d = p.axis;
    if (r.dir[d] == 0) return false;
    t = (p.ct - r.pos[d]) / r.dir[d];
    return true;
}

KX_MATH_API bool kx::intersect (const Ray3& r, const AABB3& a, R& tmin, R& tmax)
{
    tmin = R_MIN;
    tmax = R_MAX;
    if (r.dir.x != 0.0f)
    {
        R t0 = (a.pmin.x - r.pos.x) / r.dir.x;
        R t1 = (a.pmax.x - r.pos.x) / r.dir.x;
        tmin = max(tmin, min(t0,t1));
        tmax = min(tmax, max(t0,t1));
    }
    if (r.dir.y != 0.0f)
    {
        R t0 = (a.pmin.y - r.pos.y) / r.dir.y;
        R t1 = (a.pmax.y - r.pos.y) / r.dir.y;
        tmin = max(tmin, min(t0,t1));
        tmax = min(tmax, max(t0,t1));
    }
    if (r.dir.z != 0.0f)
    {
        R t0 = (a.pmin.z - r.pos.z) / r.dir.z;
        R t1 = (a.pmax.z - r.pos.z) / r.dir.z;
        tmin = max(tmin, min(t0,t1));
        tmax = min(tmax, max(t0,t1));
    }
    return tmax >= 0 && tmin <= tmax;
}

KX_MATH_API bool kx::intersect (const Ray3& r, const Sphere& s, R& tmin, R& tmax)
{
    vec3 l = s.center - r.pos;
    R l2 = norm2 (l);
    R r2 = s.radius2;
    if (l2 < r2) return true;
    R p = dot (l, r.dir);
    if (p < 0.0f) return false;
    R a2 = l2 - p*p;
    if (a2 < r2)
    {
        R k = sqrt(r2 - a2);
        tmin = p-k;
        tmax = p+k;
        return true;
    }
    return false;
}

KX_MATH_API bool kx::intersect (const Ray3& r, const Triangle3& tri, R& t, R eps, R tau)
{
    return intersect(r, tri.p0, tri.p1, tri.p2, t, eps, tau);
}

KX_MATH_API bool kx::intersect (const Ray3& r, const vec3& p0, const vec3& p1, const vec3& p2, R& t, R eps, R tau)
{
    vec3 a = p0 - p2;
    vec3 b = p1 - p2;
    vec3 c = r.pos  - p2;
    vec3 s = cross(a, r.dir);
    vec3 e = cross(b,c);
    R sb = dot(s,b);
    if (abs(sb) < tau) return false;
    R isb = 1.0 / sb;
    R u  = dot(e, r.dir)*isb;
    R v  = dot(s,c)*isb;
    R tt = dot(e,a)*isb;
    // Use the first condition to turn on backface culling
    //if (sb > 0 && u >= 0 && v >= 0 && u+v <= 1 && tt >= 0)
    if (u + eps >= 0 && v + eps >= 0 && u+v - eps <= 1 && tt + eps >= 0)
    {
        t = tt;
        return true;
    }
    else return false;
}


//
// Boolean intersection tests
//


KX_MATH_API bool kx::intersect (const Ray3& r, const Plane& p)
{
    R t;
    return intersect(r, p, t);
}

KX_MATH_API bool kx::intersect (const Ray3& r, const AxisPlane& p)
{
    R t;
    return intersect(r, p, t);
}

KX_MATH_API bool kx::intersect (const Ray3& r, const AABB3& a)
{
    R tmin = R_MIN;
    R tmax = R_MAX;
    return intersect(r, a, tmin, tmax);
}

KX_MATH_API bool kx::intersect (const Ray3& r, const Sphere& s)
{
    vec3 l = s.center - r.pos;
    R l2 = norm2 (l);
    R r2 = s.radius2;
    if (l2 < r2) return true;
    R p = dot (l, r.dir);
    if (p < 0.0f) return false;
    R a2 = l2 - p*p;
    return a2 < r2;
}

KX_MATH_API bool kx::contains (const Frustum& f, const vec3& p)
{
    return  classify(f.left,   p) == Side::front &&
            classify(f.right,  p) == Side::front &&
            classify(f.bottom, p) == Side::front &&
            classify(f.top,    p) == Side::front &&
            classify(f.near,   p) == Side::front &&
            classify(f.far,    p) == Side::front;
}

KX_MATH_API bool kx::contains (const Frustum& f, R x, R y, R z)
{
    return contains(f, vec3(x,y,z));
}

KX_MATH_API bool kx::contains (const Sphere& s, const vec3& p)
{
    return norm2(p - s.center) < s.radius2;
}

KX_MATH_API bool kx::contains (const Triangle2& tri, const vec2& p)
{
    return contains(tri.p0, tri.p1, tri.p2, p);
}

KX_MATH_API bool kx::contains (const vec2& p0, const vec2& p1, const vec2& p2, const vec2& p)
{
    vec2 v1 = p1-p0;
    vec2 v2 = p2-p0;
    R d = det(v1,v2);
    R s = (v2.y*(p.x-p0.x) - v2.x*(p.y-p0.y)) / d;
    R t = (v1.x*(p.y-p0.y) - v1.y*(p.x-p0.x)) / d;
    return s >= 0 && t >= 0 && (s+t) <= 1;
}

KX_MATH_API bool kx::contains (const Quad2& quad, const vec2& p)
{
    return contains(quad.p0, quad.p1, quad.p2, quad.p3, p);
}

KX_MATH_API bool kx::contains (const vec2& p0, const vec2& p1, const vec2&, const vec2& p3, const vec2& p)
{
    // This is like contains(triangle, p), except that the last condition is
    // (s+t) <= 2 instead of (s+t) <= 1 and edge p0p3 is used as the second vector
    // instead of p0p2.
    vec2 v1 = p1-p0;
    vec2 v2 = p3-p0;
    R d = det(v1,v2);
    R s = (v2.y*(p.x-p0.x) - v2.x*(p.y-p0.y)) / d;
    R t = (v1.x*(p.y-p0.y) - v1.y*(p.x-p0.x)) / d;
    return s >= 0 && t >= 0 && (s+t) <= 2;
}
