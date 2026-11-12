// Z:\Toshi\Source\TKernel\TPlane.cpp - plane stored as normal (xyz) and distance (w).
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TVector.h"

namespace Toshi {

TPlane::TPlane(const TVector3& n, const TVector3& point)
{
    SetNormal(n);
    SetD(TVector3::DotProduct(n, point));
}

void TPlane::Set(const TVector3& n, const TVector3& point)
{
    SetNormal(n);
    SetD(TVector3::DotProduct(n, point));
}

void TPlane::Negate()
{
    m_oPlane.Negate4();
}

void TPlane::Negate(const TPlane& p)
{
    m_oPlane.Negate4(p.m_oPlane);
}

void TPlane::SetPoint(const TVector3& point)
{
    SetD(TVector3::DotProduct(GetNormal(), point));
}

void TPlane::GetPoint(TVector3& point) const
{
    point.Multiply(GetNormal(), GetD());
}

} // namespace Toshi
