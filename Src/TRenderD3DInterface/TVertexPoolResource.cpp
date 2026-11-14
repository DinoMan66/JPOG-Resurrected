// Toshi::TVertexPoolResource.
// Source: Z:\Toshi\Source\TRenderD3D\TVertexPoolResource.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TMemory.h"
#include "TVertexPoolResource.h"
#include "TVertexBlockResource.h"
#include "TVertexFactoryResourceInterface.h"

namespace Toshi {

TVertexPoolResource::TVertexPoolResource()
{
    m_usUnk3C = 0;
    m_unk60 = 0;
    for (int stream = 0; stream < 8; stream++)
        m_apManagedStreams[stream] = 0;
}

TVertexPoolResource::~TVertexPoolResource()
{
}

TVertexFactoryResource* TVertexPoolResource::GetFactory()
{
    return (TVertexFactoryResource*)m_pFactory;
}

unsigned char* TVertexPoolResource::GetManagedStream(unsigned int stream)
{
    if (!IsLocked())
    {
        if (stream < m_pFactory->GetVertexFormat()->m_uiNumStreams)
            return m_apManagedStreams[stream];
    }
    return 0;
}

TVertexBlockResource* TVertexPoolResource::GetVertexBlock()
{
    TResource* block = Parent();
    if (block->GetClass().IsExactly(TVertexBlockResource::m_sClass) == true)
        return (TVertexBlockResource*)block;
    return 0;
}

void TVertexPoolResource::Invalidate()
{
    if (IsValid() == true)
    {
        GetVertexBlock()->DetachPool(this);
        TResource::Invalidate();
    }
}

void TVertexPoolResource::OnDestroy()
{
    if ((GetFlags() & 1) != 0)
    {
        for (unsigned int stream = 0; stream < m_pFactory->GetVertexFormat()->m_uiNumStreams; stream++)
        {
            if (m_apManagedStreams[stream] != 0)
            {
                tfree(m_apManagedStreams[stream]);
                m_apManagedStreams[stream] = 0;
            }
        }
    }
    TVertexPoolResourceInterface::OnDestroy();
}

bool TVertexPoolResource::Create(TVertexFactoryResourceInterface* factory, unsigned int maxVertices, unsigned int flags)
{
    if ((flags & 4) != 0)
        flags = (flags & ~4) | 2;
    if (TVertexPoolResourceInterface::Create(factory, maxVertices, flags) == false)
        return false;
    if ((GetFlags() & 1) != 0)
    {
        for (unsigned int stream = 0; stream < m_pFactory->GetVertexFormat()->m_uiNumStreams; stream++)
        {
            unsigned int vertexSize = m_pFactory->GetVertexFormat()->m_aStreamFormats[stream].m_uiVertexSize;
            m_apManagedStreams[stream] = (unsigned char*)tmalloc(vertexSize * maxVertices, 0, -1);
        }
    }
    return true;
}

TOSHI_DEFINE_CLASS(TVertexPoolResource, TVertexPoolResourceInterface)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TVertexPoolResource)

} // namespace Toshi
