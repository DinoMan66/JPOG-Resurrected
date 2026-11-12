// Z:\Toshi\Source\TKernel\TVector3.cpp - 3D vector arithmetic.
// Not written yet: Normalise, IsNormalised, IsReasonable, Divide(float), Divide(vec, float), the Rotate* functions,
// SetVectorProjection/GetScalarProjection and the VEC_* constants.
// Set(x, y, z), the (x, y, z) constructor and the copy operations stay inline in TVector.h.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include <math.h>
#include "TKernelMisc.h"
#include "TVector.h"

namespace Toshi {

TVector3::TVector3(const float* const values)
{
    Set(values);
}

void TVector3::Set(const float* const values)
{
    x = values[0];
    y = values[1];
    z = values[2];
}

bool TVector3::operator==(const TVector3& other) const
{
    return IsEqual(other);
}

bool TVector3::operator!=(const TVector3& other) const
{
    return !IsEqual(other);
}

TVector3& TVector3::operator/=(float scalar)
{
    Divide(scalar);
    return *this;
}

TVector3& TVector3::operator/=(const TVector3& other)
{
    Divide(other);
    return *this;
}

TVector3& TVector3::operator*=(float scalar)
{
    Multiply(scalar);
    return *this;
}

TVector3& TVector3::operator*=(const TVector3& other)
{
    Multiply(other);
    return *this;
}

TVector3& TVector3::operator-=(const TVector3& other)
{
    Subtract(other);
    return *this;
}

TVector3& TVector3::operator+=(const TVector3& other)
{
    Add(other);
    return *this;
}

const float& TVector3::operator()(unsigned int index) const
{
    return (&x)[index];
}

float& TVector3::operator()(unsigned int index)
{
    return (&x)[index];
}

TVector3 TVector3::operator/(const TVector3& other) const
{
    TVector3 result;
    result.Divide(*this, other);
    return result;
}

TVector3 TVector3::operator-(const TVector3& other) const
{
    TVector3 result;
    result.Subtract(*this, other);
    return result;
}

TVector3 TVector3::operator+(const TVector3& other) const
{
    TVector3 result;
    result.Add(*this, other);
    return result;
}

float TVector3::DotProduct(const TVector3& other) const
{
    return DotProduct(*this, other);
}

float TVector3::DotProduct(const TVector3& a, const TVector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float TVector3::Magnitude() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

float TVector3::MagnitudeSq() const
{
    return x * x + y * y + z * z;
}

bool TVector3::IsEqual(const TVector3& other) const
{
    if (x == other.x && y == other.y && z == other.z)
    {
        return true;
    }
    return false;
}

float TVector3::DistanceSq(const TVector3& a, const TVector3& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    return dx * dx + dy * dy + dz * dz;
}

float TVector3::Distance(const TVector3& a, const TVector3& b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;
    return (float)sqrt(dx * dx + dy * dy + dz * dz);
}

void TVector3::Abs(const TVector3& other)
{
    x = (float)fabs(other.x);
    y = (float)fabs(other.y);
    z = (float)fabs(other.z);
}

void TVector3::Abs()
{
    x = (float)fabs(x);
    y = (float)fabs(y);
    z = (float)fabs(z);
}

void TVector3::Add(const TVector3& a, const TVector3& b)
{
    x = a.x + b.x;
    y = a.y + b.y;
    z = a.z + b.z;
}

void TVector3::Subtract(const TVector3& a, const TVector3& b)
{
    x = a.x - b.x;
    y = a.y - b.y;
    z = a.z - b.z;
}

void TVector3::Multiply(const TVector3& a, const TVector3& b)
{
    x = a.x * b.x;
    y = a.y * b.y;
    z = a.z * b.z;
}

void TVector3::Divide(const TVector3& a, const TVector3& b)
{
    x = a.x / b.x;
    y = a.y / b.y;
    z = a.z / b.z;
}

void TVector3::Add(const TVector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}

void TVector3::Subtract(const TVector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

void TVector3::Multiply(const TVector3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
}

void TVector3::Divide(const TVector3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
}

void TVector3::Multiply(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void TVector3::Multiply(const TVector3& other, float scalar)
{
    x = other.x * scalar;
    y = other.y * scalar;
    z = other.z * scalar;
}

void TVector3::Negate()
{
    x = -x;
    y = -y;
    z = -z;
}

void TVector3::Negate(const TVector3& other)
{
    x = -other.x;
    y = -other.y;
    z = -other.z;
}

void TVector3::CrossProduct(const TVector3& a, const TVector3& b)
{
    float cx = a.y * b.z - a.z * b.y;
    float cy = a.z * b.x - a.x * b.z;
    float cz = a.x * b.y - a.y * b.x;
    x = cx;
    y = cy;
    z = cz;
}

void TVector3::Lerp(const TVector3& a, const TVector3& b, float t)
{
    x = a.x + (b.x - a.x) * t;
    y = a.y + (b.y - a.y) * t;
    z = a.z + (b.z - a.z) * t;
}

void TVector3::Lerp(const TVector3& target, float t)
{
    x = x + (target.x - x) * t;
    y = y + (target.y - y) * t;
    z = z + (target.z - z) * t;
}

float TVector3::GetScalarProjectionOnUnit(TVector3& unit)
{
    return x * unit.x + y * unit.y + z * unit.z;
}

void TVector3::Divide(float s)
{
    float inv = 1.0f / s;
    x *= inv;
    y *= inv;
    z *= inv;
}

void TVector3::Divide(const TVector3& a, float s)
{
    float inv = 1.0f / s;
    x = a.x * inv;
    y = a.y * inv;
    z = a.z * inv;
}

void TVector3::Normalise()
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


bool TVector3::IsNormalised(float tolerance) const
{
    float lengthSq = x * x + y * y + z * z;
    if ((1.0f - tolerance) * (1.0f - tolerance) < lengthSq && lengthSq < (tolerance + 1.0f) * (tolerance + 1.0f)) {
        return true;
    }
    return false;
}

void TVector3::Clip(float minimum, float maximum)
{
    TMath::Clip(x, minimum, maximum);
    TMath::Clip(y, minimum, maximum);
    TMath::Clip(z, minimum, maximum);
}

float TVector3::GetScalarProjection(TVector3& onto)
{
    float ox = onto.x;
    float oy = onto.y;
    float oz = onto.z;
    return (z * oz + y * oy + x * ox) / (oz * oz + oy * oy + ox * ox);
}


void TVector3::RotateX(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float rotatedY = c * y + -s * z;
    float rotatedZ = y * s + z * c;
    y = rotatedY;
    z = rotatedZ;
}

void TVector3::RotateY(float angle)
{
    float s, c;
    TMath::SinCos(angle, s, c);
    float rotatedX = c * x + s * z;
    float rotatedZ = -s * x + z * c;
    x = rotatedX;
    z = rotatedZ;
}


void TVector3::SetVectorProjection(TVector3& onto)
{
    float scalar = GetScalarProjection(onto);
    TVector3 projection(onto.x * scalar, onto.y * scalar, scalar * onto.z);
    *this = projection;
}

bool TVector3::IsReasonable(float limit) const
{
    float negative = -limit;
    if (negative <= x && x <= limit && negative <= y && y <= limit && negative <= z && z <= limit) {
        return true;
    }
    return false;
}

} // namespace Toshi
