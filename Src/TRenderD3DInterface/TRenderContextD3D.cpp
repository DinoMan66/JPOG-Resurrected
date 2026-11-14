// Toshi::TRenderContextD3D.
// Source: Z:\Toshi\Source\TRenderD3D\TRenderContextD3D.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TRenderContextD3D.h"
#include "TRenderD3DInterface.h"

namespace Toshi {

TRenderContextD3D::TRenderContextD3D(TRenderD3DInterface& renderer)
    : TRenderContext(renderer)
{
}

TRenderContextD3D::~TRenderContextD3D()
{
}

TRenderD3DInterface& TRenderContextD3D::GetRenderer()
{
    return *(TRenderD3DInterface*)m_pRenderer;
}

void TRenderContextD3D::Update()
{
    if (IsDirty())
    {
        if (m_eProjType == PROJTYPE_PERSPECTIVE)
        {
            ComputePerspectiveProjection();
            ComputePerspectiveFrustum();
        }
        else
        {
            ComputeOrthographicProjection();
            ComputeOrthographicFrustum();
        }
    }
    SetRenderMatrices();
}

void TRenderContextD3D::SetRenderMatrices()
{
    IDirect3DDevice8* device = GetRenderer().GetD3DDevice();
    device->SetTransform(D3DTS_VIEW, (const D3DMATRIX*)&TMatrix44::IDENTITY);
    device = GetRenderer().GetD3DDevice();
    device->SetTransform(D3DTS_PROJECTION, (const D3DMATRIX*)&m_oViewProjectionMatrix);
}

} // namespace Toshi
