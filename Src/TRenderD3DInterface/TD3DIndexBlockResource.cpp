// Toshi::TIndexBlockResource.
// Source: Z:\Toshi\Source\TRenderD3D\TD3DIndexBlockResource.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TIndexPoolResource.h"
#include "TMemory.h"
#include "TRenderInterface.h"
#include "TIndexBlockResource.h"
#include "TRenderD3DInterface.h"

namespace Toshi {

unsigned int TIndexBlockResource::GetFlags()
{
    return m_uiFlags;
}

unsigned int TIndexBlockResource::GetIndicesUsed() const
{
    return m_uiIndicesUsed;
}

unsigned short TIndexBlockResource::GetMaxIndices() const
{
    return m_usMaxIndices;
}

TIndexFactoryResource* TIndexBlockResource::GetFactory()
{
    return m_pFactory;
}

bool TIndexBlockResource::IsLocked()
{
    if (m_uiLockCount > 0)
        return true;
    return false;
}

void TIndexBlockResource::ChildIndexUsedChanged(int delta)
{
    m_uiIndicesUsed += delta;
}

bool TIndexBlockResource::OnLostDevice()
{
    if (!(m_uiFlags & 1))
        Invalidate();
    return true;
}

bool TIndexBlockResource::OnResetDevice()
{
    if (!(m_uiFlags & 1))
        Validate();
    return true;
}

void TIndexBlockResource::Invalidate()
{
    if (IsValid() == true)
    {
        DestroyHAL();
        TResource::Invalidate();
    }
}

TIndexBlockResource::TIndexBlockResource()
    : m_pFactory(0), m_uiFlags(0), m_usMaxIndices(0), m_unk3C(0), m_uiIndicesUsed(0), m_uiLockCount(0), m_unk48(0),
      m_usUnk4C(0), m_pD3DIndexBuffer(0)
{
}

bool TIndexBlockResource::AttachPool(TIndexPoolResource* pool)
{
    m_uiIndicesUsed += pool->GetNumIndices();
    pool->SetParent(this);
    if ((GetFlags() & 1) != 0)
        Invalidate();
    return true;
}

bool TIndexBlockResource::DetachPool(TIndexPoolResource* pool)
{
    pool->SetParent(Parent());
    m_uiIndicesUsed -= pool->GetNumIndices();
    if (m_uiIndicesUsed == 0 && Child() == 0)
    {
        GetRenderer()->DestroyResource(this);
        return true;
    }
    return false;
}

bool TIndexBlockResource::CanFit(TIndexPoolResource* pool)
{
    if ((m_uiFlags & 1) == 0)
    {
        if ((m_uiFlags & 4) != 0)
        {
            if ((pool->GetFlags() & 4) != 0)
                return true;
        }
    }
    else
    {
        if ((pool->GetFlags() & 1) != 0)
            return m_uiIndicesUsed + pool->GetNumIndices() < m_usMaxIndices;
    }
    return false;
}

int TIndexBlockResource::s_iHALMemoryUsage;

void TIndexBlockResource::DestroyHAL()
{
    TMemory::HALMemInfo before;
    TMemory::GetHALMemInfo(before);
    if (m_pD3DIndexBuffer != 0)
    {
        SAFE_RELEASE(m_pD3DIndexBuffer);
        m_pD3DIndexBuffer = 0;
    }
    TMemory::HALMemInfo after;
    TMemory::GetHALMemInfo(after);
    s_iHALMemoryUsage -= after.m_iUnk28;
}

bool TIndexBlockResource::CreateHAL()
{
    DestroyHAL();
    TMemory::HALMemInfo before;
    TMemory::GetHALMemInfo(before);
    TRenderD3DInterface* renderer = (TRenderD3DInterface*)GetRenderer();
    unsigned int length = m_usMaxIndices * 2;
    unsigned int usage = D3DUSAGE_WRITEONLY;
    if ((m_uiFlags & 1) == 0)
    {
        usage = D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC;
        m_unk3C = 0;
    }
    if (renderer->GetCurrentDevice()->SupportsHardwareTransfomations() == false)
        usage |= D3DUSAGE_SOFTWAREPROCESSING;
    int pool = ((m_uiFlags & 1) != 0) ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT;
    long result = renderer->GetD3DDevice()->CreateIndexBuffer(length, usage, D3DFMT_INDEX16, pool, (void**)&m_pD3DIndexBuffer);
    TRenderD3DInterface::TD3DAssert(result, "Unable to create a new index buffer!");
    if (result < 0)
        return false;
    TMemory::HALMemInfo after;
    TMemory::GetHALMemInfo(after);
    s_iHALMemoryUsage += after.m_iUnk28;
    return true;
}

bool TIndexBlockResource::Create(TIndexFactoryResource* factory, unsigned short maxIndices, unsigned int flags)
{
    m_pFactory = factory;
    m_usMaxIndices = maxIndices;
    m_uiFlags = flags;
    return TResource::Create();
}

void TIndexBlockResource::Unlock()
{
    if (m_uiLockCount > 0)
    {
        TRenderD3DInterface::TD3DAssert(m_pD3DIndexBuffer->Unlock(), "Couldn't unlock stream index buffer!");
        m_uiLockCount--;
    }
}

TIndexBlockResource::~TIndexBlockResource()
{
}

TOSHI_DEFINE_CLASS(TIndexBlockResource, TResource)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TIndexBlockResource)

} // namespace Toshi
