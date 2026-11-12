// Z:\Toshi\Source\TGUI - TGUIWindow. The original file name is not in the binary's strings.
// NotifyParentChange, the focus map functions and the (de)serialisation are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIWindow.h"
#include "TGUIWidgetInfo.h"
#include "PPropertyValue.h"

namespace Toshi {

TGUIWidgetInfo* TGUIWindow::ms_widget_info;
TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIWindow::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUIWindow::ms_oPropertySet;

TGUIWindow::TGUIWindow()
    : m_pDefaultFocus(0), m_oFocusMap(10)
{
    m_pWidgetInfo = ms_widget_info;
}

TGUIWindow::~TGUIWindow()
{
}

void TGUIWindow::SetDefaultFocus(TGUIWidget* widget)
{
    m_pDefaultFocus = widget;
    m_pFocus = widget;
}

void TGUIWindow::Set_default_focus_property(const PPropertyValue& value)
{
    m_pDefaultFocus = FindNamedChild(value.GetTPCString());
}

void TGUIWindow::NotifyFocusGained(TGUIWidget* from, TGUIWidget* to)
{
    TGUIWidget::NotifyFocusGained(from, to);
}

// Remembers where the focus went so the window can give it back later
void TGUIWindow::NotifyFocusLost(TGUIWidget* from, TGUIWidget* to)
{
    m_pFocus = to;
    TGUIWidget::NotifyFocusLost(from, to);
}

TClass TGUIWindow::m_sClass("TGUIWindow", &TGUIWidget::m_sClass, TGUIWindow::CreateObject,
                            TGUIWindow::CreateObjectInPlace, TGUIWindow::InitialiseStatic,
                            TGUIWindow::DeinitialiseStatic, 0x10000);

TClass& TGUIWindow::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIWindow::DeinitialiseStatic()
{
    delete ms_widget_info;
    for (TArray<TGUIPropertySpec*>::Iterator it(*ms_oPropertySet); it.IsValid(); ++it) {
        delete *it;
    }
    delete ms_oPropertySet;
    delete ms_oPropertySetOrdered;
    ms_oPropertySet = 0;
    ms_oPropertySetOrdered = 0;
}

void __stdcall TGUIWindow::InitialiseStatic()
{
}

// TGUIWindow is abstract, so its factory functions create nothing
TObject* __stdcall TGUIWindow::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIWindow::CreateObject()
{
    return 0;
}

} // namespace Toshi
