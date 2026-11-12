// Z:\Toshi\Source\TKernel\TSphere.cpp - bounding sphere stored as origin (xyz) and radius (w).
// Union is not written yet.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TVector.h"

namespace Toshi {

TPlane::PlaneComparison TSphere::ComparePlane(TPlane& plane)
{
    float distance = TVector3::DotProduct(plane.GetNormal(), GetOrigin()) - plane.GetD();

    // Signs as the binary has them: a sphere in front of the plane reports PLANE_NEGATIVE.
    if (distance > GetRadius())
    {
        return TPlane::PLANE_NEGATIVE;
    }
    if (distance < -GetRadius())
    {
        return TPlane::PLANE_POSITIVE;
    }
    return TPlane::PLANE_CROSSING;
}

} // namespace Toshi
