// Z:\Toshi\Source\TKernel - members of TVector2/TVector3/TMatrix44 that call a small helper of
// their own class. The original calls those helpers out of line; our compiler build inlines a helper defined in
// the same file (MATCHING_NOTES #23), so these callers live in a file of their own.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TVector.h"

namespace Toshi {

TVector2 TVector2::operator/(float scalar) const
{
    TVector2 result;
    result.Divide(*this, scalar);
    return result;
}

TVector2 TVector2::operator/(const TVector2& other) const
{
    TVector2 result;
    result.Divide(*this, other);
    return result;
}

TVector2 TVector2::operator*(float scalar) const
{
    TVector2 result;
    result.Multiply(*this, scalar);
    return result;
}

TVector2 TVector2::operator*(const TVector2& other) const
{
    TVector2 result;
    result.Multiply(*this, other);
    return result;
}

TVector2 TVector2::operator-(const TVector2& other) const
{
    TVector2 result;
    result.Subtract(*this, other);
    return result;
}

TVector2 TVector2::operator+(const TVector2& other) const
{
    TVector2 result;
    result.Add(*this, other);
    return result;
}

TVector3 TVector3::operator*(float scalar) const
{
    TVector3 result;
    result.Multiply(*this, scalar);
    return result;
}

TMatrix44 TMatrix44::operator/(float s) const
{
    TMatrix44 result;
    result.Divide(*this, s);
    return result;
}

void TVector3::SetUnitVectorProjection(TVector3& onto)
{
    float scalar = GetScalarProjectionOnUnit(onto);
    TVector3 projection(onto.x * scalar, onto.y * scalar, scalar * onto.z);
    *this = projection;
}

} // namespace Toshi
