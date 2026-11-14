// PGUIPanel accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIPanel.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIPanel::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIPanel::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIPanel::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIPanel::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUIPanel::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIPanel::Serialise(PProperties* properties)
{
    if (!TGUIWidget::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIPanel::AllowsChildren() const
{
    return true;
}

bool PGUIPanel::IsEditing() const
{
    return IsState(STATE_EDITING);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIPanel::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIPanel::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

void PGUIPanel::SetEditing(bool editing)
{
    SetState(STATE_EDITING, editing);
}

void PGUIPanel::Pack()
{
    PackChildren();

    if (GetStyle() != 0)
    {
        int width = GetWidth();
        int height = GetHeight();

        SetComponentBBox(0, 0, 0, width, height);
    }

    SetValidated(true);
}

PGUIPanel::PGUIPanel(const PGUIPanel& other)
    : Toshi::TGUIWidget(other)
{
}

PGUIPanel* PGUIPanel::Clone() const
{
    return new PGUIPanel(*this);
}
