// Toshi::TRenderCaptureD3D (TRenderD3DInterface.dll, TRenderCaptureD3D.cpp) - screen capture
// through Direct3D 8. Size 0x1c.
#ifndef TRENDERCAPTURED3D_H
#define TRENDERCAPTURED3D_H
#include "TRenderCapture.h"
#include "TRenderD3DAPI.h"

namespace Toshi {

class TRENDERD3D_API TRenderCaptureD3D : public TRenderCapture
{
public:
    TRenderCaptureD3D();
    virtual ~TRenderCaptureD3D();

    virtual bool Create(FORMAT format, int width, int height);
    virtual void Destroy();
    virtual bool Request();
    virtual bool Wait();
    virtual bool Poll();
    virtual void* ObtainBuffer();
    virtual void ReleaseBuffer();

private:
    /* 0x04 */ void*  m_pBuffer;
    /* 0x08 */ FORMAT m_eFormat;
    /* 0x0C */ int    m_iWidth;
    /* 0x10 */ int    m_iHeight;
    /* 0x14 */ int    m_unk14;
    /* 0x18 */ bool   m_unk18;
};

} // namespace Toshi
#endif
