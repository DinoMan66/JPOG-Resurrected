// Z:\Toshi\Source\TKernel\TVector2.cpp - 2D vector arithmetic.
// Not written yet: Normalise, IsNormalised, Rotate, SubXZ, Divide(float), Divide(vec, float).
// Set(x, y), the (x, y) constructor and the copy operations stay inline in TVector.h.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include <math.h>
#include "TKernelMisc.h"
#include "TVector.h"

namespace Toshi {

TVector2::TVector2(const float* const values)
{
    Set(values);
}

void TVector2::Set(const float* const values)
{
    x = values[0];
    y = values[1];
}

bool TVector2::operator==(const TVector2& other) const
{
    return IsEqual(other);
}

bool TVector2::operator!=(const TVector2& other) const
{
    return !IsEqual(other);
}

TVector2& TVector2::operator/=(float scalar)
{
    Divide(scalar);
    return *this;
}

TVector2& TVector2::operator/=(const TVector2& other)
{
    Divide(other);
    return *this;
}

TVector2& TVector2::operator*=(float scalar)
{
    Multiply(scalar);
    return *this;
}

TVector2& TVector2::operator*=(const TVector2& other)
{
    Multiply(other);
    return *this;
}

TVector2& TVector2::operator-=(const TVector2& other)
{
    Subtract(other);
    return *this;
}

TVector2& TVector2::operator+=(const TVector2& other)
{
    Add(other);
    return *this;
}

const float& TVector2::operator()(unsigned int index) const
{
    return (&x)[index];
}

float& TVector2::operator()(unsigned int index)
{
    return (&x)[index];
}

float TVector2::CrossProduct(const TVector2& other) const
{
    return CrossProduct(*this, other);
}

float TVector2::DotProduct(const TVector2& other) const
{
    return DotProduct(*this, other);
}

float TVector2::CrossProduct(const TVector2& a, const TVector2& b)
{
    return a.x * b.y - a.y * b.x;
}

float TVector2::DotProduct(const TVector2& a, const TVector2& b)
{
    return a.x * b.x + a.y * b.y;
}

float TVector2::Magnitude() const
{
    return (float)sqrt(x * x + y * y);
}

float TVector2::MagnitudeSq() const
{
    return x * x + y * y;
}

bool TVector2::IsEqual(const TVector2& other) const
{
    if (x == other.x && y == other.y)
    {
        return true;
    }
    return false;
}

float TVector2::DistanceSq(const TVector2& a, const TVector2& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return dx * dx + dy * dy;
}

float TVector2::Distance(const TVector2& a, const TVector2& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return (float)sqrt(dx * dx + dy * dy);
}

void TVector2::Lerp(const TVector2& a, const TVector2& b, float t)
{
    x = a.x + (b.x - a.x) * t;
    y = a.y + (b.y - a.y) * t;
}

TVector3 TVector2::GetVector3XZ() const
{
    return TVector3(x, 0.0f, y);
}

TVector3 TVector2::GetVector3XY() const
{
    return TVector3(x, y, 0.0f);
}

void TVector2::SetXZFromVector3(const TVector3& v)
{
    x = v.x;
    y = v.z;
}

void TVector2::SetXYFromVector3(const TVector3& v)
{
    x = v.x;
    y = v.y;
}

void TVector2::AddXZ(TVector3& result, const TVector3& a, const TVector2& b)
{
    result.x = a.x + b.x;
    result.y = a.y;
    result.z = a.z + b.y;
}

void TVector2::SetPerpendicular()
{
    float negatedY = -y;
    float oldX = x;
    x = negatedY;
    y = oldX;
}

void TVector2::Divide(const TVector2& other)
{
    x /= other.x;
    y /= other.y;
}

void TVector2::Multiply(float scalar)
{
    x *= scalar;
    y *= scalar;
}

void TVector2::Multiply(const TVector2& other)
{
    x *= other.x;
    y *= other.y;
}

void TVector2::Subtract(const TVector2& other)
{
    x -= other.x;
    y -= other.y;
}

void TVector2::Add(const TVector2& other)
{
    x += other.x;
    y += other.y;
}

void TVector2::Negate()
{
    x = -x;
    y = -y;
}

void TVector2::Abs()
{
    x = (float)fabs(x);
    y = (float)fabs(y);
}

void TVector2::Divide(const TVector2& a, const TVector2& b)
{
    x = a.x / b.x;
    y = a.y / b.y;
}

void TVector2::Multiply(const TVector2& a, float scalar)
{
    x = a.x * scalar;
    y = a.y * scalar;
}

void TVector2::Multiply(const TVector2& a, const TVector2& b)
{
    x = a.x * b.x;
    y = a.y * b.y;
}

void TVector2::Subtract(const TVector2& a, const TVector2& b)
{
    x = a.x - b.x;
    y = a.y - b.y;
}

void TVector2::Add(const TVector2& a, const TVector2& b)
{
    x = a.x + b.x;
    y = a.y + b.y;
}

void TVector2::Negate(const TVector2& other)
{
    x = -other.x;
    y = -other.y;
}

void TVector2::Abs(const TVector2& other)
{
    x = (float)fabs(other.x);
    y = (float)fabs(other.y);
}

void TVector2::Divide(float s)
{
    float inv = 1.0f / s;
    x *= inv;
    y *= inv;
}

void TVector2::Divide(const TVector2& a, float s)
{
    float inv = 1.0f / s;
    x = a.x * inv;
    y = a.y * inv;
}

void TVector2::Normalise()
{
    float lengthSq = x * x + y * y;
    if (lengthSq == 0.0f) {
        x = 1.0f;
        y = 0.0f;
    } else {
        float inv = 1.0f / (float)sqrt(lengthSq);
        x *= inv;
        y *= inv;
    }
}


void __stdcall TVector2::SubXZ(TVector3& result, const TVector3& a, const TVector2& b)
{
    result.x = a.x - b.x;
    result.y = a.y;
    result.z = a.z - b.y;
}


void TVector2::Rotate(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float rotatedX = c * x + s * y;
    float rotatedY = -s * x + c * y;
    x = rotatedX;
    y = rotatedY;
}


bool TVector2::IsNormalised(float tolerance) const
{
    float lengthSq = x * x + y * y;
    if ((1.0f - tolerance) * (1.0f - tolerance) < lengthSq && lengthSq < (tolerance + 1.0f) * (tolerance + 1.0f)) {
        return true;
    }
    return false;
}

} // namespace Toshi
