// Toshi::TRenderD3DInterface - accessors.
// Source: Z:\Toshi\Source\TRenderD3D\TRenderD3DInterface.cpp (recorded in the binary).
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TRenderD3DInterface.h"
#include "TRenderCaptureD3D.h"
#include "TRenderContextD3D.h"
#include "TModelD3D.h"
#include "TTextureResource.h"
#include "TDebugText.h"
#include "TMath.h"

namespace Toshi {

void TRenderD3DInterface::SetTextureColorStage(unsigned int stage, unsigned int arg1, unsigned int op, unsigned int arg2)
{
    m_pD3DDevice->SetTextureStageState(stage, D3DTSS_COLOROP, op);
    m_pD3DDevice->SetTextureStageState(stage, D3DTSS_COLORARG1, arg1);
    m_pD3DDevice->SetTextureStageState(stage, D3DTSS_COLORARG2, arg2);
}

void TRenderD3DInterface::SetTextureAlphaStage(unsigned int stage, unsigned int arg1, unsigned int op, unsigned int arg2)
{
    m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ALPHAOP, op);
    m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ALPHAARG1, arg1);
    m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ALPHAARG2, arg2);
}

bool TRenderD3DInterface::IsTextureFormatSupported(TTEXTURERESOURCEFORMAT format)
{
    _D3DFORMAT d3dFormat;
    if (format == 1)
    {
        d3dFormat = D3DFMT_A8R8G8B8;
    }
    else if (format == 2)
    {
        d3dFormat = D3DFMT_X8R8G8B8;
    }
    else
    {
        if (format != 3)
        {
            if (format == 4)
                return true;
            return false;
        }
        d3dFormat = D3DFMT_A1R5G5B5;
    }
    return IsTextureFormatSupported(d3dFormat);
}

bool TRenderD3DInterface::Supports32BitTextures()
{
    if (IsTextureFormatSupported((TTEXTURERESOURCEFORMAT)1) == false)
        return false;
    if (IsTextureFormatSupported((TTEXTURERESOURCEFORMAT)2) == true)
        return true;
    return false;
}

float TRenderD3DInterface::GetContrast() const
{
    return m_fContrast;
}

float TRenderD3DInterface::GetBrightness() const
{
    return m_fBrightness;
}

float TRenderD3DInterface::GetGamma() const
{
    return m_fGamma;
}

float TRenderD3DInterface::GetSaturate() const
{
    return m_fSaturate;
}

void TRenderD3DInterface::ForceEnableColourCorrection(bool enable)
{
    m_bColourCorrection = enable;
}

bool TRenderD3DInterface::IsColourCorrection()
{
    return m_bColourCorrection;
}

void TRenderD3DInterface::EnableColourCorrection(bool enable)
{
    if (IsCapableColourCorrection() != true)
        enable = false;
    m_bColourCorrection = enable;
}

bool TRenderD3DInterface::SetPixelAspectRatio(float ratio)
{
    m_fPixelAspectRatio = ratio;
    return true;
}

float TRenderD3DInterface::GetPixelAspectRatio()
{
    return m_fPixelAspectRatio;
}

const TRenderInterface::DisplayParams* TRenderD3DInterface::GetCurrentDisplayParams() const
{
    return &m_oDisplayParams;
}

TRenderCapture* TRenderD3DInterface::CreateCapture()
{
    return new TRenderCaptureD3D;
}

TRenderContext* TRenderD3DInterface::CreateRenderContext()
{
    return new TRenderContextD3D(*this);
}

bool TRenderD3DInterface::AdjustDisplay(const DisplayParams* params)
{
    if (!IsCreated())
        return false;
    if (!IsDisplayCreated())
        return false;
    LostDevice();
    DestroyDisplay();
    if (!CreateDisplay(params))
        return false;
    ResetDevice();
    return true;
}

bool TRenderD3DInterface::DestroyDisplay()
{
    if (m_pInvalidTexture != 0)
    {
        m_pInvalidTexture->DestroyResource();
        m_pInvalidTexture = 0;
    }
    FlushDyingResources();
    if (m_pDebugText != 0)
        m_pDebugText->Destroy();
    if (!IsDisplayCreated())
        return true;
    if (m_pD3DDevice != 0)
    {
        SAFE_RELEASE(m_pD3DDevice);
        m_pD3DDevice = 0;
    }
    return TRenderInterface::DestroyDisplay();
}

void TRenderD3DInterface::FailedD3DMessageBox()
{
    char title[1024];
    char message[1024];
    GetPrivateProfileStringA("Setup", "IDS_D3DDEVICEERRORTITLE", "Initialization failure", title, 1024, ".\\Setup.ini");
    GetPrivateProfileStringA("Setup", "IDS_D3DDEVICEERROR",
                             "Failed to initialize Direct3D. Please ensure DirectX8.1b is installed AND DirectX8.1b drivers for your video card",
                             message, 1024, ".\\Setup.ini");
    MessageBoxA(NULL, message, title, MB_OK);
}

void TRenderD3DInterface::FailedDisplayMessageBox()
{
    char title[1024];
    char message[1024];
    GetPrivateProfileStringA("Setup", "IDS_D3DDISPLAYERRORTITLE", "Initialization failure", title, 1024, ".\\Setup.ini");
    GetPrivateProfileStringA("Setup", "IDS_D3DDISPLAYERROR",
                             "Failed to create the display. Please run the Jurassic Park setup program and reconfigure",
                             message, 1024, ".\\Setup.ini");
    MessageBoxA(NULL, message, title, MB_OK);
}

TModel* TRenderD3DInterface::CreateModel(const char* name, bool load)
{
    TModelD3D* model = new TModelD3D;
    if (model != 0)
    {
        if (!model->Create(name, load))
        {
            model->Delete();
            return 0;
        }
    }
    return model;
}

void TRenderD3DInterface::DestroyCapture(TRenderCapture* capture)
{
    capture->Destroy();
    delete capture;
}

void TRenderD3DInterface::SetContrast(float contrast)
{
    TMath::Clip(contrast, 0.0f, 1.0f);
    m_fContrast = contrast;
    m_bColourDirty = true;
}

void TRenderD3DInterface::SetBrightness(float brightness)
{
    TMath::Clip(brightness, 0.0f, 1.0f);
    m_fBrightness = brightness;
    m_bColourDirty = true;
}

void TRenderD3DInterface::SetGamma(float gamma)
{
    TMath::Clip(gamma, 0.0f, 1.0f);
    m_fGamma = gamma;
    m_bColourDirty = true;
}

void TRenderD3DInterface::SetSaturate(float saturate)
{
    TMath::Clip(saturate, 0.0f, 1.0f);
    m_fSaturate = saturate;
    m_bColourDirty = true;
}

float TRenderD3DInterface::NormalizeValue(float value) const
{
    return (value - 0.5f) * 2.0f;
}

float TRenderD3DInterface::DeNormalizeValue(float value) const
{
    return 0.5 + value * 0.5;
}

float TRenderD3DInterface::TransformBrightness(float brightness, float value)
{
    float result = brightness - 0.5f + value;
    TMath::Clip(result, 0.0f, 1.0f);
    return result;
}

float TRenderD3DInterface::TransformContrast(float contrast, float value)
{
    if (contrast < 0.5)
        return (value - 0.5f) * 2.0f * contrast + 0.5f;
    if (contrast > 0.5f)
        return TMath::Gain(contrast, value);
    return value;
}

int TRenderD3DInterface::GetNumAdapters()
{
    return GetAdapterList()->Count();
}

void TRenderD3DInterface::CreateAcceleratorTable()
{
    DestroyAcceleratorTable();
    ACCEL accelerators[2];
    accelerators[0].fVirt = FVIRTKEY;
    accelerators[0].key = VK_ESCAPE;
    accelerators[0].cmd = 0;
    accelerators[1].fVirt = FALT;
    accelerators[1].key = VK_RETURN;
    accelerators[1].cmd = 1;
    m_hAccelTable = ::CreateAcceleratorTable(accelerators, 2);
}

void TRenderD3DInterface::DestroyAcceleratorTable()
{
    if (m_hAccelTable != 0)
    {
        ::DestroyAcceleratorTable(m_hAccelTable);
        m_hAccelTable = 0;
    }
}

TRenderD3DInterface::~TRenderD3DInterface()
{
    Destroy();
}

void TRenderD3DInterface::DestroyAdapterDatabase()
{
    TNodeList<TRenderAdapter>* adapters = GetAdapterList();
    for (TRenderAdapter* adapter = adapters->Head(); adapter != adapters->End(); adapter = adapters->Head())
    {
        adapters->Remove(adapter);
        delete adapter;
    }
}

_D3DGAMMARAMP* TRenderD3DInterface::GetCurrentColourRamp()
{
    ComputeTables();
    return &m_oGammaRamp;
}

void TRenderD3DInterface::UpdateColourSettings()
{
    if (IsColourCorrection() == true)
        m_pD3DDevice->SetGammaRamp(0, GetCurrentColourRamp());
}

void TRenderD3DInterface::SetTextureAddressMode(unsigned int stage, unsigned int mode)
{
    if (mode == 0)
    {
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
    }
    else if (mode == 2)
    {
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
    }
    else if (mode == 1)
    {
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSU, D3DTADDRESS_MIRROR);
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSV, D3DTADDRESS_MIRROR);
    }
    else if (mode == 3)
    {
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSU, D3DTADDRESS_BORDER);
        m_pD3DDevice->SetTextureStageState(stage, D3DTSS_ADDRESSV, D3DTADDRESS_BORDER);
    }
}

void TRenderD3DInterface::SetDefaultRenderStates()
{
    m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, 0);
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
    m_pD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
}

void TRenderD3DInterface::UnloadShaders()
{
}

TOSHI_DEFINE_CLASS(TRenderD3DInterface, TRenderInterface)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TRenderD3DInterface)

} // namespace Toshi
