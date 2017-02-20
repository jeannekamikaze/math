#include <math/mat4.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/utils.h>

using namespace kx;
using namespace std;

KX_MATH_API mat4::mat4 ()
{
    val[0][0] = 1; val[0][1] = 0; val[0][2] = 0; val[0][3] = 0;
    val[1][0] = 0; val[1][1] = 1; val[1][2] = 0; val[1][3] = 0;
    val[2][0] = 0; val[2][1] = 0; val[2][2] = 1; val[2][3] = 0,
            val[3][0] = 0; val[3][1] = 0; val[3][2] = 0; val[3][3] = 1;
}

KX_MATH_API mat4::mat4 (R m00, R m10, R m20, R m30,
                          R m01, R m11, R m21, R m31,
                          R m02, R m12, R m22, R m32,
                          R m03, R m13, R m23, R m33)
{
    val[0][0] = m00; val[0][1] = m01; val[0][2] = m02; val[0][3] = m03;
    val[1][0] = m10; val[1][1] = m11; val[1][2] = m12; val[1][3] = m13;
    val[2][0] = m20; val[2][1] = m21; val[2][2] = m22; val[2][3] = m23,
            val[3][0] = m30; val[3][1] = m31; val[3][2] = m32; val[3][3] = m33;
}

KX_MATH_API mat4::mat4 (const vec4& v0,
                          const vec4& v1,
                          const vec4& v2,
                          const vec4& v3)
{
    val[0][0] = v0.x; val[0][1] = v0.y; val[0][2] = v0.z; val[0][3] = v0.w;
    val[1][0] = v1.x; val[1][1] = v1.y; val[1][2] = v1.z; val[1][3] = v1.w;
    val[2][0] = v2.x; val[2][1] = v2.y; val[2][2] = v2.z; val[2][3] = v2.w,
            val[3][0] = v3.x; val[3][1] = v3.y; val[3][2] = v3.z; val[3][3] = v3.w;
}

KX_MATH_API mat4::mat4 (const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3)
{
    val[0][0] = v0.x; val[0][1] = v0.y; val[0][2] = v0.z; val[0][3] = 0.0f;
    val[1][0] = v1.x; val[1][1] = v1.y; val[1][2] = v1.z; val[1][3] = 0.0f;
    val[2][0] = v2.x; val[2][1] = v2.y; val[2][2] = v2.z; val[2][3] = 0.0f;
    val[3][0] = v3.x; val[3][1] = v3.y; val[3][2] = v3.z; val[3][3] = 1.0f;
}

KX_MATH_API R& mat4::operator() (int row, int col)
{
    return val[col][row];
}

KX_MATH_API R mat4::operator() (int row, int col) const
{
    return val[col][row];
}

KX_MATH_API vec3& mat4::v0 ()
{
    return *((vec3*)val[0]);
}

KX_MATH_API vec3& mat4::v1 ()
{
    return *((vec3*)val[1]);
}

KX_MATH_API vec3& mat4::v2 ()
{
    return *((vec3*)val[2]);
}

KX_MATH_API vec3& mat4::v3 ()
{
    return *((vec3*)val[3]);
}

KX_MATH_API const vec3& mat4::v0 () const
{
    return *((vec3*)val[0]);
}

KX_MATH_API const vec3& mat4::v1 () const
{
    return *((vec3*)val[1]);
}

KX_MATH_API const vec3& mat4::v2 () const
{
    return *((vec3*)val[2]);
}

KX_MATH_API const vec3& mat4::v3 () const
{
    return *((vec3*)val[3]);
}

KX_MATH_API vec4& mat4::column (int i)
{
    return *((vec4*)val[i]);
}

KX_MATH_API const vec4& mat4::column (int i) const
{
    return *((vec4*)val[i]);
}

KX_MATH_API vec4 mat4::row (int i)
{
    return vec4(val[0][i], val[1][i], val[2][i], val[3][i]);
}

KX_MATH_API mat4 mat4::operator* (const mat4& m) const
{
    const mat4& a = *this;

    R m00 = a(0,0) * m(0,0) + a(0,1) * m(1,0) + a(0,2) * m(2,0) + a(0,3) * m(3,0);
    R m01 = a(0,0) * m(0,1) + a(0,1) * m(1,1) + a(0,2) * m(2,1) + a(0,3) * m(3,1);
    R m02 = a(0,0) * m(0,2) + a(0,1) * m(1,2) + a(0,2) * m(2,2) + a(0,3) * m(3,2);
    R m03 = a(0,0) * m(0,3) + a(0,1) * m(1,3) + a(0,2) * m(2,3) + a(0,3) * m(3,3);

    R m10 = a(1,0) * m(0,0) + a(1,1) * m(1,0) + a(1,2) * m(2,0) + a(1,3) * m(3,0);
    R m11 = a(1,0) * m(0,1) + a(1,1) * m(1,1) + a(1,2) * m(2,1) + a(1,3) * m(3,1);
    R m12 = a(1,0) * m(0,2) + a(1,1) * m(1,2) + a(1,2) * m(2,2) + a(1,3) * m(3,2);
    R m13 = a(1,0) * m(0,3) + a(1,1) * m(1,3) + a(1,2) * m(2,3) + a(1,3) * m(3,3);

    R m20 = a(2,0) * m(0,0) + a(2,1) * m(1,0) + a(2,2) * m(2,0) + a(2,3) * m(3,0);
    R m21 = a(2,0) * m(0,1) + a(2,1) * m(1,1) + a(2,2) * m(2,1) + a(2,3) * m(3,1);
    R m22 = a(2,0) * m(0,2) + a(2,1) * m(1,2) + a(2,2) * m(2,2) + a(2,3) * m(3,2);
    R m23 = a(2,0) * m(0,3) + a(2,1) * m(1,3) + a(2,2) * m(2,3) + a(2,3) * m(3,3);

    R m30 = a(3,0) * m(0,0) + a(3,1) * m(1,0) + a(3,2) * m(2,0) + a(3,3) * m(3,0);
    R m31 = a(3,0) * m(0,1) + a(3,1) * m(1,1) + a(3,2) * m(2,1) + a(3,3) * m(3,1);
    R m32 = a(3,0) * m(0,2) + a(3,1) * m(1,2) + a(3,2) * m(2,2) + a(3,3) * m(3,2);
    R m33 = a(3,0) * m(0,3) + a(3,1) * m(1,3) + a(3,2) * m(2,3) + a(3,3) * m(3,3);

    return mat4
            (m00, m01, m02, m03
             ,m10, m11, m12, m13
             ,m20, m21, m22, m23
             ,m30, m31, m32, m33);
}

KX_MATH_API void mat4::operator*= (const mat4& m)
{
    const mat4& a = *this;

    R m00 = a(0,0) * m(0,0) + a(0,1) * m(1,0) + a(0,2) * m(2,0) + a(0,3) * m(3,0);
    R m10 = a(0,0) * m(0,1) + a(0,1) * m(1,1) + a(0,2) * m(2,1) + a(0,3) * m(3,1);
    R m20 = a(0,0) * m(0,2) + a(0,1) * m(1,2) + a(0,2) * m(2,2) + a(0,3) * m(3,2);
    R m30 = a(0,0) * m(0,3) + a(0,1) * m(1,3) + a(0,2) * m(2,3) + a(0,3) * m(3,3);

    R m01 = a(1,0) * m(0,0) + a(1,1) * m(1,0) + a(1,2) * m(2,0) + a(1,3) * m(3,0);
    R m11 = a(1,0) * m(0,1) + a(1,1) * m(1,1) + a(1,2) * m(2,1) + a(1,3) * m(3,1);
    R m21 = a(1,0) * m(0,2) + a(1,1) * m(1,2) + a(1,2) * m(2,2) + a(1,3) * m(3,2);
    R m31 = a(1,0) * m(0,3) + a(1,1) * m(1,3) + a(1,2) * m(2,3) + a(1,3) * m(3,3);

    R m02 = a(2,0) * m(0,0) + a(2,1) * m(1,0) + a(2,2) * m(2,0) + a(2,3) * m(3,0);
    R m12 = a(2,0) * m(0,1) + a(2,1) * m(1,1) + a(2,2) * m(2,1) + a(2,3) * m(3,1);
    R m22 = a(2,0) * m(0,2) + a(2,1) * m(1,2) + a(2,2) * m(2,2) + a(2,3) * m(3,2);
    R m32 = a(2,0) * m(0,3) + a(2,1) * m(1,3) + a(2,2) * m(2,3) + a(2,3) * m(3,3);

    R m03 = a(3,0) * m(0,0) + a(3,1) * m(1,0) + a(3,2) * m(2,0) + a(3,3) * m(3,0);
    R m13 = a(3,0) * m(0,1) + a(3,1) * m(1,1) + a(3,2) * m(2,1) + a(3,3) * m(3,1);
    R m23 = a(3,0) * m(0,2) + a(3,1) * m(1,2) + a(3,2) * m(2,2) + a(3,3) * m(3,2);
    R m33 = a(3,0) * m(0,3) + a(3,1) * m(1,3) + a(3,2) * m(2,3) + a(3,3) * m(3,3);

    *this = mat4
            (m00, m10, m20, m30
             ,m01, m11, m21, m31
             ,m02, m12, m22, m32
             ,m03, m13, m23, m33);
}

KX_MATH_API mat4 mat4::transl () const
{
    const mat4& m = *this;
    return mat4
            (1.0f, 0.0f, 0.0f, m(0,3)
             ,0.0f, 1.0f, 0.0f, m(1,3)
             ,0.0f, 0.0f, 1.0f, m(2,3)
             ,0.0f, 0.0f, 0.0f, 1.0f);
}

KX_MATH_API mat4 mat4::rot () const
{
    const mat4& m = *this;
    return mat4
            (m(0,0), m(0,1), m(0,2), 0.0f
             ,m(1,0), m(1,1), m(1,2), 0.0f
             ,m(2,0), m(2,1), m(2,2), 0.0f
             ,0.0f  , 0.0f  , 0.0f  , 1.0f);
}

KX_MATH_API mat4 mat4::rotx (R angle)
{
    R a = angle * TO_RAD;
    R s = sin (a);
    R c = cos (a);

    return mat4
            (1, 0,  0, 0
             ,0, c, -s, 0
             ,0, s,  c, 0
             ,0, 0,  0, 1);
}

KX_MATH_API mat4 mat4::roty (R angle)
{
    R a = angle * TO_RAD;
    R s = sin (a);
    R c = cos (a);

    return mat4
            ( c, 0, s, 0
              , 0, 1, 0, 0
              ,-s, 0, c, 0
              , 0, 0, 0, 1);
}

KX_MATH_API mat4 mat4::rotz (R angle)
{
    R a = angle * TO_RAD;
    R s = sin (a);
    R c = cos (a);

    return mat4
            (c, -s, 0, 0
             ,s,  c, 0, 0
             ,0,  0, 1, 0
             ,0,  0, 0, 1);
}

KX_MATH_API mat4 mat4::rot (R angle, const vec3& axis)
{
    return rot (angle, axis.x, axis.y, axis.z);
}

KX_MATH_API mat4 mat4::rot (R angle, R x, R y, R z)
{
    R a = angle * TO_RAD;
    R s = sin (a);
    R c = cos (a);

    R xy  = x*y;
    R xz  = x*z;
    R yz  = y*z;
    R sx  = s*x;
    R sy  = s*y;
    R sz  = s*z;
    R omc = 1.0f - c;

    return mat4
            (c + omc*x*x, omc*xy-sz, omc*xz+sy, 0
             ,omc*xy+sz,   c+omc*y*y, omc*yz-sx, 0
             ,omc*xz-sy,   omc*yz+sx, c+omc*z*z, 0
             ,0,           0,         0,         1);
}

KX_MATH_API mat4 mat4::scale (const vec3& s)
{
    return mat4
            (s.x,   0,   0,   0
             ,  0, s.y,   0,   0
             ,  0,   0, s.z,   0
             ,  0,   0,   0,   1);
}

KX_MATH_API mat4 mat4::scale (R x, R y, R z)
{
    return mat4
            (x, 0, 0, 0
             ,0, y, 0, 0
             ,0, 0, z, 0
             ,0, 0, 0, 1);
}

KX_MATH_API mat4 mat4::transl (const vec3& p)
{
    return mat4
            (1, 0, 0, p.x
             ,0, 1, 0, p.y
             ,0, 0, 1, p.z
             ,0, 0, 0, 1);
}

KX_MATH_API mat4 mat4::transl (R x, R y, R z)
{
    return mat4
            (1, 0, 0, x
             ,0, 1, 0, y
             ,0, 0, 1, z
             ,0, 0, 0, 1);
}

KX_MATH_API mat4 mat4::reflectx ()
{
    return mat4
        (-1, 0, 0, 0
         , 0, 1, 0, 0
         , 0, 0, 1, 0
         , 0, 0, 0, 1);
}

KX_MATH_API mat4 mat4::reflecty ()
{
    return mat4
        (1,  0,  0,  0
         ,0, -1,  0,  0
         ,0,  0,  1,  0
         ,0,  0,  0,  1);
}

KX_MATH_API mat4 mat4::reflectz ()
{
    return mat4
        (1,  0,  0,  0
         ,0,  1,  0,  0
         ,0,  0, -1,  0
         ,0,  0,  0,  1);
}

KX_MATH_API mat4 mat4::id ()
{
    return mat4
        (1.0f, 0.0f, 0.0f, 0.0f
         ,0.0f, 1.0f, 0.0f, 0.0f
         ,0.0f, 0.0f, 1.0f, 0.0f
         ,0.0f, 0.0f, 0.0f, 1.0f);
}

KX_MATH_API mat4 mat4::transform (vec3 f)
{
    f.normalise();
    vec3 r = cross (f, up3());
    vec3 u = cross (r, f);
    r.normalise();
    u.normalise();
    return mat4
            (r.x , u.x , -f.x , 0.0f
             ,r.y , u.y , -f.y , 0.0f
             ,r.z , u.z , -f.z , 0.0f
             ,0.0f, 0.0f, 0.0f, 1.0f
             );
}

KX_MATH_API mat4 mat4::lookAt (const vec3& position, const vec3& target)
{
    vec3 fwd   = normalise (target - position);
    vec3 right = cross (fwd, vec3(0,1,0));
    vec3 up    = cross (right, fwd);
    return mat4 (right, up, fwd, position);
}

KX_MATH_API mat4 mat4::ortho (R l, R r, R b, R t, R n, R f)
{
    R tx = -(r+l) / (r-l);
    R ty = -(t+b) / (t-b);
    R tz = -(f+n) / (f-n);

    return mat4
            (2/(r-l), 0,        0,       tx
             ,0,       2/(t-b),  0,       ty
             ,0,       0,       -2/(f-n), tz
             ,0,       0,        0,       1);
}

KX_MATH_API mat4 mat4::perspective (R fovy, R r, R near, R far)
{
    R f = tan (fovy * TO_RAD / 2.0f);
    f   = f == 0.0f ? 1.0f : 1.0f / f;
    R a = near - far;

    return mat4
            (f/r,  0,  0,            0
             ,0,   f,  0,            0
             ,0,   0, (far+near)/a, (2*far*near/a)
             ,0,   0, -1,            0);
}

mat4 mat4::perspectiveInverse(R fovy, R r, R near, R far)
{
    R f = tan (fovy * TO_RAD / 2.0f);
    f   = f == 0.0f ? 1.0f : 1.0f / f;
    R a = far*near;

    R P32 = 0.5f * (near-far) / a;
    R P33 = 0.5f * (far+near) / a;

    return mat4
            (r/f,      0,   0,   0
             ,0,  1.0f/f,   0,   0
             ,0,       0,   0,  -1
             ,0,       0, P32, P33);
}

KX_MATH_API R kx::det (const mat4& m)
{
    R inv[16];

    inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];

    return m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
}

KX_MATH_API mat4 kx::inverse (const mat4& m)
{
    R inv[16];

    inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
    inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
    inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
    inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
    inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
    inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
    inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
    inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
    inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
    inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
    inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];

    R det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0.0f) return mat4::id();

    det = 1.0f / det;
    return mat4
            (inv[0] * det, inv[4] * det, inv[8]  * det, inv[12] * det
            ,inv[1] * det, inv[5] * det, inv[9]  * det, inv[13] * det
            ,inv[2] * det, inv[6] * det, inv[10] * det, inv[14] * det
            ,inv[3] * det, inv[7] * det, inv[11] * det, inv[15] * det);
}

KX_MATH_API mat4 kx::inverse_transform (const mat4& m)
{
    vec3 r = m.v0 ();
    vec3 u = m.v1 ();
    vec3 f = m.v2 ();
    vec3 t = m.v3 ();

    return mat4
            (r.x , r.y , r.z , -dot(r,t)
             , u.x , u.y , u.z , -dot(u,t)
             , f.x , f.y , f.z , -dot(f,t)
             , 0.0f, 0.0f, 0.0f, 1.0f);
}

KX_MATH_API mat4 kx::transpose (const mat4& m)
{
    return mat4
            (m(0,0), m(1,0), m(2,0), m(3,0)
             ,m(0,1), m(1,1), m(2,1), m(3,1)
             ,m(0,2), m(1,2), m(2,2), m(3,2)
             ,m(0,3), m(1,3), m(2,3), m(3,3));
}

KX_MATH_API vec3 kx::transform (const mat4& m, const vec3& v, R w)
{
    vec3 u;
    u.x = m(0,0) * v.x + m(0,1) * v.y + m(0,2) * v.z + m(0,3) * w;
    u.y = m(1,0) * v.x + m(1,1) * v.y + m(1,2) * v.z + m(1,3) * w;
    u.z = m(2,0) * v.x + m(2,1) * v.y + m(2,2) * v.z + m(2,3) * w;
    return u;
}

KX_MATH_API vec4 kx::operator* (const mat4& m, const vec4& v)
{
    return vec4
            (m(0,0)*v.x + m(0,1)*v.y + m(0,2)*v.z + m(0,3)*v.w,
             m(1,0)*v.x + m(1,1)*v.y + m(1,2)*v.z + m(1,3)*v.w,
             m(2,0)*v.x + m(2,1)*v.y + m(2,2)*v.z + m(2,3)*v.w,
             m(3,0)*v.x + m(3,1)*v.y + m(3,2)*v.z + m(3,3)*v.w);
}
