// Z:\Toshi\Source\TGUI - TGUIWidget. The original file name is not in the binary's strings.
// Only the accessors and the class boilerplate are written so far.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIWidget.h"
#include "TGUIWidgetInfo.h"
#include "TGUILayoutManager.h"
#include "TGUIRectangle.h"
#include "TGUIStyle.h"
#include "PPropertyValue.h"

namespace Toshi {

void TGUIWidget::GetBBox(TGUIRectangle& box) const
{
    box = TGUIRectangle(m_sX, m_sY, m_sWidth, m_sHeight);
}

// Setting a position twice to the same value changes nothing
void TGUIWidget::SetPosition(int x, int y)
{
    if (m_sX != x || m_sY != y)
    {
        m_sX = x;
        m_sY = y;
    }
}

// The widget owns its layout manager
void TGUIWidget::SetLayoutManager(TGUILayoutManager* manager)
{
    if (m_pLayoutManager)
    {
        delete m_pLayoutManager;
    }
    m_pLayoutManager = manager;
}

TGUIWidgetInfo* TGUIWidget::ms_widget_info;
TPCString* TGUIWidget::ms_paDirectionName;
TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIWidget::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUIWidget::ms_oPropertySet;

int TGUIWidget::GetInteriorWidth() const
{
    const TGUIStyle* style = m_pStyle;
    int width = m_sWidth;
    if (style)
    {
        width -= style->GetMarginLeft();
        width -= style->GetMarginRight();
    }
    return width;
}

int TGUIWidget::GetInteriorHeight() const
{
    const TGUIStyle* style = m_pStyle;
    int height = m_sHeight;
    if (style)
    {
        height -= style->GetMarginTop();
        height -= style->GetMarginBottom();
    }
    return height;
}

bool TGUIWidget::OnPointerExit()
{
    SetState(STATE_ROLLOVER, 0u);
    return false;
}

bool TGUIWidget::OnPointerEnter()
{
    const unsigned int rollover = STATE_ROLLOVER;
    SetState(rollover, rollover);
    return false;
}

// The notifications and the focus question travel up the tree until a widget handles them
void TGUIWidget::NotifyDescendantRemoved(TGUIWidget* ancestor, TGUIWidget* descendant)
{
    if (m_pParent)
    {
        m_pParent->NotifyDescendantRemoved(ancestor, descendant);
    }
}

void TGUIWidget::NotifyDescendantRemoval(TGUIWidget* descendant)
{
    if (m_pParent)
    {
        m_pParent->NotifyDescendantRemoval(descendant);
    }
}

void TGUIWidget::NotifyDescendantAddition(TGUIWidget* descendant)
{
    if (m_pParent)
    {
        m_pParent->NotifyDescendantAddition(descendant);
    }
}

TGUIWidget* TGUIWidget::AllowsFocus(TGUIWidget* from)
{
    if (m_pParent)
    {
        return m_pParent->AllowsFocus(from);
    }
    return 0;
}

void TGUIWidget::OrderPosition(int position)
{
    if (m_pParent)
    {
        m_pParent->OrderChildSetPosition(this, position);
    }
}

void TGUIWidget::OrderBackward()
{
    if (m_pParent)
    {
        m_pParent->OrderChildMovePosition(this, 1);
    }
}

void TGUIWidget::OrderForward()
{
    if (m_pParent)
    {
        m_pParent->OrderChildMovePosition(this, -1);
    }
}

void TGUIWidget::OrderToBack()
{
    if (m_pParent)
    {
        m_pParent->OrderChildSetPosition(this, 0);
    }
}

void TGUIWidget::OrderToFront()
{
    if (m_pParent)
    {
        m_pParent->OrderChildSetPosition(this, -1);
    }
}

bool TGUIWidget::Val_animsync_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue TGUIWidget::Get_animsync_property() const
{
    return PPropertyValue(m_fAnimSync);
}

void TGUIWidget::Set_animsync_property(const PPropertyValue& value)
{
    m_fAnimSync = value.GetFloat();
}

PPropertyValue TGUIWidget::Get_placemode_property() const
{
    return PPropertyValue(m_ePlaceMode);
}

void TGUIWidget::Set_placemode_property(const PPropertyValue& value)
{
    m_ePlaceMode = (PlaceMode)value.GetInteger();
}

PPropertyValue TGUIWidget::Get_sizemode_vert_property() const
{
    return PPropertyValue(m_eSizeModeVert);
}

void TGUIWidget::Set_sizemode_vert_property(const PPropertyValue& value)
{
    m_eSizeModeVert = (SizeMode)value.GetInteger();
}

PPropertyValue TGUIWidget::Get_sizemode_horiz_property() const
{
    return PPropertyValue(m_eSizeModeHoriz);
}

void TGUIWidget::Set_sizemode_horiz_property(const PPropertyValue& value)
{
    m_eSizeModeHoriz = (SizeMode)value.GetInteger();
}

PPropertyValue TGUIWidget::Get_height_property() const
{
    return PPropertyValue(m_sHeight);
}

PPropertyValue TGUIWidget::Get_width_property() const
{
    return PPropertyValue(m_sWidth);
}

PPropertyValue TGUIWidget::Get_ypos_property() const
{
    return PPropertyValue(m_sY);
}

void TGUIWidget::Set_ypos_property(const PPropertyValue& value)
{
    m_sY = value.GetInteger();
}

PPropertyValue TGUIWidget::Get_xpos_property() const
{
    return PPropertyValue(m_sX);
}

void TGUIWidget::Set_xpos_property(const PPropertyValue& value)
{
    m_sX = value.GetInteger();
}

bool TGUIWidget::Val_name_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_TPCSTRING);
}

PPropertyValue TGUIWidget::Get_name_property() const
{
    return PPropertyValue(m_oName);
}

TClass TGUIWidget::m_sClass("TGUIWidget", &TGUIDeserialisable::m_sClass, TGUIWidget::CreateObject,
                            TGUIWidget::CreateObjectInPlace, TGUIWidget::InitialiseStatic,
                            TGUIWidget::DeinitialiseStatic, 0x10000);

TClass& TGUIWidget::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIWidget::DeinitialiseStatic()
{
    delete ms_widget_info;
    for (TArray<TGUIPropertySpec*>::Iterator it(*ms_oPropertySet); it.IsValid(); ++it) {
        delete *it;
    }
    delete ms_oPropertySet;
    delete ms_oPropertySetOrdered;
    ms_oPropertySet = 0;
    ms_oPropertySetOrdered = 0;
    if (ms_paDirectionName != 0) {
        delete[] ms_paDirectionName;
    }
}

void __stdcall TGUIWidget::InitialiseStatic()
{
}

// TGUIWidget is abstract (Clone is pure virtual), so its factory functions create nothing
TObject* __stdcall TGUIWidget::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIWidget::CreateObject()
{
    return 0;
}

} // namespace Toshi
