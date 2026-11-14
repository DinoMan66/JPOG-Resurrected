// Toshi::TVertexPoolResource - the Direct3D vertex pool: a range of vertices inside a TVertexBlockResource.
// Size 0x64. The pool is a child of its block in the resource tree.
#ifndef TVERTEXPOOLRESOURCE_H
#define TVERTEXPOOLRESOURCE_H
#include "TRenderD3DAPI.h"
#include "TVertexPoolResourceInterface.h"

namespace Toshi {

class TVertexBlockResource;
class TVertexFactoryResource;

class TRENDERD3D_API TVertexPoolResource : public TVertexPoolResourceInterface
{
    TOSHI_DECLARE_CLASS(TVertexPoolResource)
public:
    TVertexPoolResource();
    virtual ~TVertexPoolResource();
    virtual void Invalidate();
    virtual bool Lock(LockBuffer* buffer);
    virtual void Unlock(unsigned short newNumVertices);

    TVertexFactoryResource* GetFactory();
    TVertexBlockResource* GetVertexBlock();
    unsigned char* GetManagedStream(unsigned int stream);

protected:
    virtual void OnDestroy();
    virtual bool Create(TVertexFactoryResourceInterface* factory, unsigned int maxVertices, unsigned int flags);

private:
    /* 0x3C */ unsigned short m_usUnk3C;
    /* 0x40 */ unsigned char* m_apManagedStreams[8];    // CPU copy of each vertex stream, only when the flags ask for it
    /* 0x60 */ int            m_unk60;
};

} // namespace Toshi
#endif
