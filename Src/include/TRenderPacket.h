// Toshi::TRenderPacket (TRenderD3DInterface.dll, 0x7c bytes). One mesh instance queued for a shader:
// the mesh, its material, the model-view matrix and the lighting the shader needs. Packets live in
// the array of a TOrderTable and are chained per material (m_pNext).
#ifndef TRENDERPACKET_H
#define TRENDERPACKET_H
#include "TRenderD3DAPI.h"
#include "TVector.h"

namespace Toshi {

class TMesh;
class TRegMaterial;
class TSkeletonInstance;

class TRENDERD3D_API TRenderPacket                                      // 0x7c
{
    friend class TRegMaterial;
public:
    TRenderPacket();
    ~TRenderPacket();

    void SetModelViewMatrix(const TMatrix44& matrix);
    void SetMesh(TMesh* mesh);
    void SetRegMat(TRegMaterial* regMaterial);
    TRenderPacket* SetNext(TRenderPacket* next);
    TSkeletonInstance* GetSkeletonInstance();
    void SetSkeletonInstance(TSkeletonInstance* skeleton);
    float GetTextureFade();
    float GetAlphaFade();
    const TVector3& GetLightDir();
    const TVector3& GetDiffuse();
    const TVector3& GetAmbient();
    void SetTextureFade(float fade);
    void SetAlphaFade(float fade);
    void SetLightDir(const TVector3& lightDir);
    void SetDiffuse(const TVector3& diffuse);
    void SetAmbient(const TVector3& ambient);
    TMatrix44& GetModelViewMatrix();
    TMesh* GetMesh();
    TRegMaterial* GetRegMat();
    TRenderPacket* GetNext();

private:
    TRenderPacket* m_pNext;                     // +0x00
    TRegMaterial*  m_pRegMat;                   // +0x04
    TMesh*         m_pMesh;                     // +0x08
    TMatrix44      m_oModelView;                // +0x0c
    TSkeletonInstance* m_pSkeletonInstance;     // +0x4c
    TVector3       m_oAmbient;                  // +0x50
    TVector3       m_oDiffuse;                  // +0x5c
    TVector3       m_oLightDir;                 // +0x68
    float          m_fAlphaFade;                // +0x74
    unsigned char  m_ucTextureFade;             // +0x78 (0-255)
};

} // namespace Toshi
#endif
