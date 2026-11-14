// PGUIListBox style properties. They are in a translation unit of their own: the original calls SetListItemStyle
// out of line from Set_listitemstyle_property, so the two cannot share a file with it.
#define PGUICORE_EXPORTS
#include "PGUIListBox.h"
#include "PPropertyValue.h"
#include "TGUIStyle.h"

bool PGUIListBox::Val_scrollbarstyle_property(const PPropertyValue& value)
{
    if (value.CanBeType(&Toshi::TGUIStyle::m_sClass)) {
        return true;
    }
    if (value.CanBeType(PPropertyValue::TYPE_TPCSTRING)) {
        return true;
    }
    return false;
}

PPropertyValue PGUIListBox::Get_scrollbarstyle_property() const
{
    return PPropertyValue(m_pScrollBarStyle ? m_pScrollBarStyle->GetName() : Toshi::TPCString());
}

void PGUIListBox::Set_scrollbarstyle_property(const PPropertyValue& value)
{
    if (value.IsType(&Toshi::TGUIStyle::m_sClass)) {
        SetScrollBarStyle(static_cast<Toshi::TGUIStyle*>(value.GetTObject()));
    } else if (value.IsType(PPropertyValue::TYPE_TPCSTRING)) {
        SetScrollBarStyle(value.GetTPCString());
    }
}

bool PGUIListBox::Val_listitemstyle_property(const PPropertyValue& value)
{
    if (value.CanBeType(&Toshi::TGUIStyle::m_sClass)) {
        return true;
    }
    if (value.CanBeType(PPropertyValue::TYPE_TPCSTRING)) {
        return true;
    }
    return false;
}

PPropertyValue PGUIListBox::Get_listitemstyle_property() const
{
    return PPropertyValue(m_pListItemStyle ? m_pListItemStyle->GetName() : Toshi::TPCString());
}

void PGUIListBox::Set_listitemstyle_property(const PPropertyValue& value)
{
    if (value.IsType(&Toshi::TGUIStyle::m_sClass)) {
        SetListItemStyle(static_cast<Toshi::TGUIStyle*>(value.GetTObject()));
    } else if (value.IsType(PPropertyValue::TYPE_TPCSTRING)) {
        SetListItemStyle(value.GetTPCString());
    }
}
