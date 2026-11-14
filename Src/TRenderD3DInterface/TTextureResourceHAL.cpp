// Toshi::TTextureResourceHAL - accessors and class boilerplate.
// Source unit: Z:\Toshi\Source\TRenderD3D\TTextureResourceD3D.cpp (path string in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TTextureResourceHAL.h"
#include "TNewDelete.h"
#include "TSystem.h"
#include "TRenderD3DInterface.h"

namespace Toshi {

TTextureResourceHAL::TTextureResourceHAL()
    : m_uiLockCount(0), m_bUnk40(false), m_pData(0), m_uiDataSize(0), m_pD3DTexture(0)
{
}

TTextureResourceHAL::~TTextureResourceHAL()
{
}

bool TTextureResourceHAL::Create(void* data, unsigned int dataSize, unsigned int flags,
                                 unsigned int width, unsigned int height)
{
    if (!TTextureResource::Create(data, dataSize, flags, 0, 0))
        return false;
    m_uiCreateFlags = flags;
    m_unk4C = width;
    m_unk50 = height;
    m_unk54 = 0;
    m_unk5C = 0;
    m_unk58 = 1;
    m_bUnk40 = true;
    m_pData = data;
    m_uiDataSize = dataSize;
    Validate();
    return true;
}

bool TTextureResourceHAL::Create(const char* fileName, unsigned int flags)
{
    if (!TTextureResource::Create(fileName, flags))
        return false;
    m_uiCreateFlags = flags;
    m_unk58 = 1;
    return true;
}

bool TTextureResourceHAL::CreateEx(void* data, unsigned int dataSize, unsigned int width, unsigned int height,
                                   unsigned int mipLevels, TTEXTURERESOURCEFORMAT format, unsigned int flags)
{
    if (!TTextureResource::CreateEx(data, dataSize, width, height, mipLevels, format, flags))
        return false;
    m_uiCreateFlags = 0x40;
    m_unk4C = width;
    m_unk50 = height;
    m_unk54 = mipLevels;
    m_unk5C = format;
    m_unk58 = flags;
    m_bUnk40 = true;
    m_pData = data;
    m_uiDataSize = dataSize;
    Validate();
    return true;
}

bool TTextureResourceHAL::IsPPM(const char* fileName)
{
    int length = TSystem::StringLength(fileName);
    if (length >= 4 && TSystem::StringCompareNoCase(fileName + length - 4, ".ppm", -1) == 0)
        return true;
    return false;
}

bool TTextureResourceHAL::CreateFromPPMFile(const char* fileName)
{
    return false;
}

void TTextureResourceHAL::Unlock()
{
    if (m_uiLockCount > 0 && m_pD3DTexture != 0)
    {
        m_pD3DTexture->UnlockRect(0);
        m_uiLockCount--;
    }
}

TRenderD3DInterface* TTextureResourceHAL::GetRenderer() const
{
    return (TRenderD3DInterface*)TResource::GetRenderer();
}

int TTextureResourceHAL::GetWidth()
{
    Validate();
    return m_iWidth;
}

int TTextureResourceHAL::GetHeight()
{
    Validate();
    return m_iHeight;
}

void TTextureResourceHAL::DestroyResource()
{
    TTextureResource::DestroyResource();
}

TOSHI_DEFINE_CLASS(TTextureResourceHAL, TTextureResource)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TTextureResourceHAL)

} // namespace Toshi
