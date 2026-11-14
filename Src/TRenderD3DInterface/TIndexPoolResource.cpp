// Toshi::TIndexPoolResource.
// Source: Z:\Toshi\Source\TRenderD3D\TIndexPoolResource.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TMemory.h"
#include "TIndexPoolResource.h"
#include "TIndexBlockResource.h"

namespace Toshi {

TIndexPoolResource::TIndexPoolResource()
{
    m_usUnk3C = 0;
    m_pManagedBuffer = 0;
    m_unk44 = 0;
}

TIndexPoolResource::~TIndexPoolResource()
{
}

TIndexFactoryResource* TIndexPoolResource::GetFactory()
{
    return (TIndexFactoryResource*)m_pFactory;
}

unsigned short* TIndexPoolResource::GetManagedBuffer()
{
    if (!IsLocked())
        return m_pManagedBuffer;
    return 0;
}

TIndexBlockResource* TIndexPoolResource::GetIndexBlock()
{
    TResource* block = Parent();
    if (block->GetClass().IsExactly(TIndexBlockResource::m_sClass) == true)
        return (TIndexBlockResource*)block;
    return 0;
}

void TIndexPoolResource::Invalidate()
{
    if (IsValid() == true)
    {
        GetIndexBlock()->DetachPool(this);
        TResource::Invalidate();
    }
}

void TIndexPoolResource::OnDestroy()
{
    if ((GetFlags() & 1) != 0 && m_pManagedBuffer != 0)
    {
        tfree(m_pManagedBuffer);
        m_pManagedBuffer = 0;
    }
    TIndexPoolResourceInterface::OnDestroy();
}

bool TIndexPoolResource::Create(TIndexFactoryResourceInterface* factory, unsigned int maxIndices, unsigned int flags)
{
    if ((flags & 4) != 0)
        flags = (flags & ~4) | 2;
    if (TIndexPoolResourceInterface::Create(factory, maxIndices, flags) == false)
        return false;
    if ((GetFlags() & 1) != 0)
        m_pManagedBuffer = (unsigned short*)tmalloc(maxIndices * 2, 0, -1);
    return true;
}

TOSHI_DEFINE_CLASS(TIndexPoolResource, TIndexPoolResourceInterface)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TIndexPoolResource)

} // namespace Toshi
