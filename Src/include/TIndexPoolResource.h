// Toshi::TIndexPoolResource - the Direct3D index pool: a range of indices inside a TIndexBlockResource.
// Size 0x48. The pool is a child of its block in the resource tree.
#ifndef TINDEXPOOLRESOURCE_H
#define TINDEXPOOLRESOURCE_H
#include "TRenderD3DAPI.h"
#include "TIndexPoolResourceInterface.h"

namespace Toshi {

class TIndexBlockResource;
class TIndexFactoryResource;

class TRENDERD3D_API TIndexPoolResource : public TIndexPoolResourceInterface
{
    TOSHI_DECLARE_CLASS(TIndexPoolResource)
public:
    TIndexPoolResource();
    virtual ~TIndexPoolResource();
    virtual void Invalidate();
    virtual bool Lock(LockBuffer* buffer);
    virtual void Unlock(unsigned short newNumIndices);

    TIndexFactoryResource* GetFactory();
    TIndexBlockResource* GetIndexBlock();
    unsigned short* GetManagedBuffer();

protected:
    virtual void OnDestroy();
    virtual bool Create(TIndexFactoryResourceInterface* factory, unsigned int maxIndices, unsigned int flags);

private:
    /* 0x3C */ unsigned short  m_usUnk3C;
    /* 0x40 */ unsigned short* m_pManagedBuffer;    // CPU copy of the indices, only when the flags ask for it
    /* 0x44 */ int             m_unk44;
};

} // namespace Toshi
#endif
