// PGUIVerticalSplit accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIVerticalSplit.h"
#include "PPropertyValue.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIVerticalSplit::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIVerticalSplit::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIVerticalSplit::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIVerticalSplit::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIVerticalSplit::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIVerticalSplit::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

Toshi::TGUIWidget* PGUIVerticalSplit::GetLeftWidget() const
{
    if (GetChildCount() > 0)
    {
        return GetChildren().Head();
    }

    return 0;
}

Toshi::TGUIWidget* PGUIVerticalSplit::GetRightWidget() const
{
    if (GetChildCount() >= 2)
    {
        return GetChildren().Head()->Next();
    }

    return 0;
}

bool PGUIVerticalSplit::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIVerticalSplit::Serialise(PProperties* properties)
{
    if (!PGUIPanel::Serialise(properties)) {
        return false;
    }
    return true;
}

PGUIVerticalSplit* PGUIVerticalSplit::Clone() const
{
    return new PGUIVerticalSplit(*this);
}

PPropertyValue PGUIVerticalSplit::Get_stretchright_property() const
{
    return PPropertyValue(m_fStretchRight);
}

void PGUIVerticalSplit::Set_stretchright_property(const PPropertyValue& value)
{
    m_fStretchRight = value.GetFloat();
}

PPropertyValue PGUIVerticalSplit::Get_stretchleft_property() const
{
    return PPropertyValue(m_fStretchLeft);
}

void PGUIVerticalSplit::Set_stretchleft_property(const PPropertyValue& value)
{
    m_fStretchLeft = value.GetFloat();
}

PGUIVerticalSplit::PGUIVerticalSplit(const PGUIVerticalSplit& other)
    : PGUIPanel(other)
{
    m_fStretchLeft = other.m_fStretchLeft;
    m_fStretchRight = other.m_fStretchRight;
}

bool PGUIVerticalSplit::Val_stretchleft_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_FLOAT)) {
        return false;
    }
    return value.GetFloat() >= 0.0f;
}
