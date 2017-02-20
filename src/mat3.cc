#include <math/mat3.h>
#include <math/mat4.h>
#include <math/vec2.h>

using namespace kx;
using namespace std;

KX_MATH_API mat3::mat3 ()
{
    val[0][0] = 1; val[0][1] = 0; val[0][2] = 0;
    val[1][0] = 0; val[1][1] = 1; val[1][2] = 0;
    val[2][0] = 0; val[2][1] = 0; val[2][2] = 1;
}

KX_MATH_API mat3::mat3 (R m00, R m10, R m20,
            R m01, R m11, R m21,
            R m02, R m12, R m22)
{
    val[0][0] = m00; val[0][1] = m01; val[0][2] = m02;
    val[1][0] = m10; val[1][1] = m11; val[1][2] = m12;
    val[2][0] = m20; val[2][1] = m21; val[2][2] = m22;
}

KX_MATH_API mat3::mat3 (const vec3& v0,
            const vec3& v1,
            const vec3& v2)
{
    val[0][0] = v0.x; val[0][1] = v0.y; val[0][2] = v0.z;
    val[1][0] = v1.x; val[1][1] = v1.y; val[1][2] = v1.z;
    val[2][0] = v2.x; val[2][1] = v2.y; val[2][2] = v2.z;
}

KX_MATH_API mat3::mat3 (const vec2& right, const vec2& up, const vec2& pos)
{
    val[0][0] = right.x; val[0][1] = right.y; val[0][2] = 0;
    val[1][0] = up.x;    val[1][1] = up.y;    val[1][2] = 0;
    val[2][0] = pos.x;   val[2][1] = pos.y;   val[2][2] = 1;
}

KX_MATH_API mat3::mat3 (const mat4& m)
{
    val[0][0] = m(0,0); val[0][1] = m(1,0); val[0][2] = m(2,0);
    val[1][0] = m(0,1); val[1][1] = m(1,1); val[1][2] = m(2,1);
    val[2][0] = m(0,2); val[2][1] = m(1,2); val[2][2] = m(2,2);
}

KX_MATH_API mat3 mat3::rot (R angle)
{
    R a  = angle * (R) M_PI / 180.0f;
    R sa = sin(a);
    R ca = cos(a);

    return mat3
        (ca, -sa, 0
        ,sa,  ca, 0
        , 0,   0, 1);
}

KX_MATH_API mat3 mat3::scale (vec3 s)
{
    return mat3
        (s.x,   0,   0
        ,  0, s.y,   0
        ,  0,   0, s.z);
}

KX_MATH_API mat3 mat3::scale (R x, R y, R z)
{
    return mat3
        (x, 0, 0
        ,0, y, 0
        ,0, 0, z);
}

KX_MATH_API mat3 mat3::transl (vec2 p)
{
    return mat3
        (1, 0, p.x
        ,0, 1, p.y
        ,0, 0, 1);
}

KX_MATH_API mat3 mat3::transl (R x, R y)
{
    return mat3
        (1, 0, x
        ,0, 1, y
        ,0, 0, 1);
}

KX_MATH_API R& mat3::operator() (int row, int col)
{
    return val[col][row];
}

KX_MATH_API R mat3::operator() (int row, int col) const
{
    return val[col][row];
}

KX_MATH_API vec2& mat3::v0 ()
{
    return *((vec2*)val[0]);
}

KX_MATH_API vec2& mat3::v1 ()
{
    return *((vec2*)val[1]);
}

KX_MATH_API vec2& mat3::v2 ()
{
    return *((vec2*)val[2]);
}

KX_MATH_API const vec2& mat3::v0 () const
{
    return *((vec2*)val[0]);
}

KX_MATH_API const vec2& mat3::v1 () const
{
    return *((vec2*)val[1]);
}

KX_MATH_API const vec2& mat3::v2 () const
{
    return *((vec2*)val[2]);
}

KX_MATH_API mat3 mat3::operator* (const mat3& m)
{
    const mat3& a = *this;

    R m00 = a(0,0) * m(0,0) + a(0,1) * m(1,0) + a(0,2) * m(2,0);
    R m01 = a(0,0) * m(0,1) + a(0,1) * m(1,1) + a(0,2) * m(2,1);
    R m02 = a(0,0) * m(0,2) + a(0,1) * m(1,2) + a(0,2) * m(2,2);

    R m10 = a(1,0) * m(0,0) + a(1,1) * m(1,0) + a(1,2) * m(2,0);
    R m11 = a(1,0) * m(0,1) + a(1,1) * m(1,1) + a(1,2) * m(2,1);
    R m12 = a(1,0) * m(0,2) + a(1,1) * m(1,2) + a(1,2) * m(2,2);

    R m20 = a(2,0) * m(0,0) + a(2,1) * m(1,0) + a(2,2) * m(2,0);
    R m21 = a(2,0) * m(0,1) + a(2,1) * m(1,1) + a(2,2) * m(2,1);
    R m22 = a(2,0) * m(0,2) + a(2,1) * m(1,2) + a(2,2) * m(2,2);

    return mat3
        (m00, m01, m02
        ,m10, m11, m12
        ,m20, m21, m22);
}

KX_MATH_API void mat3::operator*= (const mat3& m)
{
    const mat3& a = *this;

    R m00 = a(0,0) * m(0,0) + a(0,1) * m(1,0) + a(0,2) * m(2,0);
    R m01 = a(0,0) * m(0,1) + a(0,1) * m(1,1) + a(0,2) * m(2,1);
    R m02 = a(0,0) * m(0,2) + a(0,1) * m(1,2) + a(0,2) * m(2,2);

    R m10 = a(1,0) * m(0,0) + a(1,1) * m(1,0) + a(1,2) * m(2,0);
    R m11 = a(1,0) * m(0,1) + a(1,1) * m(1,1) + a(1,2) * m(2,1);
    R m12 = a(1,0) * m(0,2) + a(1,1) * m(1,2) + a(1,2) * m(2,2);

    R m20 = a(2,0) * m(0,0) + a(2,1) * m(1,0) + a(2,2) * m(2,0);
    R m21 = a(2,0) * m(0,1) + a(2,1) * m(1,1) + a(2,2) * m(2,1);
    R m22 = a(2,0) * m(0,2) + a(2,1) * m(1,2) + a(2,2) * m(2,2);

    *this = mat3
        (m00, m01, m02
        ,m10, m11, m12
        ,m20, m21, m22);
}

KX_MATH_API mat3 mat3::transl () const
{
    const mat3& m = *this;
    return mat3
        (1.0f, 0.0f, m(0,2)
        ,0.0f, 1.0f, m(1,2)
        ,0.0f, 0.0f, 1.0f);
}

KX_MATH_API mat3 mat3::rot () const
{
    const mat3& m = *this;
    return mat3
        (m(0,0), m(0,1), 0.0f
        ,m(1,0), m(1,1), 0.0f
        ,0.0f  , 0.0f  , 1.0f);
}

KX_MATH_API mat3 mat3::reflectx ()
{
    return mat3
    (-1, 0, 0
    , 0, 1, 0
    , 0, 0, 1);
}

KX_MATH_API mat3 mat3::reflecty ()
{
    return mat3
    (1,  0,  0
    ,0, -1,  0
    ,0,  0,  1);
}

KX_MATH_API mat3 mat3::reflectz ()
{
    return mat3
    (1,  0,  0
    ,0,  1,  0
    ,0,  0, -1);
}

KX_MATH_API mat3 mat3::id ()
{
    return mat3
    ( 1.0f, 0.0f, 0.0f
    , 0.0f, 1.0f, 0.0f
    , 0.0f, 0.0f, 1.0f);
}

KX_MATH_API mat3 kx::inverse (const mat3& m)
{
    R m00 = m[0];
    R m01 = m[1];
    R m02 = m[2];
    R m03 = m[3];
    R m04 = m[4];
    R m05 = m[5];
    R m06 = m[6];
    R m07 = m[7];
    R m08 = m[8];

    R det = m00*(m04*m08-m05*m07) - m03*(m01*m08-m02*m07) + m06*(m01*m05-m02*m04);
    if (det == 0.0f) return mat3::id();

    R d10 = m04*m08 - m07*m05;
    R d11 = m03*m08 - m06*m05;
    R d12 = m03*m07 - m06*m04;
    R d20 = m01*m08 - m07*m02;
    R d21 = m00*m08 - m06*m02;
    R d22 = m00*m07 - m06*m01;
    R d30 = m01*m05 - m04*m02;
    R d31 = m00*m05 - m03*m02;
    R d32 = m00*m04 - m03*m01;

    det = det / 1.0f;

    return mat3
            ( d10*det, -d11*det,  d12*det
            ,-d20*det,  d21*det, -d22*det
            , d30*det, -d31*det,  d32*det);
}

KX_MATH_API mat3 kx::transpose (const mat3& m)
{
    return mat3
        (m(0,0), m(1,0), m(2,0)
        ,m(0,1), m(1,1), m(2,1)
        ,m(0,2), m(1,2), m(2,2));
}

KX_MATH_API vec3 kx::operator* (const mat3& m, vec3 v)
{
    return vec3
        (m(0,0)*v.x + m(0,1)*v.y + m(0,2)*v.z,
         m(1,0)*v.x + m(1,1)*v.y + m(1,2)*v.z,
         m(2,0)*v.x + m(2,1)*v.y + m(2,2)*v.z);
}
