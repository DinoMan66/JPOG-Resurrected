// PGUIButton accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIButton.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIButton::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIButton::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIButton::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIButton::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUIButton::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIButton::Serialise(PProperties* properties)
{
    if (!TGUIWidget::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIButton::AcceptsFocus() const
{
    return true;
}

bool PGUIButton::IsPressed() const
{
    return IsState(STATE_PRESSED);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIButton::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIButton::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void PGUIButton::SetPressed(bool pressed)
{
    SetState(STATE_PRESSED, pressed);
}

Toshi::TObject* __stdcall PGUIButton::CreateObjectInPlace(void* memory)
{
    return 0;
}

Toshi::TObject* __stdcall PGUIButton::CreateObject()
{
    return 0;
}
