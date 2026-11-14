// Z:\Toshi\Source\TRenderD3D\TRegMaterial.cpp  (reconstruction; source path not confirmed by a string)
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TShader.h"
#include "TRegMaterial.h"
#include "TOrderTable.h"
#include "TRenderPacket.h"

namespace Toshi {

TRenderPacket* TRegMaterial::AddRenderPacket(TMesh* mesh)           // 0x6060
{
    TRenderPacket* previous = m_pRenderPackets;
    m_pRenderPackets = m_pOrderTable->AllocRenderPacket();
    m_pRenderPackets->SetNext(previous);
    m_pOrderTable->UseMaterial(this);
    m_pRenderPackets->SetMesh(mesh);
    return m_pRenderPackets;
}

void TRegMaterial::Render()                                         // 0x60b0
{
    m_pMaterial->PreRender();
    for (TRenderPacket* packet = m_pRenderPackets; packet != 0; packet = packet->m_pNext)
        packet->m_pMesh->GetShader()->Render(packet);
    m_pRenderPackets = 0;
    m_uiFlags &= ~2;
    m_pMaterial->PostRender();
}

void TRegMaterial::SetNexUsedMaterial(TRegMaterial* next)           // 0x6280
{
    m_pNexUsedMaterial = next;
}

void TRegMaterial::SetMaterial(TMaterial* material)                 // 0x6290
{
    m_pMaterial = material;
}

void TRegMaterial::SetOrderTable(TOrderTable* orderTable)           // 0x62a0
{
    m_pOrderTable = orderTable;
}

void TRegMaterial::SetFlags(unsigned int flags)                     // 0x62b0
{
    m_uiFlags = flags;
}

TRegMaterial::~TRegMaterial()                                       // 0x62c0
{
}

TRegMaterial::TRegMaterial()                                        // 0x62d0
{
    m_uiFlags = 0;
    m_pOrderTable = 0;
    m_pMaterial = 0;
    m_pRenderPackets = 0;
    m_pNexUsedMaterial = 0;
}

TRegMaterial* TRegMaterial::GetNexUsedMaterial()                    // 0x6480
{
    return m_pNexUsedMaterial;
}

TRenderPacket* TRegMaterial::GetRenderPackets()                     // 0x6490
{
    return m_pRenderPackets;
}

TMaterial* TRegMaterial::GetMaterial()                              // 0x64a0
{
    return m_pMaterial;
}

TOrderTable* TRegMaterial::GetOrderTable()                          // 0x64b0
{
    return m_pOrderTable;
}

unsigned int TRegMaterial::GetFlags()                               // 0x64c0
{
    return m_uiFlags;
}

} // namespace Toshi
