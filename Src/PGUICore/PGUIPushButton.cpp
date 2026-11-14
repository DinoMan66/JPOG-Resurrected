// PGUIPushButton accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIPushButton.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIPushButton::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIPushButton::ms_oPropertySet;

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIPushButton::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIPushButton::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void PGUIPushButton::Pack()
{
    if (GetStyle() != 0)
    {
        int width = GetWidth();
        int height = GetHeight();

        SetComponentBBox(0, 0, 0, width, height);
        SetComponentBBox(1, 0, 0, width, height);
        SetComponentBBox(2, 0, 0, width, height);
    }

    SetValidated(true);
}

PGUIPushButton::PGUIPushButton(const PGUIPushButton& other)
    : PGUIButton(other)
{
}

PGUIPushButton* PGUIPushButton::Clone() const
{
    return new PGUIPushButton(*this);
}

bool PGUIPushButton::Serialise(PProperties* properties)
{
    if (!PGUIButton::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIPushButton::Deserialise(const PProperties* properties)
{
    if (!PGUIButton::Deserialise(properties)) {
        return false;
    }
    return true;
}

Toshi::TGUIWidgetInfo* PGUIPushButton::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIPushButton::GetStaticWidgetInfo()
{
    return ms_widget_info;
}
