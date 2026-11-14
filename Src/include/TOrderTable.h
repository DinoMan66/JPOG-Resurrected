// Toshi::TOrderTable (TRenderD3DInterface.dll, 0x40 bytes). Per-shader queue: a pool of TRegMaterial
// and a pool of TRenderPacket, handed out while a frame is built and rendered by Render().
#ifndef TORDERTABLE_H
#define TORDERTABLE_H
#include "TRenderD3DAPI.h"
#include "TNodeList.h"
#include "TRegMaterial.h"

namespace Toshi {

class TShader;
class TMaterial;
class TRenderPacket;

class TRENDERD3D_API TOrderTable                                        // 0x40
{
public:
    TOrderTable(TShader* shader, unsigned int numMaterials, unsigned int numRenderPackets);
    ~TOrderTable();

    TRegMaterial* RegisterMaterial(TMaterial* material);
    void DeregisterMaterial(TRegMaterial* regMaterial);
    void DeregisterAllMaterials();
    void UseMaterial(TRegMaterial* regMaterial);
    void Render();
    TRenderPacket* AllocRenderPacket();
    unsigned int GetNumRendPackets();
    unsigned int GetMaxRendPackets();
    unsigned int GetNumMaterials();
    unsigned int GetMaxMaterials();
    TShader* GetShader();

private:
    TShader*       m_pShader;                   // +0x00
    unsigned int   m_uiMaxMaterials;            // +0x04
    unsigned int   m_uiMaxRenderPackets;        // +0x08
    unsigned int   m_uiNumRenderPackets;        // +0x0c (packets handed out this frame)
    TNodeList<TRegMaterial> m_oRegisteredMaterials;     // +0x10 (root +0x10, count +0x1c)
    TNodeList<TRegMaterial> m_oFreeMaterials;           // +0x20 (root +0x20, count +0x2c)
    TRegMaterial*  m_pMaterialPool;             // +0x30
    TRenderPacket* m_pRenderPacketPool;         // +0x34
    TRegMaterial*  m_pUsedMaterials;            // +0x38 (unsorted shaders)
    TRegMaterial*  m_pUsedMaterialsSorted;      // +0x3c (sorted shaders)
};

} // namespace Toshi
#endif
