// TGUIScreen accessors and the input manager stack. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIScreen.h"
#include "TGUIInputContext.h"

namespace Toshi {

TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIScreen::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUIScreen::ms_oPropertySet;

bool TGUIScreen::Deserialise(const PProperties* properties)
{
    return false;
}

bool TGUIScreen::Serialise(PProperties* properties)
{
    return false;
}

TGUIWidget* TGUIScreen::AllowsFocus(TGUIWidget* from)
{
    return from;
}

void TGUIScreen::GetPointerPosition(int& x, int& y) const
{
    x = m_iPointerX;
    y = m_iPointerY;
}

void TGUIScreen::SetPointerSpeed(float speed)
{
    m_fPointerSpeed = speed;
}

bool TGUIScreen::IsPointerVisible() const
{
    return m_bPointerVisible;
}

void TGUIScreen::SetPointerVisible(bool visible)
{
    m_bPointerVisible = visible;
}

TGUIWidget* TGUIScreen::GetFocusedWidget() const
{
    return m_pFocusedWidget;
}

TGUIWindow* TGUIScreen::GetFocusedWindow() const
{
    return m_pFocusedWindow;
}

TGUIInputContext* TGUIScreen::GetInputContext() const
{
    return m_pInputContext;
}

TGUIAudioContext* TGUIScreen::GetAudioContext() const
{
    return m_pAudioContext;
}

void TGUIScreen::SetAudioContext(TGUIAudioContext* context)
{
    m_pAudioContext = context;
}

TGUIDisplayContext* TGUIScreen::GetDisplayContext() const
{
    return m_pDisplayContext;
}

void TGUIScreen::SetDisplayContext(TGUIDisplayContext* context)
{
    m_pDisplayContext = context;
}

TGUIInputManager* TGUIScreen::GetInputManager()
{
    return m_apInputManagers[m_iInputManagerIndex];
}

void TGUIScreen::PushInputManager(TGUIInputManager* manager)
{
    m_iInputManagerIndex++;
    if (m_iInputManagerIndex < 8) {
        m_apInputManagers[m_iInputManagerIndex] = manager;
    }
}

void TGUIScreen::PopInputManager(TGUIInputManager* manager)
{
    int top = m_iInputManagerIndex - 1;
    if (top < 0) {
        m_iInputManagerIndex = 0;
    } else {
        m_iInputManagerIndex = top;
    }
}

TGUIWidget* TGUIScreen::GetFocusGrabWidget() const
{
    int top = m_unk100 - 1;
    return m_unk108[top];
}

bool TGUIScreen::IsPaintContinued()
{
    return m_unk134 != 0;
}

void TGUIScreen::NotifyDescendantCanFocus(TGUIWidget* widget)
{
}

void TGUIScreen::NotifyFocusGained()
{
}

void TGUIScreen::NotifyFocusLost()
{
}

void TGUIScreen::GrabPointer(TGUIWidget* widget)
{
    m_pPointerGrabWidget = widget;
}

void TGUIScreen::Pack()
{
    PackChildren();
}

void TGUIScreen::Layout(short width, short height)
{
    SetLayoutValid(true);
}

void __stdcall TGUIScreen::pointer_out_callback(TGUIWidget* widget)
{
    widget->OnPointerExit();
}

const TArray<TGUIPropertySpec*>* TGUIScreen::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIScreen::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void TGUIScreen::ContinuePaint()
{
    if (m_unk134) {
        Paint(m_unk134);
    }
}

void TGUIScreen::RestartPaint()
{
    Paint(0);
}

void TGUIScreen::SetPointerAccel(int accel, int unused, int limit)
{
    m_unk138 = accel;
    m_unk13C = accel;
    m_unk140 = limit;
}

void TGUIScreen::SetPointerImage(TGUITextureSection* image, int hotspotX, int hotspotY)
{
    m_pPointerImage = image;
    m_unk128 = hotspotX;
    m_unk12C = hotspotY;
}

// The context knows the screen it belongs to: detach the old context, attach the new one
void TGUIScreen::SetInputContext(TGUIInputContext* context)
{
    if (m_pInputContext)
        m_pInputContext->SetScreen(0);
    m_pInputContext = context;
    if (context)
        context->SetScreen(this);
}

// Releases of the buttons in bits 9-12 of the doodad are consumed by the screen itself
bool TGUIScreen::OnButtonRelease(TInputInterface::InputEvent* event, int doodad)
{
    if (doodad & 0x1E00)
        return true;
    return TGUIWidget::OnButtonRelease(event, doodad);
}

} // namespace Toshi
