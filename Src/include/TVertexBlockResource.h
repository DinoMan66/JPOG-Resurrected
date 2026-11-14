// Toshi::TVertexBlockResource (TRenderD3DInterface.dll, TD3DVertexBlockResource.cpp) - a Direct3D
// vertex buffer shared by the vertex pools attached to it. Size 0x74.
#ifndef TVERTEXBLOCKRESOURCE_H
#define TVERTEXBLOCKRESOURCE_H
#include "TResource.h"
#include "TFreeList.h"
#include "TRenderD3DAPI.h"
#include "d3d8min.h"

namespace Toshi {

class TVertexFactoryResource;
class TVertexPoolResource;

class TRENDERD3D_API TVertexBlockResource : public TResource
{
    TOSHI_DECLARE_CLASS(TVertexBlockResource)
    TOSHI_FREELIST_DECLARE()
public:
    class HALBuffer;

    TVertexBlockResource();
    virtual ~TVertexBlockResource();

    virtual bool Validate();
    virtual void Invalidate();
    virtual bool OnLostDevice();
    virtual bool OnResetDevice();

    bool Create(TVertexFactoryResource* factory, unsigned short maxVertices, unsigned int flags);
    bool AttachPool(TVertexPoolResource* pool);
    bool DetachPool(TVertexPoolResource* pool);
    bool CanFit(TVertexPoolResource* pool);
    bool GetHAL(HALBuffer* buffer);
    void Unlock();
    bool IsLocked();
    void ChildVertexUsedChanged(int delta);
    unsigned int GetFlags();
    unsigned int GetVerticesUsed() const;
    unsigned short GetMaxVertices() const;
    TVertexFactoryResource* GetFactory();

    static int s_iTotalVertexBufferBytesAllocated;
    static int s_iHALMemoryUsage;
    static int s_iCurrentNumHALCreated;
    static int s_iTotalNumHALCreated;
    static int s_iTotalNumHALDestroyed;
    static int s_iCurrentVertexBufferBytesAllocated;
    static int s_iWastedVertexBufferBytesAllocated;

protected:
    bool CreateHAL();
    void DestroyHAL();

private:

    /* 0x30 */ TVertexFactoryResource* m_pFactory;
    /* 0x34 */ unsigned int            m_uiFlags;
    /* 0x38 */ unsigned short          m_usMaxVertices;
    /* 0x3C */ int                     m_unk3C;
    /* 0x40 */ unsigned int            m_uiVerticesUsed;
    /* 0x44 */ unsigned int            m_uiLockCount;
    /* 0x48 */ int                     m_unk48;
    /* 0x4C */ unsigned int            m_uiNumStreams;
    /* 0x50 */ unsigned short          m_unk50;
    /* 0x54 */ IDirect3DVertexBuffer8* m_apD3DBuffers[8];
};

} // namespace Toshi
#endif
