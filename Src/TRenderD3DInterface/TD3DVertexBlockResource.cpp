// Toshi::TVertexBlockResource.
// Source: Z:\Toshi\Source\TRenderD3D\TD3DVertexBlockResource.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TVertexPoolResource.h"
#include "TVertexFactoryResource.h"
#include "TMemory.h"
#include "TRenderD3DInterface.h"
#include "TRenderInterface.h"
#include "TVertexBlockResource.h"

namespace Toshi {

unsigned int TVertexBlockResource::GetFlags()
{
    return m_uiFlags;
}

unsigned int TVertexBlockResource::GetVerticesUsed() const
{
    return m_uiVerticesUsed;
}

unsigned short TVertexBlockResource::GetMaxVertices() const
{
    return m_usMaxVertices;
}

TVertexFactoryResource* TVertexBlockResource::GetFactory()
{
    return m_pFactory;
}

bool TVertexBlockResource::IsLocked()
{
    if (m_uiLockCount > 0)
        return true;
    return false;
}

void TVertexBlockResource::ChildVertexUsedChanged(int delta)
{
    m_uiVerticesUsed += delta;
}

bool TVertexBlockResource::OnLostDevice()
{
    if (!(m_uiFlags & 1))
        Invalidate();
    return true;
}

bool TVertexBlockResource::OnResetDevice()
{
    if (!(m_uiFlags & 1))
        Validate();
    return true;
}

void TVertexBlockResource::Invalidate()
{
    if (IsValid() == true)
    {
        DestroyHAL();
        TResource::Invalidate();
    }
}

bool TVertexBlockResource::AttachPool(TVertexPoolResource* pool)
{
    m_uiVerticesUsed += pool->GetNumVertices();
    pool->SetParent(this);
    if ((GetFlags() & 1) != 0)
        Invalidate();
    return true;
}

bool TVertexBlockResource::DetachPool(TVertexPoolResource* pool)
{
    pool->SetParent(Parent());
    m_uiVerticesUsed -= pool->GetNumVertices();
    if (m_uiVerticesUsed == 0 && Child() == 0)
    {
        GetRenderer()->DestroyResource(this);
        return true;
    }
    return false;
}

int TVertexBlockResource::s_iTotalVertexBufferBytesAllocated;
int TVertexBlockResource::s_iHALMemoryUsage;
int TVertexBlockResource::s_iCurrentNumHALCreated;
int TVertexBlockResource::s_iTotalNumHALCreated;
int TVertexBlockResource::s_iTotalNumHALDestroyed;
int TVertexBlockResource::s_iCurrentVertexBufferBytesAllocated;
int TVertexBlockResource::s_iWastedVertexBufferBytesAllocated;

void TVertexBlockResource::Unlock()
{
    if (m_uiLockCount > 0)
    {
        for (unsigned int stream = 0; stream < m_pFactory->GetVertexFormat()->m_uiNumStreams; stream++)
            TRenderD3DInterface::TD3DAssert(m_apD3DBuffers[stream]->Unlock(), "Couldn't unlock stream vertex buffer!");
        m_uiLockCount--;
    }
}

void TVertexBlockResource::DestroyHAL()
{
    TMemory::HALMemInfo before;
    TMemory::GetHALMemInfo(before);
    for (unsigned int stream = 0; stream < m_uiNumStreams; stream++)
    {
        if (m_apD3DBuffers[stream] != 0)
        {
            SAFE_RELEASE(m_apD3DBuffers[stream]);
            m_apD3DBuffers[stream] = 0;
            s_iCurrentNumHALCreated--;
            s_iTotalNumHALDestroyed++;
            s_iCurrentVertexBufferBytesAllocated -= m_pFactory->GetVertexFormat()->m_aStreamFormats[stream].m_uiVertexSize * m_usMaxVertices;
        }
    }
    m_uiNumStreams = 0;
    TMemory::HALMemInfo after;
    TMemory::GetHALMemInfo(after);
    s_iHALMemoryUsage -= after.m_iUnk28;
    if (s_iTotalVertexBufferBytesAllocated < s_iHALMemoryUsage)
        s_iWastedVertexBufferBytesAllocated = s_iHALMemoryUsage - s_iTotalVertexBufferBytesAllocated;
}

bool TVertexBlockResource::CreateHAL()
{
    DestroyHAL();
    TVertexFactoryFormat* format = m_pFactory->GetVertexFormat();
    TRenderD3DInterface* renderer = (TRenderD3DInterface*)GetRenderer();
    m_uiNumStreams = format->m_uiNumStreams;
    for (unsigned int stream = 0; stream < m_uiNumStreams; stream++)
    {
        unsigned int bufferSize = format->m_aStreamFormats[stream].m_uiVertexSize * m_usMaxVertices;
        unsigned int usage = D3DUSAGE_WRITEONLY;
        if ((m_uiFlags & 1) == 0)
        {
            usage = D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC;
            m_unk3C = 0;
        }
        if (renderer->GetCurrentDevice()->SupportsHardwareTransfomations() == false)
            usage |= D3DUSAGE_SOFTWAREPROCESSING;
        int pool = ((m_uiFlags & 1) != 0) ? D3DPOOL_MANAGED : D3DPOOL_DEFAULT;
        long result = renderer->GetD3DDevice()->CreateVertexBuffer(bufferSize, usage, 0, pool, (void**)&m_apD3DBuffers[stream]);
        TRenderD3DInterface::TD3DAssert(result, "Unable to create a new vertex buffer!");
        if (result < 0)
            return false;
        TMemory::HALMemInfo info;
        TMemory::GetHALMemInfo(info);
        s_iTotalVertexBufferBytesAllocated += bufferSize;
        s_iHALMemoryUsage += info.m_iUnk28;
        s_iCurrentNumHALCreated++;
        s_iTotalNumHALCreated++;
        s_iCurrentVertexBufferBytesAllocated += bufferSize;
        if (s_iTotalVertexBufferBytesAllocated < s_iHALMemoryUsage)
            s_iWastedVertexBufferBytesAllocated = s_iHALMemoryUsage - s_iTotalVertexBufferBytesAllocated;
    }
    return true;
}

bool TVertexBlockResource::Create(TVertexFactoryResource* factory, unsigned short maxVertices, unsigned int flags)
{
    m_pFactory = factory;
    m_usMaxVertices = maxVertices;
    m_uiFlags = flags;
    return TResource::Create();
}

TVertexBlockResource::~TVertexBlockResource()
{
}

TOSHI_DEFINE_CLASS(TVertexBlockResource, TResource)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TVertexBlockResource)

} // namespace Toshi
