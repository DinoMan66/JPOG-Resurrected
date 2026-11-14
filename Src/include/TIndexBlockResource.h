// Toshi::TIndexBlockResource (TRenderD3DInterface.dll, TD3DIndexBlockResource.cpp) - a Direct3D
// index buffer shared by the index pools attached to it. Size 0x54.
#ifndef TINDEXBLOCKRESOURCE_H
#define TINDEXBLOCKRESOURCE_H
#include "TResource.h"
#include "TFreeList.h"
#include "TRenderD3DAPI.h"
#include "d3d8min.h"

namespace Toshi {

class TIndexFactoryResource;
class TIndexPoolResource;

class TRENDERD3D_API TIndexBlockResource : public TResource
{
    TOSHI_DECLARE_CLASS(TIndexBlockResource)
    TOSHI_FREELIST_DECLARE()
public:
    class HALBuffer;

    TIndexBlockResource();
    virtual ~TIndexBlockResource();

    virtual bool Validate();
    virtual void Invalidate();
    virtual bool OnLostDevice();
    virtual bool OnResetDevice();

    bool Create(TIndexFactoryResource* factory, unsigned short maxIndices, unsigned int flags);
    bool AttachPool(TIndexPoolResource* pool);
    bool DetachPool(TIndexPoolResource* pool);
    bool CanFit(TIndexPoolResource* pool);
    bool GetHAL(HALBuffer* buffer);
    void Unlock();
    bool IsLocked();
    void ChildIndexUsedChanged(int delta);
    unsigned int GetFlags();
    unsigned int GetIndicesUsed() const;
    unsigned short GetMaxIndices() const;
    TIndexFactoryResource* GetFactory();

    static int s_iHALMemoryUsage;

protected:
    bool CreateHAL();
    void DestroyHAL();

private:

    /* 0x30 */ TIndexFactoryResource* m_pFactory;
    /* 0x34 */ unsigned int           m_uiFlags;
    /* 0x38 */ unsigned short         m_usMaxIndices;
    /* 0x3C */ int                    m_unk3C;
    /* 0x40 */ unsigned int           m_uiIndicesUsed;
    /* 0x44 */ unsigned int           m_uiLockCount;
    /* 0x48 */ int                    m_unk48;
    /* 0x4C */ unsigned short        m_usUnk4C;
    /* 0x4E */ unsigned short        m_usUnk4E;
    /* 0x50 */ IDirect3DIndexBuffer8* m_pD3DIndexBuffer;
};

} // namespace Toshi
#endif
