#include <math/spatial.h>

using namespace kx;
using namespace std;

KX_MATH_API Spatial::Spatial ()
    : r (right3()), u (up3()), f (forward3()) {}

KX_MATH_API Spatial::Spatial (const vec3& pos, const vec3& target)
{
    setPosition (pos);
    lookAt (target);
}

KX_MATH_API void Spatial::move (const vec3& direction)
{
    p += direction;
}

KX_MATH_API void Spatial::move (R dx, R dy, R dz)
{
    p.x += dx;
    p.y += dy;
    p.z += dz;
}

KX_MATH_API void Spatial::moveForwards (R speed)
{
    move (fwd() * speed);
}

KX_MATH_API void Spatial::moveBackwards (R speed)
{
    move (fwd() * -speed);
}

KX_MATH_API void Spatial::moveLeft (R speed)
{
     move (right() * -speed);
}

KX_MATH_API void Spatial::moveRight (R speed)
{
     move (right() * speed);
}

KX_MATH_API void Spatial::moveUp (R speed)
{
     move (up() * speed);
}

KX_MATH_API void Spatial::moveDown (R speed)
{
     move (up() * -speed);
}

KX_MATH_API void Spatial::rotate (R angle, R x, R y, R z)
{
    mat4 transf = transform();
    vec3 axis = ::transform (inverse_transform(transf), vec3 (x,y,z), 0.0f);
    axis.normalise();
    transf *= mat4::rot (angle, axis);
    r = normalise(transf.v0());
    u = normalise(transf.v1());
    f = normalise(-transf.v2());
}

KX_MATH_API void Spatial::yaw (const R angle)
{
    R a = angle * TO_RAD;
    R sa = sin (a);
    R ca = cos (a);
    f = f*ca - r*sa;
    f.normalise();
    r = cross (f, u);
    r.normalise();
}

KX_MATH_API void Spatial::pitch (const R angle)
{
    R a = angle * TO_RAD;
    R sa = sin (a);
    R ca = cos (a);
    f = f*ca + u*sa;
    f.normalise();
    u = cross (r, f);
    u.normalise();
}

KX_MATH_API void Spatial::roll (const R angle)
{
    R a = angle * TO_RAD;
    R sa = sin (a);
    R ca = cos (a);
    u = u * ca - r * sa;
    u.normalise();
    r = cross (f, u);
}

KX_MATH_API void Spatial::setx (R x)
{
    p.x = x;
}

KX_MATH_API void Spatial::sety (R y)
{
    p.y = y;
}

KX_MATH_API void Spatial::setz (R z)
{
    p.z = z;
}

KX_MATH_API void Spatial::setPosition (R x, R y, R z)
{
    p.x = x; p.y = y; p.z = z;
}

KX_MATH_API void Spatial::setPosition (const vec3& v)
{
    p = v;
}

KX_MATH_API void Spatial::setForward (R x, R y, R z)
{
    setForward(vec3(x,y,z));
}

KX_MATH_API void Spatial::setForward (const vec3& forward)
{
    f = forward;
    f.normalise();
    // use aux vector to define right vector orthogonal to forward
    if (f == up3() || f == -up3())
        r = cross(f, forward3());
    else
        r = cross(f, up3());
    u = cross(r,f);
    r.normalise();
    u.normalise();
}

KX_MATH_API void Spatial::setTransform (const mat4& transform)
{
    r = transform.v0();
    u = transform.v1();
    f = -transform.v2();
    p = transform.v3();
}

KX_MATH_API void Spatial::lookAt (R x, R y, R z)
{
    setForward (vec3(x,y,z) - p);
}

KX_MATH_API void Spatial::lookAt (const vec3& target)
{
    setForward (target - p);
}

KX_MATH_API void Spatial::lookAt (const Spatial& target)
{
    setForward (target.pos() - p);
}

KX_MATH_API void Spatial::orbit (R x, R y, R z, R radius, R azimuth, R zenith)
{
    R ax = azimuth * TO_RAD;
    R ay = zenith * TO_RAD;
    R sx = sin(ax);
    R sy = sin(ay);
    R cx = cos(ax);
    R cy = cos(ay);
    setPosition (x + radius*cy*sx, y + radius*sy, z + radius*cx*cy);
}

KX_MATH_API void Spatial::orbit (const vec3& target, R radius, R azimuth, R zenith)
{
    orbit (target.x, target.y, target.z, radius, azimuth, zenith);
}

KX_MATH_API void Spatial::orbit (const Spatial& target, R radius, R azimuth, R zenith)
{
    const vec3& p = target.pos();
    orbit (p.x, p.y, p.z, radius, azimuth, zenith);
}

KX_MATH_API const vec3& Spatial::pos () const
{
    return p;
}

KX_MATH_API const vec3& Spatial::fwd () const
{
    return f;
}

KX_MATH_API const vec3& Spatial::right () const
{
    return r;
}

KX_MATH_API const vec3& Spatial::up () const
{
    return u;
}

KX_MATH_API mat4 Spatial::transform () const
{
    return mat4
        (r.x , u.x , -f.x , p.x
        ,r.y , u.y , -f.y , p.y
        ,r.z , u.z , -f.z , p.z
        ,0.0f, 0.0f, 0.0f, 1.0f
        );
}

KX_MATH_API mat4 Spatial::inverseTransform () const
{
    return inverse_transform (transform());
}
