// Z:\Toshi\Source\TKernel\TQuaternion.cpp - quaternion (x, y, z, w).
// Only the simple members are written. Skipped: anything using SinCos, IDENTITY/VEC3_ZERO_ROTATION or float
// globals (Normalise, Slerp, Lerp, RotateVector, Euler conversions, operator/(float), operator*(quaternion)).
// The (x, y, z, w) constructor and Set(x, y, z, w) are inline in TVector.h.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include <math.h>
#include "TKernelMisc.h"
#include "TVector.h"

namespace Toshi {

const TVector4& TQuaternion::AsVector4() const
{
    return *(const TVector4*)this;
}

TVector4& TQuaternion::AsVector4()
{
    return *(TVector4*)this;
}

void TQuaternion::Slerp(const TQuaternion& target, float t)
{
    Slerp(*this, target, t);
}

void TQuaternion::GetVectorDirection(TVector3& direction) const
{
    RotateVector(direction, *this, VEC3_ZERO_ROTATION);
}

// Rotates v by q: q * v * inverse(q), with v treated as a pure quaternion (w = 0).
void __stdcall TQuaternion::RotateVector(TVector3& result, const TQuaternion& rotation, const TVector3& vector)
{
    TQuaternion inverse(rotation);
    inverse.SetInverse();
    TQuaternion pure(vector.x, vector.y, vector.z, 0.0f);
    TQuaternion rotated(rotation);
    rotated *= pure;
    TQuaternion product(rotated);
    product *= inverse;
    result.x = product.x;
    result.y = product.y;
    result.z = product.z;
}

float TQuaternion::Magnitude() const
{
    return (float)sqrt(x * x + y * y + z * z + w * w);
}

float TQuaternion::MagnitudeSq() const
{
    return x * x + y * y + z * z + w * w;
}

void TQuaternion::SetIdentity()
{
    *this = IDENTITY;
}

TQuaternion& TQuaternion::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
}

// The binary divides z by other.y: an original bug, kept as is.
TQuaternion& TQuaternion::operator/=(const TQuaternion& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.y;
    w /= other.w;
    return *this;
}

TQuaternion& TQuaternion::operator+=(const TQuaternion& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

TQuaternion& TQuaternion::operator-=(const TQuaternion& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

bool TQuaternion::operator==(const TQuaternion& other) const
{
    if (x != other.x || y != other.y || z != other.z || w != other.w) {
        return false;
    }
    return true;
}

bool TQuaternion::operator!=(const TQuaternion& other) const
{
    if (x != other.x || y != other.y || z != other.z || w != other.w) {
        return true;
    }
    return false;
}

void TQuaternion::Negate()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

void TQuaternion::Divide(TQuaternion& result, const TQuaternion& a, const TQuaternion& b)
{
    result = a;
    result /= b;
}

void TQuaternion::Multiply(TQuaternion& result, const TQuaternion& a, const TQuaternion& b)
{
    result = a;
    result *= b;
}

void TQuaternion::Subtract(TQuaternion& result, const TQuaternion& a, const TQuaternion& b)
{
    result = a;
    result -= b;
}

void TQuaternion::Add(TQuaternion& result, const TQuaternion& a, const TQuaternion& b)
{
    result = a;
    result += b;
}

TQuaternion TQuaternion::operator*(float s) const
{
    TQuaternion result = *this;
    result *= s;
    return result;
}

TQuaternion TQuaternion::operator*(const TQuaternion& other) const
{
    TQuaternion result = *this;
    result *= other;
    return result;
}

TQuaternion TQuaternion::operator-(const TQuaternion& other) const
{
    TQuaternion result = *this;
    result -= other;
    return result;
}

TQuaternion TQuaternion::operator+(const TQuaternion& other) const
{
    TQuaternion result = *this;
    result += other;
    return result;
}


void TQuaternion::DebugPrint(const char* label) const
{
}

void TQuaternion::Normalise()
{
    *this /= (float)sqrt(x * x + y * y + z * z + w * w);
}

void TQuaternion::RotateAroundAxis(const TVector3& axis, float angle)
{
    float sine;
    float cosine;
    float halfAngle = angle * 0.5f;
    TMath::SinCos(halfAngle, sine, cosine);
    TQuaternion rotation(axis.x * sine, axis.y * sine, axis.z * sine, cosine);
    *this *= rotation;
}

void TQuaternion::SetRotation(const TVector3& axis, float angle)
{
    float sine;
    float cosine;
    float halfAngle = angle * 0.5f;
    TMath::SinCos(halfAngle, sine, cosine);
    x = axis.x * sine;
    y = axis.y * sine;
    z = axis.z * sine;
    w = cosine;
}

// Flips the quaternion so that its last non-zero component (w first) is positive.
void TQuaternion::MakePrincple()
{
    for (int i = 3; i >= 0; i--)
    {
        float component = (&x)[i];
        if (component != 0.0f)
        {
            if (component < 0.0f)
            {
                Negate();
            }
            return;
        }
    }
}

// Normalised-free linear blend towards the nearer of 'to' and -'to'.
void TQuaternion::Lerp(const TQuaternion& from, const TQuaternion& to, float t)
{
    TQuaternion target;
    if (TVector4::DotProduct4(from.AsVector4(), to.AsVector4()) < 0.0f)
    {
        target.AsVector4().Negate4(to.AsVector4());
    }
    else
    {
        target = to;
    }
    float inverse = 1.0f - t;
    x = target.x * t + from.x * inverse;
    y = target.y * t + from.y * inverse;
    z = target.z * t + from.z * inverse;
    w = target.w * t + from.w * inverse;
}

TQuaternion TQuaternion::operator/(float scale) const
{
    TQuaternion result = *this;
    if (scale != 0.0f)
    {
        float inverse = 1.0f / scale;
        result *= inverse;
    }
    return result;
}

TQuaternion TQuaternion::operator/(const TQuaternion& other) const
{
    TQuaternion result = *this;
    result /= other;
    return result;
}

TQuaternion& TQuaternion::operator/=(float scale)
{
    if (scale != 0.0f)
    {
        float inverse = 1.0f / scale;
        *this *= inverse;
    }
    return *this;
}

} // namespace Toshi
