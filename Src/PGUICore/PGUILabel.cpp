// PGUILabel accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUILabel.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUILabel::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUILabel::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUILabel::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUILabel::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUILabel::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUILabel::Serialise(PProperties* properties)
{
    if (!TGUIWidget::Serialise(properties)) {
        return false;
    }
    return true;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUILabel::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUILabel::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void PGUILabel::Pack()
{
    if (GetStyle() != 0)
    {
        int width = GetWidth();
        int height = GetHeight();

        SetComponentBBox(0, 0, 0, width, height);
        SetComponentBBox(1, 0, 0, width, height);
    }

    SetValidated(true);
}

PGUILabel::PGUILabel(const PGUILabel& other)
    : Toshi::TGUIWidget(other)
{
}

PGUILabel* PGUILabel::Clone() const
{
    return new PGUILabel(*this);
}
