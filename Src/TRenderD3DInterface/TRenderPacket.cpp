// Z:\Toshi\Source\TRenderD3D\TRenderPacket.cpp  (reconstruction; source path not confirmed by a string)
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TRenderPacket.h"

namespace Toshi {

TRenderPacket::TRenderPacket()                                      // 0x6110
{
    m_pNext = 0;
    m_pRegMat = 0;
    m_pSkeletonInstance = 0;
    m_oAmbient.Set(0.24f, 0.24f, 0.24f);
    m_oDiffuse.Set(1.0f, 1.0f, 0.65f);
    m_oLightDir.Set(-0.47f, 0.74f, 0.47f);
    m_fAlphaFade = 1.0f;
    m_ucTextureFade = 0xff;
}

void TRenderPacket::SetModelViewMatrix(const TMatrix44& matrix)     // 0x6170
{
    m_oModelView = matrix;
}

void TRenderPacket::SetMesh(TMesh* mesh)                            // 0x6240
{
    m_pMesh = mesh;
}

void TRenderPacket::SetRegMat(TRegMaterial* regMaterial)            // 0x6250
{
    m_pRegMat = regMaterial;
}

TRenderPacket* TRenderPacket::SetNext(TRenderPacket* next)          // 0x6260
{
    TRenderPacket* previous = m_pNext;
    m_pNext = next;
    return previous;
}

TRenderPacket::~TRenderPacket()                                     // 0x6270
{
}

TSkeletonInstance* TRenderPacket::GetSkeletonInstance()             // 0x6310
{
    return m_pSkeletonInstance;
}

void TRenderPacket::SetSkeletonInstance(TSkeletonInstance* skeleton)    // 0x6320
{
    m_pSkeletonInstance = skeleton;
}

float TRenderPacket::GetTextureFade()                               // 0x6330
{
    return m_ucTextureFade * (1.0f / 255.0f);
}

float TRenderPacket::GetAlphaFade()                                 // 0x6350
{
    return m_fAlphaFade;
}

const TVector3& TRenderPacket::GetLightDir()                        // 0x6360
{
    return m_oLightDir;
}

const TVector3& TRenderPacket::GetDiffuse()                         // 0x6370
{
    return m_oDiffuse;
}

const TVector3& TRenderPacket::GetAmbient()                         // 0x6380
{
    return m_oAmbient;
}

void TRenderPacket::SetTextureFade(float fade)                      // 0x6390
{
    m_ucTextureFade = (unsigned char)(fade * 255.0f);
}

void TRenderPacket::SetAlphaFade(float fade)                        // 0x63d0
{
    m_fAlphaFade = fade;
}

void TRenderPacket::SetLightDir(const TVector3& lightDir)           // 0x63e0
{
    m_oLightDir = lightDir;
}

void TRenderPacket::SetDiffuse(const TVector3& diffuse)             // 0x6400
{
    m_oDiffuse = diffuse;
}

void TRenderPacket::SetAmbient(const TVector3& ambient)             // 0x6420
{
    m_oAmbient = ambient;
}

TMatrix44& TRenderPacket::GetModelViewMatrix()                      // 0x6440
{
    return m_oModelView;
}

TMesh* TRenderPacket::GetMesh()                                     // 0x6450
{
    return m_pMesh;
}

TRegMaterial* TRenderPacket::GetRegMat()                            // 0x6460
{
    return m_pRegMat;
}

TRenderPacket* TRenderPacket::GetNext()                             // 0x6470
{
    return m_pNext;
}

} // namespace Toshi
