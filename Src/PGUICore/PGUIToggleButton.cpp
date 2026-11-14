// PGUIToggleButton accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIToggleButton.h"
#include "PPropertyValue.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIToggleButton::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIToggleButton::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIToggleButton::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIToggleButton::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUIToggleButton::IsToggled() const
{
    return IsState(STATE_TOGGLED);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIToggleButton::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIToggleButton::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

// the "test" property is a leftover: it accepts any value, always reads true and ignores writes
bool PGUIToggleButton::Val_test_property(const PPropertyValue& value)
{
    return true;
}

PPropertyValue PGUIToggleButton::Get_test_property() const
{
    return PPropertyValue(true);
}

void PGUIToggleButton::Set_test_property(const PPropertyValue& value)
{
}

PGUIToggleButton::PGUIToggleButton(const PGUIToggleButton& other)
    : PGUIButton(other)
{
}

PGUIToggleButton* PGUIToggleButton::Clone() const
{
    return new PGUIToggleButton(*this);
}

bool PGUIToggleButton::Serialise(PProperties* properties)
{
    if (!PGUIButton::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIToggleButton::Deserialise(const PProperties* properties)
{
    if (!PGUIButton::Deserialise(properties)) {
        return false;
    }
    return true;
}

void PGUIToggleButton::SetToggled(bool toggled)
{
    SetState(STATE_TOGGLED, toggled);
}
