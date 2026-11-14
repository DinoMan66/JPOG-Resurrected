// Toshi::TTextureResourceHAL (TRenderD3DInterface.dll, TTextureResourceHAL.cpp). Direct3D 8
// implementation of TTextureResource; objects come from a free list (class operator new/delete).
// Only the members whose bodies are written so far are declared in full.
#ifndef TTEXTURERESOURCEHAL_H
#define TTEXTURERESOURCEHAL_H
#include "TTextureResource.h"
#include "TFreeList.h"
#include "TRenderD3DAPI.h"
#include "d3d8min.h"

namespace Toshi {

class TRenderD3DInterface;

class TRENDERD3D_API TTextureResourceHAL : public TTextureResource     // 0x78
{
    TOSHI_DECLARE_CLASS(TTextureResourceHAL)
    TOSHI_FREELIST_DECLARE()
public:
    TTextureResourceHAL();
    virtual ~TTextureResourceHAL();

    virtual bool Validate();
    virtual void Invalidate();
    virtual void DestroyResource();
    virtual void Unlock();
    virtual int GetWidth();
    virtual int GetHeight();

protected:
    virtual bool Create(void* data, unsigned int dataSize, unsigned int flags,
                        unsigned int width, unsigned int height);
    virtual bool Create(const char* fileName, unsigned int flags);
    virtual bool CreateEx(void* data, unsigned int dataSize, unsigned int width, unsigned int height,
                          unsigned int mipLevels, TTEXTURERESOURCEFORMAT format, unsigned int flags);

    bool IsPPM(const char* fileName);

public:
    IDirect3DTexture8* GetD3DTexture() { return m_pD3DTexture; }
    TRenderD3DInterface* GetRenderer() const;

private:
    bool CreateFromPPMFile(const char* fileName);

    /* 0x3C */ unsigned int m_uiLockCount;
    /* 0x40 */ bool m_bUnk40;
    /* 0x44 */ void* m_pData;
    /* 0x48 */ unsigned int m_uiDataSize;
    /* 0x4C */ unsigned int m_unk4C;
    /* 0x50 */ unsigned int m_unk50;
    /* 0x54 */ unsigned int m_unk54;
    /* 0x58 */ unsigned int m_unk58;
    /* 0x5C */ unsigned int m_unk5C;
    /* 0x60 */ IDirect3DTexture8* m_pD3DTexture;
    /* 0x64 */ int  m_iWidth;
    /* 0x68 */ int  m_iHeight;
    /* 0x6C */ int  m_unk6C[3];
};

} // namespace Toshi
#endif
