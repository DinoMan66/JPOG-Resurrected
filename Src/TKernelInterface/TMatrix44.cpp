// Z:\Toshi\Source\TKernel\TMatrix44.cpp - 4x4 matrix (row vectors, translation in the last row).
// Functions are in the original's order (the binary's layout); ICC's inlining depends on it.
// Not written yet: Invert4/InvertArbitrary (x87 double-precision cofactor expansions).
// The element/row accessors, Set and the compound operators are inline in the class (TVector.h), as in the original:
// they are inlined everywhere and emitted at the end of the module.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include <math.h>
#include "TKernelMisc.h"
#include "TVector.h"

namespace Toshi {

void TMatrix44::Identity()
{
    *this = IDENTITY;
}

// 4x4 determinant as a sum of products of 2x2 minors.
float TMatrix44::Determinant4() const
{
    return (m_f42 * m_f31 - m_f32 * m_f41) * (m_f24 * m_f13 - m_f14 * m_f23)
        + ((((m_f44 * m_f33 - m_f34 * m_f43) * (m_f22 * m_f11 - m_f12 * m_f21)
            - (m_f32 * m_f11 - m_f12 * m_f31) * (m_f44 * m_f23 - m_f24 * m_f43))
            + (m_f11 * m_f42 - m_f12 * m_f41) * (m_f34 * m_f23 - m_f24 * m_f33)
            + (m_f32 * m_f21 - m_f22 * m_f31) * (m_f44 * m_f13 - m_f43 * m_f14))
            - (m_f34 * m_f13 - m_f33 * m_f14) * (m_f21 * m_f42 - m_f22 * m_f41));
}

float TMatrix44::Determinant() const
{
    return (m_f22 * m_f33 - m_f23 * m_f32) * m_f11
        - (m_f12 * m_f33 - m_f13 * m_f32) * m_f21
        + (m_f12 * m_f23 - m_f13 * m_f22) * m_f31;
}

// General inverse for matrices whose last column is (0, 0, 0, 1): invert the 3x3 part through its cofactors,
// then rotate the negated translation. Fails when the 3x3 determinant is zero.
bool TMatrix44::Invert(const TMatrix44& source)
{
    float cofactor11 = source.m_f33 * source.m_f22 - source.m_f32 * source.m_f23;
    float cofactor12 = -(source.m_f33 * source.m_f12 - source.m_f32 * source.m_f13);
    float cofactor13 = source.m_f12 * source.m_f23 - source.m_f22 * source.m_f13;
    float determinant = cofactor12 * source.m_f21 + cofactor11 * source.m_f11 + cofactor13 * source.m_f31;
    if (determinant != 0.0f) {
        float inverse = 1.0f / determinant;
        m_f11 = cofactor11 * inverse;
        m_f12 = cofactor12 * inverse;
        m_f13 = cofactor13 * inverse;
        m_f14 = source.m_f14;
        m_f21 = -(source.m_f33 * source.m_f21 - source.m_f31 * source.m_f23) * inverse;
        m_f22 = (source.m_f33 * source.m_f11 - source.m_f31 * source.m_f13) * inverse;
        m_f23 = -(source.m_f23 * source.m_f11 - source.m_f13 * source.m_f21) * inverse;
        m_f24 = source.m_f24;
        m_f31 = (source.m_f32 * source.m_f21 - source.m_f31 * source.m_f22) * inverse;
        m_f32 = -(source.m_f32 * source.m_f11 - source.m_f31 * source.m_f12) * inverse;
        m_f33 = (source.m_f11 * source.m_f22 - source.m_f12 * source.m_f21) * inverse;
        m_f34 = source.m_f34;
        m_f41 = -source.m_f41;
        m_f42 = -source.m_f42;
        m_f43 = -source.m_f43;
        m_f44 = source.m_f44;
        TVector4& translation = (TVector4&)m_f41;
        RotateVector(translation, *this, translation);
        return true;
    }
    return false;
}

// Inverse of a rotation (+ translation) matrix: transpose the 3x3 part, negate the translation, then rotate it.
void TMatrix44::InvertOrthogonal(const TMatrix44& source)
{
    Set(source.m_f11, source.m_f21, source.m_f31, source.m_f14,
        source.m_f12, source.m_f22, source.m_f32, source.m_f24,
        source.m_f13, source.m_f23, source.m_f33, source.m_f34,
        -source.m_f41, -source.m_f42, -source.m_f43, source.m_f44);
    TVector4& translation = (TVector4&)m_f41;
    RotateVector(translation, *this, translation);
}

void TMatrix44::Transpose(const TMatrix44& source)
{
    Set(source.m_f11, source.m_f21, source.m_f31, source.m_f41,
        source.m_f12, source.m_f22, source.m_f32, source.m_f42,
        source.m_f13, source.m_f23, source.m_f33, source.m_f43,
        source.m_f14, source.m_f24, source.m_f34, source.m_f44);
}

void TMatrix44::Add(const TMatrix44& a, const TMatrix44& b)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*this)(i, j) = a(i, j) + b(i, j);
        }
    }
}

void TMatrix44::Subtract(const TMatrix44& a, const TMatrix44& b)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*this)(i, j) = a(i, j) - b(i, j);
        }
    }
}

// this = a * b with row vectors: row i of the result is row i of b transformed by a.
void TMatrix44::Multiply(const TMatrix44& a, const TMatrix44& b)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*this)(i, j) = a(0, j) * b(i, 0) + a(1, j) * b(i, 1) + a(2, j) * b(i, 2) + a(3, j) * b(i, 3);
        }
    }
}

void TMatrix44::Multiply(const TMatrix44& a, float s)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*this)(i, j) = a(i, j) * s;
        }
    }
}

// Inverse of a rotation (+ translation) matrix: transpose the 3x3 part, then rotate the negated translation.
void TMatrix44::InvertOrthogonal()
{
    float temp = m_f12;
    m_f12 = m_f21;
    m_f21 = temp;
    temp = m_f13;
    m_f13 = m_f31;
    m_f31 = temp;
    temp = m_f23;
    m_f23 = m_f32;
    m_f32 = temp;
    TVector4& translation = (TVector4&)m_f41;
    translation.Negate3();
    RotateVector(translation, *this, translation);
}

void TMatrix44::Multiply(const TMatrix44& other)
{
    TMatrix44 result;
    result.Multiply(*this, other);
    *this = result;
}

bool TMatrix44::IsEqual(const TMatrix44& other) const
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((*this)(i, j) != other(i, j)) {
                return false;
            }
        }
    }
    return true;
}

// The rows are orthogonal when all their mutual dot products are (nearly) zero.
bool TMatrix44::IsOrthogonal() const
{
    TVector3 crossDots(TVector3::DotProduct(AsBasisVector3(0), AsBasisVector3(1)),
                       TVector3::DotProduct(AsBasisVector3(0), AsBasisVector3(2)),
                       TVector3::DotProduct(AsBasisVector3(1), AsBasisVector3(2)));
    return TVector3::DotProduct(crossDots, crossDots) < MAX_ORTHODEVIATION;
}

// Orthonormal: orthogonal rows that also have unit length.
bool TMatrix44::IsOrthonormal() const
{
    TVector3 crossDots(TVector3::DotProduct(AsBasisVector3(0), AsBasisVector3(1)),
                       TVector3::DotProduct(AsBasisVector3(0), AsBasisVector3(2)),
                       TVector3::DotProduct(AsBasisVector3(1), AsBasisVector3(2)));
    TVector3 lengthErrors(TVector3::DotProduct(AsBasisVector3(0), AsBasisVector3(0)) - 1.0f,
                          TVector3::DotProduct(AsBasisVector3(1), AsBasisVector3(1)) - 1.0f,
                          TVector3::DotProduct(AsBasisVector3(2), AsBasisVector3(2)) - 1.0f);
    return TVector3::DotProduct(crossDots, crossDots) + TVector3::DotProduct(lengthErrors, lengthErrors) <
           MAX_ORTHODEVIATION;
}

bool TMatrix44::IsReflected() const
{
    TVector3 cross;
    cross.CrossProduct(*(const TVector3*)&m_f11, *(const TVector3*)&m_f21);
    return TVector3::DotProduct(cross, *(const TVector3*)&m_f31) < 0.0f;
}

void TMatrix44::Scale(float x, float y, float z)
{
    m_f11 *= x; m_f12 *= x; m_f13 *= x;
    m_f21 *= y; m_f22 *= y; m_f23 *= y;
    m_f31 *= z; m_f32 *= z; m_f33 *= z;
}

void TMatrix44::Scale(const TVector4& v)
{
    m_f11 *= v.x; m_f12 *= v.x; m_f13 *= v.x;
    m_f21 *= v.y; m_f22 *= v.y; m_f23 *= v.y;
    m_f31 *= v.z; m_f32 *= v.z; m_f33 *= v.z;
}

void TMatrix44::RotateX(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float ns = -s;
    float t = m_f21;
    m_f21 = c * t + s * m_f31;
    m_f31 = m_f31 * c + t * ns;
    t = m_f22;
    m_f22 = s * m_f32 + c * t;
    m_f32 = m_f32 * c + t * ns;
    t = m_f23;
    m_f23 = s * m_f33 + c * t;
    m_f33 = t * ns + m_f33 * c;
}

void TMatrix44::RotateY(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float ns = -s;
    float t = m_f11;
    m_f11 = c * t + ns * m_f31;
    m_f31 = m_f31 * c + t * s;
    t = m_f12;
    m_f12 = ns * m_f32 + c * t;
    m_f32 = m_f32 * c + t * s;
    t = m_f13;
    m_f13 = ns * m_f33 + c * t;
    m_f33 = t * s + c * m_f33;
}

void TMatrix44::RotateZ(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float t = m_f11;
    float ns = -s;
    m_f11 = c * t + s * m_f21;
    m_f21 = m_f21 * c + t * ns;
    t = m_f12;
    m_f12 = s * m_f22 + c * t;
    m_f22 = m_f22 * c + t * ns;
    t = m_f13;
    m_f13 = s * m_f23 + c * t;
    m_f23 = m_f23 * c + t * ns;
}

void TMatrix44::LookAtTarget(TVector3& target, TVector3& position)
{
    TVector3& forward = AsBasisVector3(2);
    forward.Subtract(target, position);
    forward.Normalise();
    // right = (forward.z, 0, -forward.x), written straight into the first row
    m_f11 = m_f33;
    m_f12 = 0.0f;
    m_f13 = -m_f31;
    TVector3& right = AsBasisVector3(0);
    right.Normalise();
    AsBasisVector3(1).CrossProduct(right, forward);
}

void TMatrix44::Translate(float x, float y, float z)
{
    TVector4 v(x, y, z, 1.0f);
    TransformVector(*(TVector4*)&m_f41, *this, v);
}

void __stdcall TMatrix44::TransformVector(TVector3& result, const TMatrix44& m, const TVector3& v)
{
    float x = v.x * m.m_f11 + v.y * m.m_f21 + v.z * m.m_f31 + m.m_f41;
    float y = v.x * m.m_f12 + v.y * m.m_f22 + v.z * m.m_f32 + m.m_f42;
    float z = v.x * m.m_f13 + v.y * m.m_f23 + v.z * m.m_f33 + m.m_f43;
    result.x = x;
    result.y = y;
    result.z = z;
}

void __stdcall TMatrix44::TransformVector(TVector4& result, const TMatrix44& m, const TVector4& v)
{
    float x = v.x * m.m_f11 + v.y * m.m_f21 + v.z * m.m_f31 + v.w * m.m_f41;
    float y = v.x * m.m_f12 + v.y * m.m_f22 + v.z * m.m_f32 + v.w * m.m_f42;
    float z = v.x * m.m_f13 + v.y * m.m_f23 + v.z * m.m_f33 + v.w * m.m_f43;
    float w = v.x * m.m_f14 + v.y * m.m_f24 + v.z * m.m_f34 + v.w * m.m_f44;
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
}

void __stdcall TMatrix44::RotateVector(TVector3& result, const TMatrix44& m, const TVector3& v)
{
    float x = v.x * m.m_f11 + v.y * m.m_f21 + v.z * m.m_f31;
    float y = v.x * m.m_f12 + v.y * m.m_f22 + v.z * m.m_f32;
    float z = v.x * m.m_f13 + v.y * m.m_f23 + v.z * m.m_f33;
    result.x = x;
    result.y = y;
    result.z = z;
}

void __stdcall TMatrix44::RotateVector(TVector4& result, const TMatrix44& m, const TVector4& v)
{
    float x = v.x * m.m_f11 + v.y * m.m_f21 + v.z * m.m_f31;
    float y = v.x * m.m_f12 + v.y * m.m_f22 + v.z * m.m_f32;
    float z = v.x * m.m_f13 + v.y * m.m_f23 + v.z * m.m_f33;
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = v.w;
}

// Transforms a plane (normal + distance) by building two tangent directions on the plane, transforming them and
// the plane's point, and rebuilding the normal from the transformed tangents.
void __stdcall TMatrix44::TransformPlane(TPlane& result, const TMatrix44& m, const TPlane& plane)
{
    const TVector4& normal = plane.AsVector4();
    TVector4 tangent;
    if (fabsf(normal.y) <= fabsf(normal.x)) {
        tangent.Set(-normal.z, 0.0f, normal.x, 1.0f);
    } else {
        tangent.Set(0.0f, normal.z, -normal.y, 1.0f);
    }
    TVector4 bitangent;
    bitangent.CrossProduct(normal, tangent);
    bitangent.w = 1.0f;
    TVector4 point;
    point.Multiply(normal, plane.m_oPlane.w);
    point.w = 1.0f;
    RotateVector(tangent, m, tangent);
    RotateVector(bitangent, m, bitangent);
    result.AsVector4().CrossProduct(tangent, bitangent);
    result.AsVector4().Normalise();
    TransformVector(point, m, point);
    result.m_oPlane.w = TVector4::DotProduct3(result.AsVector4(), point);
    if (m.IsReflected()) {
        result.AsVector4().Negate4();
    }
}

void __stdcall TMatrix44::TransformPlaneOrthogonal(TPlane& result, const TMatrix44& m, const TPlane& plane)
{
    RotateVector(result.AsVector4(), m, plane.AsVector4());
    result.SetD(TVector4::DotProduct3(result.AsVector4(), *(const TVector4*)&m.m_f41) + plane.m_oPlane.w);
}

// Rotation matrix to quaternion: picks the largest of the trace and the diagonal terms for numerical stability.
void __stdcall TMatrix44::MatToQuat(TQuaternion& q, const TMatrix44& m)
{
    float trace = m.m_f22 + m.m_f11 + m.m_f33;
    if (trace > 0.0f) {
        float s = sqrtf(1.0f + trace) * 0.5f;
        q.w = s;
        float inv = 0.25f / s;
        q.x = (m.m_f23 - m.m_f32) * inv;
        q.y = (m.m_f31 - m.m_f13) * inv;
        q.z = (m.m_f12 - m.m_f21) * inv;
        return;
    }
    if (m.m_f22 <= m.m_f11) {
        if (m.m_f33 < m.m_f11) {
            float s = sqrtf(((1.0f + m.m_f11) - m.m_f22) - m.m_f33) * 0.5f;
            q.x = s;
            float inv = 0.25f / s;
            q.w = (m.m_f23 - m.m_f32) * inv;
            q.y = (m.m_f12 + m.m_f21) * inv;
            q.z = (m.m_f13 + m.m_f31) * inv;
            return;
        }
    } else if (m.m_f33 <= m.m_f22) {
        float s = sqrtf(((1.0f + m.m_f22) - m.m_f33) - m.m_f11) * 0.5f;
        q.y = s;
        float inv = 0.25f / s;
        q.w = (m.m_f31 - m.m_f13) * inv;
        q.z = (m.m_f23 + m.m_f32) * inv;
        q.x = (m.m_f21 + m.m_f12) * inv;
        return;
    }
    float s = sqrtf(((1.0f + m.m_f33) - m.m_f11) - m.m_f22) * 0.5f;
    q.z = s;
    float inv = 0.25f / s;
    q.w = (m.m_f12 - m.m_f21) * inv;
    q.x = (m.m_f31 + m.m_f13) * inv;
    q.y = (m.m_f32 + m.m_f23) * inv;
}

TMatrix44& TMatrix44::SetFromQuaternion(const TQuaternion& q)
{
    float sy = QUATSCALAR * q.y;
    float sz = QUATSCALAR * q.z;
    float sxw = QUATSCALAR * q.x * q.w;
    float sxx = QUATSCALAR * q.x * q.x;
    float szz = sz * q.z;
    m_f11 = 1.0f - (szz + sy * q.y);
    m_f21 = sy * q.x - q.w * sz;
    m_f31 = q.x * sz + sy * q.w;
    m_f12 = q.w * sz + sy * q.x;
    m_f22 = 1.0f - (szz + sxx);
    m_f32 = q.y * sz - sxw;
    m_f13 = q.x * sz - sy * q.w;
    m_f23 = sxw + q.y * sz;
    m_f33 = 1.0f - (sy * q.y + sxx);
    m_f14 = 0.0f;
    m_f24 = 0.0f;
    m_f34 = 0.0f;
    m_f41 = 0.0f;
    m_f42 = 0.0f;
    m_f43 = 0.0f;
    m_f44 = 1.0f;
    return *this;
}

// this = parent * (rotation with the given translation)
TMatrix44& TMatrix44::PushQuaternion(const TQuaternion& rotation, const TMatrix44& parent, const TVector3& translation)
{
    TMatrix44 local;
    local.SetFromQuaternion(rotation);
    local.AsBasisVector3(3) = translation;
    Multiply(parent, local);
    return *this;
}

TPlane TMatrix44::operator*(const TPlane& p) const
{
    TPlane result;
    TransformPlane(result, *this, p);
    return result;
}

TVector4 TMatrix44::operator*(const TVector4& v) const
{
    TVector4 result;
    TransformVector(result, *this, v);
    return result;
}

TVector3 TMatrix44::operator*(const TVector3& v) const
{
    TVector3 result;
    TransformVector(result, *this, v);
    return result;
}

void TMatrix44::GetTranslate(TVector4& v) const
{
    v.x = m_f41;
    v.y = m_f42;
    v.z = m_f43;
    v.w = m_f44;
}

void TMatrix44::GetTranslate(TVector3& v) const
{
    v.x = m_f41;
    v.y = m_f42;
    v.z = m_f43;
}

void TMatrix44::SetTranslate(float x, float y, float z)
{
    m_f41 = x;
    m_f42 = y;
    m_f43 = z;
}

void TMatrix44::SetTranslate(const TVector4& v)
{
    m_f41 = v.x;
    m_f42 = v.y;
    m_f43 = v.z;
    m_f44 = v.w;
}

void TMatrix44::SetTranslate(const TVector3& v)
{
    m_f41 = v.x;
    m_f42 = v.y;
    m_f43 = v.z;
}

void TMatrix44::Translate(const TVector4& v)
{
    TransformVector(*(TVector4*)&m_f41, *this, v);
}

void TMatrix44::Translate(const TVector3& v)
{
    TransformVector(*(TVector3*)&m_f41, *this, v);
}

void TMatrix44::LookAtTarget(TVector3& target)
{
    LookAtTarget(target, *(TVector3*)&m_f41);
}

void TMatrix44::Rotate(float x, float y, float z)
{
    RotateX(x);
    RotateY(y);
    RotateZ(z);
}

void TMatrix44::Scale(float s)
{
    Scale(s, s, s);
}

bool TMatrix44::IsIdentity() const
{
    return IsEqual(IDENTITY);
}

void TMatrix44::Divide(float s)
{
    Multiply(*this, 1.0f / s);
}

void TMatrix44::Multiply(float s)
{
    Multiply(*this, s);
}

void TMatrix44::Subtract(const TMatrix44& m)
{
    Subtract(*this, m);
}

void TMatrix44::Add(const TMatrix44& m)
{
    Add(*this, m);
}

bool TMatrix44::Invert()
{
    return Invert(*this);
}

void TMatrix44::Divide(const TMatrix44& m, float s)
{
    Multiply(m, 1.0f / s);
}

TMatrix44 TMatrix44::operator*(float s) const
{
    TMatrix44 result;
    result.Multiply(*this, s);
    return result;
}

TMatrix44 TMatrix44::operator*(const TMatrix44& m) const
{
    TMatrix44 result;
    result.Multiply(*this, m);
    return result;
}

TMatrix44 TMatrix44::operator-(const TMatrix44& m) const
{
    TMatrix44 result;
    result.Subtract(*this, m);
    return result;
}

TMatrix44 TMatrix44::operator+(const TMatrix44& m) const
{
    TMatrix44 result;
    result.Add(*this, m);
    return result;
}

void TMatrix44::DebugPrint(const char* label) const
{
}

} // namespace Toshi
