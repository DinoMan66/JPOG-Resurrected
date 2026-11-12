// Z:\Toshi\Source\TKernel\TAABox.cpp - axis-aligned bounding box (centre + half-extents).
// BoxUnion is not written yet.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TVector.h"

namespace Toshi {

TAABox::TAABox()
{
}

TAABox::TAABox(const TAABox& other)
{
    m_oCentre = other.m_oCentre;
    m_oBounds = other.m_oBounds;
}

TAABox::TAABox(const float& cx, const float& cy, const float& cz,
               const float& bx, const float& by, const float& bz)
{
    m_oCentre.Set(cx, cy, cz);
    m_oBounds.Set(bx, by, bz);
}

TAABox& TAABox::operator=(const TAABox& other)
{
    m_oCentre = other.m_oCentre;
    m_oBounds = other.m_oBounds;
    return *this;
}

void TAABox::SetBox(const float& cx, const float& cy, const float& cz,
                    const float& bx, const float& by, const float& bz)
{
    m_oCentre.Set(cx, cy, cz);
    m_oBounds.Set(bx, by, bz);
}

void TAABox::SetBounds(const TVector3& bounds)
{
    m_oBounds = bounds;
}

void TAABox::SetCentre(const TVector3& centre)
{
    m_oCentre = centre;
}

const TVector3& TAABox::GetBounds() const
{
    return m_oBounds;
}

const TVector3& TAABox::GetCentre() const
{
    return m_oCentre;
}

TPlane::PlaneComparison TAABox::ComparePlane(TPlane& plane)
{
    TVector3 absNormal;
    absNormal.Abs(plane.GetNormal());

    // Signed distance of the centre, and how far the box reaches towards the plane along its normal.
    float distance = TVector3::DotProduct(m_oCentre, plane.GetNormal()) - plane.GetD();
    float extent = TVector3::DotProduct(m_oBounds, absNormal);

    if (distance + extent < 0.0f)
    {
        return TPlane::PLANE_NEGATIVE;
    }
    if (distance - extent > 0.0f)
    {
        return TPlane::PLANE_POSITIVE;
    }
    return TPlane::PLANE_CROSSING;
}

} // namespace Toshi
