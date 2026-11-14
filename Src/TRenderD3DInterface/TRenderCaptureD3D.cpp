// Toshi::TRenderCaptureD3D.
// Source: Z:\Toshi\Source\TRenderD3D\TRenderCaptureD3D.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TRenderCaptureD3D.h"
#include "TMemory.h"

namespace Toshi {

TRenderCaptureD3D::TRenderCaptureD3D()
    : m_pBuffer(0), m_unk14(0), m_unk18(false)
{
}

TRenderCaptureD3D::~TRenderCaptureD3D()
{
    ReleaseBuffer();
}

bool TRenderCaptureD3D::Create(FORMAT format, int width, int height)
{
    m_eFormat = format;
    m_iWidth = width;
    m_iHeight = height;
    return true;
}

void TRenderCaptureD3D::Destroy()
{
    ReleaseBuffer();
}

bool TRenderCaptureD3D::Wait()
{
    return true;
}

bool TRenderCaptureD3D::Poll()
{
    return m_pBuffer != 0;
}

void* TRenderCaptureD3D::ObtainBuffer()
{
    return m_pBuffer;
}

void TRenderCaptureD3D::ReleaseBuffer()
{
    if (m_pBuffer != 0)
    {
        tfree(m_pBuffer);
        m_pBuffer = 0;
    }
}

} // namespace Toshi
