// Toshi::TRenderContextD3D (TRenderD3DInterface.dll, TRenderContextD3D.cpp) - render context that
// also keeps the combined view-projection matrix. Size 0x4c4.
#ifndef TRENDERCONTEXTD3D_H
#define TRENDERCONTEXTD3D_H
#include "TRenderContext.h"
#include "TRenderD3DAPI.h"

namespace Toshi {

class TRenderD3DInterface;

class TRENDERD3D_API TRenderContextD3D : public TRenderContext
{
public:
    TRenderContextD3D(TRenderD3DInterface& renderer);
    virtual ~TRenderContextD3D();
    virtual void Update();                                              // slot 3

    TMatrix44& GetViewProjectionMatrix() { return m_oViewProjectionMatrix; }
    TRenderD3DInterface& GetRenderer();

private:
    void ComputePerspectiveProjection();
    void ComputePerspectiveFrustum();
    void ComputeOrthographicProjection();
    void ComputeOrthographicFrustum();
    void SetRenderMatrices();

    /* 0x484 */ TMatrix44 m_oViewProjectionMatrix;
};

} // namespace Toshi
#endif
