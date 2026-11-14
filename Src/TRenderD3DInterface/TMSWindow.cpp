// Z:\Toshi\Source\TRenderD3D\TMSWindow.cpp  (reconstruction; source path not confirmed by a string)
#define TRENDERD3DINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TMSWindow.h"
#include "TRenderD3DInterface.h"
#include "TCString.h"

namespace Toshi {

bool TMSWindow::IsWindowed()                                        // 0x4c10
{
    return m_bWindowed;
}

void TMSWindow::Destroy()                                           // 0x5990
{
    if (GetHWND() != 0)
    {
        Disable();
        DestroyWindow(GetHWND());
        m_hWnd = 0;
    }
    if (m_pRenderer != 0)
    {
        TCString className(TRenderD3DInterface::m_sClass.GetName());
        UnregisterClassA(className, m_hInstance);
        m_pRenderer = 0;
    }
}

void TMSWindow::Enable()                                            // 0x5a10
{
    EnableWindow(m_hWnd, TRUE);
    ShowWindow(m_hWnd, SW_SHOW);
    m_bEnabled = true;
}

void TMSWindow::Disable()                                           // 0x5a40
{
    EnableWindow(m_hWnd, FALSE);
    ShowWindow(m_hWnd, SW_HIDE);
    m_bEnabled = false;
}

TMSWindow::operator HWND() const                                    // 0x5ad0
{
    return m_hWnd;
}

void TMSWindow::SetFullscreen()                                     // 0x5ae0
{
    m_bWindowed = false;
}

void TMSWindow::SetWindowed()                                       // 0x5af0
{
    m_bWindowed = true;
}

void TMSWindow::Position(int x, int y, int width, int height)       // 0x5b00
{
    SetWindowPos(m_hWnd, NULL, x, y, width, height, 0);
}

TRenderD3DInterface* TMSWindow::GetD3DInterface() const             // 0x5b30
{
    return m_pRenderer;
}

HWND TMSWindow::GetHWND() const                                     // 0x5b40
{
    return m_hWnd;
}

TMSWindow::~TMSWindow()                                             // 0x5b50
{
}

TOSHI_DEFINE_CLASS(TMSWindow, TObject)
TOSHI_DEFINE_CLASS_FUNCTIONS_CONCRETE(TMSWindow)

} // namespace Toshi
