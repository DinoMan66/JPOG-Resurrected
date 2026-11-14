// Toshi::TRenderD3DInterface (TRenderD3DInterface.dll, TRenderD3DInterface.cpp) - the Direct3D 8
// renderer. Size 0x820; the base class TRenderInterface ends at 0x174. Members that no method
// written so far touches are offset-named placeholders.
#ifndef TRENDERD3DINTERFACE_H
#define TRENDERD3DINTERFACE_H
#include "TRenderInterface.h"
#include "TRenderD3DAPI.h"
#include "TMSWindow.h"

#include "d3d8min.h"

struct IDirect3D8;
struct HACCEL__;

namespace Toshi {

class TRENDERD3D_API TRenderD3DInterface : public TRenderInterface
{
    TOSHI_DECLARE_CLASS(TRenderD3DInterface)
public:
    TRenderD3DInterface();
    virtual ~TRenderD3DInterface();

    virtual bool CreateDisplay(const DisplayParams* params);                    // slot 3
    virtual bool DestroyDisplay();                                              // slot 4
    virtual bool Update(float deltaTime);                                       // slot 5
    virtual bool BeginScene();                                                  // slot 6
    virtual bool EndScene();                                                    // slot 7
    virtual TRenderAdapter::Mode::Device* GetCurrentDevice() const;             // slot 8 (really returns TD3DAdapter::Mode::Device*)
    virtual const DisplayParams* GetCurrentDisplayParams() const;               // slot 9
    virtual bool Create(TKernelInterface* kernel);                              // slot 10
    virtual bool Destroy();                                                     // slot 11
    virtual void RenderIndexPrimitive(PRIMITIVETYPE type, unsigned int a, unsigned int b,
                                      const unsigned short* indices, const void* vertices, unsigned short stride);
    virtual float GetPixelAspectRatio();                                        // slot 17
    virtual bool SetPixelAspectRatio(float ratio);                              // slot 18
    virtual bool IsTextureFormatSupported(TTEXTURERESOURCEFORMAT format);       // slot 19
    virtual bool Supports32BitTextures();                                       // slot 20
    virtual TRenderContext* CreateRenderContext();                              // slot 21
    virtual TRenderCapture* CreateCapture();                                    // slot 22
    virtual void DestroyCapture(TRenderCapture* capture);                       // slot 23
    virtual void ConnectDefaultViewportHandlers(TViewport& viewport);           // slot 26
    virtual TModel* CreateModel(const char* name, bool load);                   // slot 27
    virtual void FailedD3DMessageBox();                                         // slot 28
    virtual void FailedDisplayMessageBox();                                     // slot 29
    virtual bool AdjustDisplay(const DisplayParams* params);                    // slot 32
    virtual void SetContrast(float contrast);                                   // slot 33
    virtual void SetBrightness(float brightness);                               // slot 34
    virtual void SetGamma(float gamma);                                         // slot 35
    virtual void SetSaturate(float saturate);                                   // slot 36
    virtual float GetContrast() const;                                          // slot 37
    virtual float GetBrightness() const;                                        // slot 38
    virtual float GetGamma() const;                                             // slot 39
    virtual float GetSaturate() const;                                          // slot 40
    virtual void UpdateColourSettings();                                        // slot 41
    virtual bool IsCapableColourCorrection();                                   // slot 42
    virtual void EnableColourCorrection(bool enable);                           // slot 43
    virtual void ForceEnableColourCorrection(bool enable);                      // slot 44
    virtual bool IsColourCorrection();                                          // slot 45

    bool IsTextureFormatSupported(_D3DFORMAT format);

    void SetTextureAddressMode(unsigned int stage, unsigned int mode);
    void LostDevice();
    void ResetDevice();

    void SetTextureColorStage(unsigned int stage, unsigned int arg1, unsigned int op, unsigned int arg2);
    void SetTextureAlphaStage(unsigned int stage, unsigned int arg1, unsigned int op, unsigned int arg2);

    static void __stdcall TD3DAssert(long result, const char* message);

    IDirect3D8* GetD3DInterface() { return m_pD3D; }
    IDirect3DDevice8* GetD3DDevice() { return m_pD3DDevice; }
    HACCEL__* GetAcceleratorTable() const { return m_hAccelTable; }
    TMSWindow* GetMSWindow() { return &m_oWindow; }
    bool IsDeviceLost() { return m_bDeviceLost; }
    void Exit() { m_bExit = true; }

protected:
    void UnloadShaders();
    void SetDefaultRenderStates();

private:
    float NormalizeValue(float value) const;
    float DeNormalizeValue(float value) const;
    float TransformBrightness(float brightness, float value);
    float TransformContrast(float contrast, float value);
    int GetNumAdapters();
    void DestroyAdapterDatabase();
    void DestroyAcceleratorTable();
    void CreateAcceleratorTable();
    _D3DGAMMARAMP* GetCurrentColourRamp();
    void ComputeTables();

    /* 0x174 */ IDirect3D8*       m_pD3D;
    /* 0x178 */ IDirect3DDevice8* m_pD3DDevice;
    /* 0x17C */ unsigned char     m_unk17C[0x54];
    /* 0x1D0 */ float             m_fPixelAspectRatio;
    /* 0x1D4 */ HACCEL__*         m_hAccelTable;
    /* 0x1D8 */ TRenderAdapter::Mode::Device* m_pCurrentDevice;
    /* 0x1DC */ DisplayParams     m_oDisplayParams;
    /* 0x1F0 */ TMSWindow         m_oWindow;
    /* 0x204 */ bool              m_bExit;
    /* 0x208 */ float             m_fContrast;
    /* 0x20C */ float             m_fBrightness;
    /* 0x210 */ float             m_fGamma;
    /* 0x214 */ float             m_fSaturate;
    /* 0x218 */ bool              m_bColourDirty;
    /* 0x219 */ bool              m_unk219;
    /* 0x21A */ bool              m_unk21A;
    /* 0x21B */ bool              m_bColourCorrection;
    /* 0x21C */ _D3DGAMMARAMP     m_oGammaRamp;
    /* 0x81C */ bool              m_bDeviceLost;
};

} // namespace Toshi
#endif
