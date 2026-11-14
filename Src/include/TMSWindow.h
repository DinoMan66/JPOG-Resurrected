// Toshi::TMSWindow (TRenderD3DInterface.dll, 0x14 bytes). The Win32 window the Direct3D renderer draws into.
#ifndef TMSWINDOW_H
#define TMSWINDOW_H
#include <windows.h>
#include "TRenderD3DAPI.h"
#include "TObject.h"

namespace Toshi {

class TRenderD3DInterface;

class TRENDERD3D_API TMSWindow : public TObject                         // 0x14
{
public:
    TOSHI_DECLARE_CLASS(TMSWindow)

    TMSWindow();
    virtual ~TMSWindow();

    bool IsWindowed();
    void Enable();
    void Disable();
    void Destroy();
    void SetFullscreen();
    void SetWindowed();
    void Position(int x, int y, int width, int height);
    TRenderD3DInterface* GetD3DInterface() const;
    HWND GetHWND() const;
    operator HWND() const;

private:
    HWND                 m_hWnd;                // +0x04
    TRenderD3DInterface* m_pRenderer;           // +0x08
    bool                 m_bEnabled;            // +0x0c
    bool                 m_bWindowed;           // +0x0d
    HINSTANCE            m_hInstance;           // +0x10 (read by Create and Destroy, UnregisterClass argument)
};

} // namespace Toshi
#endif
