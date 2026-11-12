// Z:\Toshi\Source\TKernel\TVector4.cpp - 4D vector (also used for colours, planes and quaternion-like data).
// The plain Add/Subtract/Multiply/Divide/Negate/Magnitude/DotProduct work on xyz only (w is kept or copied);
// the "4" variants (Subtract4, Multiply4, Negate4, DotProduct4) include w.
// Not written yet: Normalise, Max, Min, Rotate*, Divide(float), Divide(vec, float).
// Set(x, y, z, w), the (x, y, z, w) constructor and the copy operations stay inline in TVector.h.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include <math.h>
#include "TKernelMisc.h"
#include "TVector.h"

namespace Toshi {

TVector4::TVector4(const float* const values)
{
    Set(values);
}

void TVector4::Set(const float* const values)
{
    x = values[0];
    y = values[1];
    z = values[2];
    w = values[3];
}

void TVector4::Set(const TVector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = 1.0f;
}

const TVector3& TVector4::AsVector3() const
{
    return *(const TVector3*)this;
}

TVector3& TVector4::AsVector3()
{
    return *(TVector3*)this;
}

bool TVector4::operator==(const TVector4& other) const
{
    return IsEqual(other);
}

bool TVector4::operator!=(const TVector4& other) const
{
    return !IsEqual(other);
}

TVector4& TVector4::operator*=(float scalar)
{
    Multiply(scalar);
    return *this;
}

TVector4& TVector4::operator*=(const TVector4& other)
{
    Multiply(other);
    return *this;
}

TVector4& TVector4::operator-=(const TVector4& other)
{
    Subtract(other);
    return *this;
}

TVector4& TVector4::operator+=(const TVector4& other)
{
    Add(other);
    return *this;
}

const float& TVector4::operator()(unsigned int index) const
{
    return (&x)[index];
}

float& TVector4::operator()(unsigned int index)
{
    return (&x)[index];
}

TVector4 TVector4::operator/(float scalar) const
{
    TVector4 result;
    result.Divide(*this, scalar);
    return result;
}

TVector4 TVector4::operator/(const TVector4& other) const
{
    TVector4 result;
    result.Divide(*this, other);
    return result;
}

TVector4 TVector4::operator*(float scalar) const
{
    TVector4 result;
    result.Multiply(*this, scalar);
    return result;
}

TVector4 TVector4::operator*(const TVector4& other) const
{
    TVector4 result;
    result.Multiply(*this, other);
    return result;
}

TVector4 TVector4::operator-(const TVector4& other) const
{
    TVector4 result;
    result.Subtract(*this, other);
    return result;
}

TVector4 TVector4::operator+(const TVector4& other) const
{
    TVector4 result;
    result.Add(*this, other);
    return result;
}

float TVector4::DotProduct(const TVector4& other) const
{
    return DotProduct3(*this, other);
}

float TVector4::DotProduct4(const TVector4& other) const
{
    return DotProduct4(*this, other);
}

float TVector4::DotProduct3(const TVector4& other) const
{
    return DotProduct3(*this, other);
}

float TVector4::DotProduct(const TVector4& a, const TVector4& b)
{
    return DotProduct3(a, b);
}

float TVector4::DotProduct4(const TVector4& a, const TVector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float TVector4::DotProduct3(const TVector4& a, const TVector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float TVector4::Magnitude() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

float TVector4::MagnitudeSq() const
{
    return x * x + y * y + z * z;
}

bool TVector4::IsEqual(const TVector4& other) const
{
    if (x == other.x && y == other.y && z == other.z && w == other.w)
    {
        return true;
    }
    return false;
}

float TVector4::DistanceSq(const TVector4& a, const TVector4& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    return dx * dx + dy * dy + dz * dz;
}

float TVector4::Distance(const TVector4& a, const TVector4& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

void TVector4::CrossProduct(const TVector4& a, const TVector4& b)
{
    float cx = a.y * b.z - a.z * b.y;
    float cy = a.z * b.x - a.x * b.z;
    float cz = a.x * b.y - a.y * b.x;
    float cw = a.w;
    x = cx;
    y = cy;
    z = cz;
    w = cw;
}

void TVector4::Lerp(const TVector4& other, float t)
{
    Lerp(*this, other, t);
}

void TVector4::Lerp3(const TVector4& other, float t)
{
    Lerp3(*this, other, t);
}

void TVector4::Lerp(const TVector4& a, const TVector4& b, float t)
{
    x = a.x + (b.x - a.x) * t;
    y = a.y + (b.y - a.y) * t;
    z = a.z + (b.z - a.z) * t;
    w = a.w + (b.w - a.w) * t;
}

void TVector4::Lerp3(const TVector4& a, const TVector4& b, float t)
{
    x = a.x + (b.x - a.x) * t;
    y = a.y + (b.y - a.y) * t;
    z = a.z + (b.z - a.z) * t;
    w = a.w;
}

void TVector4::Negate()
{
    Negate3();
}

void TVector4::Negate(const TVector4& other)
{
    Negate3(other);
}

void TVector4::Negate3()
{
    x = -x;
    y = -y;
    z = -z;
}

void TVector4::Negate3(const TVector4& other)
{
    x = -other.x;
    y = -other.y;
    z = -other.z;
    w = other.w;
}

void TVector4::Negate4()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

void TVector4::Negate4(const TVector4& other)
{
    x = -other.x;
    y = -other.y;
    z = -other.z;
    w = -other.w;
}

void TVector4::Abs()
{
    x = (float)fabs(x);
    y = (float)fabs(y);
    z = (float)fabs(z);
    w = (float)fabs(w);
}

void TVector4::Abs(const TVector4& other)
{
    x = (float)fabs(other.x);
    y = (float)fabs(other.y);
    z = (float)fabs(other.z);
    w = (float)fabs(other.w);
}

void TVector4::Sin(const TVector4& other)
{
    x = (float)sin(other.x);
    y = (float)sin(other.y);
    z = (float)sin(other.z);
    w = (float)sin(other.w);
}

void TVector4::Cos(const TVector4& other)
{
    x = (float)cos(other.x);
    y = (float)cos(other.y);
    z = (float)cos(other.z);
    w = (float)cos(other.w);
}

void TVector4::Add(const TVector4& a, const TVector4& b)
{
    x = a.x + b.x;
    y = a.y + b.y;
    z = a.z + b.z;
    w = a.w;
}

void TVector4::Subtract(const TVector4& a, const TVector4& b)
{
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
    w = a.w;
}

void TVector4::Subtract4(const TVector4& a, const TVector4& b)
{
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
    w = a.w - b.w;
}

void TVector4::Multiply(const TVector4& a, const TVector4& b)
{
    x = a.x * b.x;
    y = a.y * b.y;
    z = a.z * b.z;
    w = a.w;
}

void TVector4::Multiply(const TVector4& a, float scalar)
{
    x = a.x * scalar;
    y = a.y * scalar;
    z = a.z * scalar;
    w = a.w;
}

void TVector4::Divide(const TVector4& a, const TVector4& b)
{
    x = a.x / b.x;
    y = a.y / b.y;
    z = a.z / b.z;
    w = a.w;
}

void TVector4::Subtract(const TVector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

void TVector4::Multiply4(const TVector4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
}

void TVector4::Divide(const TVector4& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
}

void TVector4::Multiply(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void TVector4::Multiply(const TVector4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
}

void TVector4::Add(const TVector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

template <class T>
static inline const T& MaxOf(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

template <class T>
static inline const T& MinOf(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

void TVector4::Max(const TVector4& a, const TVector4& b)
{
    x = MaxOf(a.x, b.x);
    y = MaxOf(a.y, b.y);
    z = MaxOf(a.z, b.z);
    w = MaxOf(a.w, b.w);
}

void TVector4::Max(const TVector4& a, float s)
{
    x = MaxOf(a.x, s);
    y = MaxOf(a.y, s);
    z = MaxOf(a.z, s);
    w = MaxOf(a.w, s);
}

void TVector4::Min(const TVector4& a, const TVector4& b)
{
    x = MinOf(a.x, b.x);
    y = MinOf(a.y, b.y);
    z = MinOf(a.z, b.z);
    w = MinOf(a.w, b.w);
}

void TVector4::Min(const TVector4& a, float s)
{
    x = MinOf(a.x, s);
    y = MinOf(a.y, s);
    z = MinOf(a.z, s);
    w = MinOf(a.w, s);
}

void TVector4::Max(const TVector4& other)
{
    x = MaxOf(x, other.x);
    y = MaxOf(y, other.y);
    z = MaxOf(z, other.z);
    w = MaxOf(w, other.w);
}

void TVector4::Max(float s)
{
    x = MaxOf(x, s);
    y = MaxOf(y, s);
    z = MaxOf(z, s);
    w = MaxOf(w, s);
}

void TVector4::Min(const TVector4& other)
{
    x = MinOf(x, other.x);
    y = MinOf(y, other.y);
    z = MinOf(z, other.z);
    w = MinOf(w, other.w);
}

void TVector4::Min(float s)
{
    x = MinOf(x, s);
    y = MinOf(y, s);
    z = MinOf(z, s);
    w = MinOf(w, s);
}

void TVector4::Divide(const TVector4& a, float s)
{
    float inv = 1.0f / s;
    x = a.x * inv;
    y = a.y * inv;
    z = a.z * inv;
    w = a.w;
}

void TVector4::Divide(float s)
{
    float inv = 1.0f / s;
    x *= inv;
    y *= inv;
    z *= inv;
}

void TVector4::Normalise()
{
    float lengthSq = x * x + y * y + z * z;
    if (lengthSq == 0.0f) {
        x = 0.0f;
        y = 0.0f;
        z = 1.0f;
    } else {
        float inv = 1.0f / (float)sqrt(lengthSq);
        x *= inv;
        y *= inv;
        z *= inv;
    }
}


void TVector4::RotateX(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float rotatedY = c * y + -s * z;
    float rotatedZ = y * s + z * c;
    y = rotatedY;
    z = rotatedZ;
}

void TVector4::RotateY(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float rotatedX = c * x + s * z;
    float rotatedZ = -s * x + z * c;
    x = rotatedX;
    z = rotatedZ;
}

} // namespace Toshi
