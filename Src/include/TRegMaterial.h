// Toshi::TRegMaterial (TRenderD3DInterface.dll, 0x20 bytes). A material registered with a TOrderTable:
// it sits in the table's registered/free list (TNode base: owner list, next, prev) and keeps the
// chain of render packets queued for it until the table renders them.
#ifndef TREGMATERIAL_H
#define TREGMATERIAL_H
#include "TRenderD3DAPI.h"
#include "TNodeList.h"

namespace Toshi {

class TMaterial;
class TOrderTable;
class TRenderPacket;
class TMesh;

class TRENDERD3D_API TRegMaterial : public TNodeList<TRegMaterial>::TNode   // 0x20
{
public:
    TRegMaterial();
    ~TRegMaterial();

    TRenderPacket* AddRenderPacket(TMesh* mesh);
    void Render();
    void SetNexUsedMaterial(TRegMaterial* next);
    void SetMaterial(TMaterial* material);
    void SetOrderTable(TOrderTable* orderTable);
    void SetFlags(unsigned int flags);
    TRegMaterial* GetNexUsedMaterial();
    TRenderPacket* GetRenderPackets();
    TMaterial* GetMaterial();
    TOrderTable* GetOrderTable();
    unsigned int GetFlags();

private:
    friend class TOrderTable;

    unsigned int   m_uiFlags;                   // +0x0c (bit 0 registered, bit 1 queued for rendering)
    TOrderTable*   m_pOrderTable;               // +0x10
    TMaterial*     m_pMaterial;                 // +0x14
    TRenderPacket* m_pRenderPackets;            // +0x18 (newest packet first)
    TRegMaterial*  m_pNexUsedMaterial;          // +0x1c (chain of materials used this frame)
};

} // namespace Toshi
#endif
