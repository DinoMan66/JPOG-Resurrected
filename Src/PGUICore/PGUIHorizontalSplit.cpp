// PGUIHorizontalSplit accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIHorizontalSplit.h"
#include "PPropertyValue.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIHorizontalSplit::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIHorizontalSplit::ms_oPropertySet;

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIHorizontalSplit::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIHorizontalSplit::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

Toshi::TGUIWidgetInfo* PGUIHorizontalSplit::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIHorizontalSplit::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

Toshi::TGUIWidget* PGUIHorizontalSplit::GetTopWidget() const
{
    if (GetChildCount() > 0)
    {
        return GetChildren().Head();
    }

    return 0;
}

Toshi::TGUIWidget* PGUIHorizontalSplit::GetBottomWidget() const
{
    if (GetChildCount() >= 2)
    {
        return GetChildren().Head()->Next();
    }

    return 0;
}

bool PGUIHorizontalSplit::Deserialise(const PProperties* properties)
{
    if (!PGUIPanel::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIHorizontalSplit::Serialise(PProperties* properties)
{
    if (!PGUIPanel::Serialise(properties)) {
        return false;
    }
    return true;
}

PGUIHorizontalSplit* PGUIHorizontalSplit::Clone() const
{
    return new PGUIHorizontalSplit(*this);
}

PPropertyValue PGUIHorizontalSplit::Get_stretchbottom_property() const
{
    return PPropertyValue(m_fStretchBottom);
}

void PGUIHorizontalSplit::Set_stretchbottom_property(const PPropertyValue& value)
{
    m_fStretchBottom = value.GetFloat();
}

PPropertyValue PGUIHorizontalSplit::Get_stretchtop_property() const
{
    return PPropertyValue(m_fStretchTop);
}

void PGUIHorizontalSplit::Set_stretchtop_property(const PPropertyValue& value)
{
    m_fStretchTop = value.GetFloat();
}

PGUIHorizontalSplit::PGUIHorizontalSplit(const PGUIHorizontalSplit& other)
    : PGUIPanel(other)
{
    m_fStretchTop = other.m_fStretchTop;
    m_fStretchBottom = other.m_fStretchBottom;
}

bool PGUIHorizontalSplit::Val_stretchtop_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_FLOAT)) {
        return false;
    }
    return value.GetFloat() >= 0.0f;
}
