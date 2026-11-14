// Z:\Toshi\Source\TRenderD3D\TOrderTable.cpp  (reconstruction; source path not confirmed by a string)
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TShader.h"
#include "TOrderTable.h"
#include "TRenderPacket.h"

namespace Toshi {

void TOrderTable::DeregisterAllMaterials()                          // 0x5f60
{
    for (TRegMaterial* material = m_oRegisteredMaterials.Head(); material != m_oRegisteredMaterials.End(); material = m_oRegisteredMaterials.Head())
        DeregisterMaterial(material);
}

void TOrderTable::UseMaterial(TRegMaterial* regMaterial)            // 0x5f90
{
    if ((regMaterial->m_uiFlags & 2) == 0)
    {
        regMaterial->SetFlags(regMaterial->m_uiFlags | 2);
        if ((regMaterial->m_pMaterial->GetFlags() & 2) == 0)
        {
            regMaterial->SetNexUsedMaterial(m_pUsedMaterials);
            m_pUsedMaterials = regMaterial;
        }
        else
        {
            regMaterial->SetNexUsedMaterial(m_pUsedMaterialsSorted);
            m_pUsedMaterialsSorted = regMaterial;
        }
    }
}

TRenderPacket* TOrderTable::AllocRenderPacket()                     // 0x62f0
{
    TRenderPacket* packet = &m_pRenderPacketPool[m_uiNumRenderPackets++];
    if (m_uiNumRenderPackets == m_uiMaxRenderPackets)
        return 0;
    return packet;
}

unsigned int TOrderTable::GetNumRendPackets()                       // 0x64d0
{
    return m_uiNumRenderPackets;
}

unsigned int TOrderTable::GetMaxRendPackets()                       // 0x64e0
{
    return m_uiMaxRenderPackets;
}

unsigned int TOrderTable::GetNumMaterials()                         // 0x64f0
{
    return m_oRegisteredMaterials.Count();
}

unsigned int TOrderTable::GetMaxMaterials()                         // 0x6500
{
    return m_uiMaxMaterials;
}

TShader* TOrderTable::GetShader()                                   // 0x6510
{
    return m_pShader;
}

} // namespace Toshi
