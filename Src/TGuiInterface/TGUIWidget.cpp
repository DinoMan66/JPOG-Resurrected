// Z:\Toshi\Source\TGUI - TGUIWidget. The original file name is not in the binary's strings.
// Only the accessors and the class boilerplate are written so far.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIWidget.h"
#include "TGUIWidgetInfo.h"
#include "TGUILayoutManager.h"
#include "TGUIRectangle.h"
#include "TGUIStyle.h"
#include "TGUITextureSection.h"
#include "TGUIScreen.h"
#include "TGUIWindow.h"
#include "PPropertyValue.h"

namespace Toshi {

void TGUIWidget::GetBBox(TGUIRectangle& box) const
{
    box = TGUIRectangle(m_sX, m_sY, m_sWidth, m_sHeight);
}

// Centres the widget in its parent
void TGUIWidget::SetPositionCenter()
{
    int parentWidth = m_pParent->GetWidth();
    int parentHeight = m_pParent->GetHeight();
    SetPosition((parentWidth - GetWidth()) / 2, (parentHeight - GetHeight()) / 2);
}

// Is the point inside the widget? The point is given in the parent's coordinates and returned relative to the widget
bool TGUIWidget::HitTest(int x, int y, int& localX, int& localY)
{
    int relativeX = x - m_sX;
    int relativeY = y - m_sY;
    if (relativeX >= 0 && relativeX < m_sWidth && relativeY >= 0 && relativeY < m_sHeight) {
        localX = relativeX;
        localY = relativeY;
        return true;
    }
    return false;
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

void TGUIWidget::SetFixedSize(int width, int height)
{
    if (m_sWidth != width || m_sHeight != height) {
        m_bValidated = false;
    }
    m_sWidth = width;
    m_sHeight = height;
    m_eSizeModeHoriz = SIZE_MODE_0;
    m_eSizeModeVert = SIZE_MODE_0;
}

void TGUIWidget::SetFixedHeight(int height)
{
    if (m_sHeight != height) {
        m_bValidated = false;
    }
    m_sHeight = height;
    m_eSizeModeVert = SIZE_MODE_0;
}

void TGUIWidget::SetFixedWidth(int width)
{
    if (m_sWidth != width) {
        m_bValidated = false;
    }
    m_sWidth = width;
    m_eSizeModeHoriz = SIZE_MODE_0;
}

// The height and width only change while the widget's size is not fixed
void TGUIWidget::SetHeight(int height)
{
    if (m_eSizeModeVert != SIZE_MODE_0) {
        if (m_sHeight != height) {
            m_bValidated = false;
        }
        m_sHeight = height;
    }
}

void TGUIWidget::SetWidth(int width)
{
    if (m_eSizeModeHoriz != SIZE_MODE_0) {
        if (m_sWidth != width) {
            m_bValidated = false;
        }
        m_sWidth = width;
    }
}

// A widget can be resized or moved by its layout unless its parent has a layout manager
bool TGUIWidget::CanResizeHoriz() const
{
    if (m_eSizeModeHoriz != SIZE_MODE_0) {
        if (m_eSizeModeHoriz != SIZE_MODE_2) {
            return false;
        }
        if (m_pParent != 0 && m_pParent->GetLayoutManager() != 0) {
            return false;
        }
    }
    return true;
}

bool TGUIWidget::CanResizeVert() const
{
    if (m_eSizeModeVert != SIZE_MODE_0) {
        if (m_eSizeModeVert != SIZE_MODE_2) {
            return false;
        }
        if (m_pParent != 0 && m_pParent->GetLayoutManager() != 0) {
            return false;
        }
    }
    return true;
}

bool TGUIWidget::IsDescendantOf(const TGUIWidget* ancestor) const
{
    for (const TGUIWidget* widget = m_pParent; widget != 0; widget = widget->m_pParent) {
        if (widget == ancestor) {
            return true;
        }
    }
    return false;
}

bool TGUIWidget::IsAncestorOf(const TGUIWidget* descendant) const
{
    if (descendant == 0) {
        return false;
    }
    return descendant->IsDescendantOf(this);
}

// The window is the closest widget (this one included) that is a TGUIWindow
TGUIWindow* TGUIWidget::GetWindow()
{
    for (TGUIWidget* widget = this; widget != 0; widget = widget->m_pParent) {
        if (widget->IsA(TGUIWindow::m_sClass)) {
            return (TGUIWindow*)widget;
        }
    }
    return 0;
}

// The widget and everything below it give up the focus
void TGUIWidget::RemoveFocus()
{
    SetState(STATE_FOCUSED, 0u);
    TNodeList<TGUIWidget>::Iterator end(m_oChildren.End());
    for (TNodeList<TGUIWidget>::Iterator it = m_oChildren.Begin(); it != end; ++it) {
        it->RemoveFocus();
    }
}

// The screen is told that this widget lost the focus
void TGUIWidget::NotifyFocusLost(TGUIWidget* from, TGUIWidget* to)
{
    GetScreen()->ReleaseFocus(this);
}

void TGUIWidget::RequestFocus()
{
    GetScreen()->ChangeWidgetFocus(this, false);
}

// The screen is the closest widget (this one included) that is a TGUIScreen
TGUIScreen* TGUIWidget::GetScreen()
{
    for (TGUIWidget* widget = this; widget != 0; widget = widget->m_pParent) {
        if (widget->IsA(TGUIScreen::m_sClass)) {
            return (TGUIScreen*)widget;
        }
    }
    return 0;
}

// A widget without a style has no margins
void TGUIWidget::GetMargins(int& left, int& right, int& top, int& bottom)
{
    if (m_pStyle != 0) {
        m_pStyle->GetMargins(left, right, top, bottom);
    } else {
        left = 0;
        right = 0;
        top = 0;
        bottom = 0;
    }
}

// The interior is the widget's size without the style's margins
void TGUIWidget::GetInteriorSize(int& width, int& height) const
{
    if (m_pStyle == 0) {
        width = m_sWidth;
        height = m_sHeight;
    } else {
        width = m_sWidth - m_pStyle->GetMarginLeft() - m_pStyle->GetMarginRight();
        height = m_sHeight - m_pStyle->GetMarginTop() - m_pStyle->GetMarginBottom();
    }
}

// Only widgets with a calculated size mode are resized
void TGUIWidget::SetSize(int width, int height)
{
    if (m_eSizeModeHoriz != SIZE_MODE_0) {
        if (m_eSizeModeVert != SIZE_MODE_0) {
            if (m_sWidth != width || m_sHeight != height) {
                m_bValidated = false;
            }
            m_sWidth = width;
            m_sHeight = height;
        }
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

bool TGUIWidget::OnPointerMove(int x, int y)
{
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

bool TGUIWidget::Val_sizemode_horiz_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT)
        && (value.GetInteger() == 0 || value.GetInteger() == 1 || value.GetInteger() == 2);
}

bool TGUIWidget::Val_sizemode_vert_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT)
        && (value.GetInteger() == 0 || value.GetInteger() == 1 || value.GetInteger() == 2);
}

bool TGUIWidget::Val_placemode_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && (value.GetInteger() == 0 || value.GetInteger() == 1);
}

bool TGUIWidget::Val_xpos_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && value.GetInteger() >= 0;
}

bool TGUIWidget::Val_ypos_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && value.GetInteger() >= 0;
}

// The widget has to end inside its parent
bool TGUIWidget::Val_width_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (m_pParent == 0) {
        return true;
    }
    return m_sX + value.GetInteger() < m_pParent->GetWidth();
}

bool TGUIWidget::Val_height_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (m_pParent == 0) {
        return true;
    }
    return m_sY + value.GetInteger() < m_pParent->GetHeight();
}

void TGUIWidget::Set_height_property(const PPropertyValue& value)
{
    if (m_sHeight != value.GetInteger()) {
        m_bValidated = false;
    }
    m_sHeight = value.GetInteger();
}

void TGUIWidget::Set_width_property(const PPropertyValue& value)
{
    if (m_sWidth != value.GetInteger()) {
        m_bValidated = false;
    }
    m_sWidth = value.GetInteger();
}

bool TGUIWidget::Val_name_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_TPCSTRING);
}

PPropertyValue TGUIWidget::Get_name_property() const
{
    return PPropertyValue(m_oName);
}

void TGUIWidget::Set_name_property(const PPropertyValue& value)
{
    m_oName = value.GetTPCString();
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

void TGUIWidget::Create(TGUIInterface* gui, TGUIStyle* style, const TPCString& name)
{
    m_pInterface = gui;
    SetStyle(style);
    m_oName = name;
}

// The widget class's own properties come first, then one per parameter of the style
int TGUIWidget::GetPropertyCount() const
{
    if (m_pStyle != 0) {
        return m_pStyle->GetParameterCount() + m_pWidgetInfo->GetPropertyCount();
    }
    return m_pWidgetInfo->GetPropertyCount();
}

// Index runs over the widget class's properties first, then over the parameters of the style
const TGUIPropertySpec* TGUIWidget::GetPropertyInfo(int index) const
{
    if (index < m_pWidgetInfo->GetPropertyCount()) {
        return m_pWidgetInfo->GetPropertyInfo(index);
    }
    return m_pStyle->GetParameterInfo(index - m_pWidgetInfo->GetPropertyCount())->m_pPropertySpec;
}

bool TGUIWidget::CanMove() const
{
    if (m_ePlaceMode == PLACE_MODE_0) {
        return true;
    }
    if (m_ePlaceMode == PLACE_MODE_1) {
        return true;
    }
    return false;
}

// The children are numbered from 0 in list order
TGUIWidget* TGUIWidget::FindIndexedChild(int index) const
{
    int position = 0;
    for (TNodeList<TGUIWidget>::Iterator it = m_oChildren.Begin(); it != m_oChildren.End(); ++it) {
        if (position++ == index) {
            return it.Get();
        }
    }
    return 0;
}

// The direction names are indexed by NeighbourDirection; six of them are stored
TGUIWidget::NeighbourDirection TGUIWidget::GetDirectionEnum(const TPCString& name)
{
    for (int i = 0; i < 6; i++) {
        if (name == ms_paDirectionName[i]) {
            return (NeighbourDirection)i;
        }
    }
    return NEIGHBOUR_DIRECTION_NONE;
}

// A depth-first search for the child with the given name
TGUIWidget* TGUIWidget::FindNamedChild(const TPCString& name) const
{
    TNodeList<TGUIWidget>::Iterator end(m_oChildren.End());
    for (TNodeList<TGUIWidget>::Iterator it = m_oChildren.Begin(); it != end; ++it) {
        if (it->m_oName == name) {
            return it.Get();
        }
        TGUIWidget* found = it->FindNamedChild(name);
        if (found != 0) {
            return found;
        }
    }
    return 0;
}

// The nearest ancestor (or this widget) that manages its children, or this widget when there is none
TGUIWidget* TGUIWidget::FindChildManager()
{
    for (TGUIWidget* widget = this; widget != 0; widget = widget->m_pParent) {
        if (widget->ManagesChildren()) {
            return widget;
        }
    }
    return this;
}

// A widget can take focus when it and all its ancestors are enabled and visible
bool TGUIWidget::CanFocus()
{
    for (TGUIWidget* widget = this; widget != 0; widget = widget->m_pParent) {
        if (!widget->IsEnabled() || !widget->IsVisible()) {
            return false;
        }
    }
    return true;
}

// The state variables of the widget class name the bits of m_uiState they control
void TGUIWidget::Set_state_property(const TPCString& name, bool set)
{
    const TGUIStateVarInfo* info = m_pWidgetInfo->GetStateVarInfo(name);
    if (info != 0) {
        if (set == true) {
            m_uiState |= info->m_uiStateBits;
        } else {
            m_uiState &= ~info->m_uiStateBits;
        }
    }
}

void TGUIWidget::Set_state_property(int index, bool set)
{
    const TGUIStateVarInfo* info = m_pWidgetInfo->GetStateVarInfo(index);
    if (set == true) {
        m_uiState |= info->m_uiStateBits;
    } else {
        m_uiState &= ~info->m_uiStateBits;
    }
}

bool TGUIWidget::Get_state_property(int index)
{
    return (m_uiState & m_pWidgetInfo->GetStateVarInfo(index)->m_uiStateBits) != 0;
}

bool TGUIWidget::Get_state_property(const TPCString& name)
{
    const TGUIStateVarInfo* info = m_pWidgetInfo->GetStateVarInfo(name);
    if (info != 0) {
        return (m_uiState & info->m_uiStateBits) != 0;
    }
    return false;
}

void TGUIWidget::SetParameter(int index, const TLString& value)
{
    m_pStyle->GetParameterInfo(index);
    m_pParameters[index].SetTLString(value);
    InvalidateComponentCache(false);
}

void TGUIWidget::SetParameter(int index, TGUITextureSection* value)
{
    m_pStyle->GetParameterInfo(index);
    m_pParameters[index].SetTObject(value);
    InvalidateComponentCache(false);
}

PPropertyValue TGUIWidget::GetParameter(int index) const
{
    m_pStyle->GetParameterInfo(index);
    return m_pParameters[index];
}

bool TGUIWidget::Val_style_parameter(const PPropertyValue& value, TGUIStyleParameterInfo* info)
{
    return true;
}

PPropertyValue TGUIWidget::Get_style_parameter(TGUIStyleParameterInfo* info) const
{
    int index = info->m_iIndex;
    m_pStyle->GetParameterInfo(index);
    return m_pParameters[index];
}

// Positions are relative to the parent, so the device position is the sum along the chain of parents
void TGUIWidget::TransformDeviceToWidget(int x, int y, int& widgetX, int& widgetY) const
{
    const TGUIWidget* widget = this;
    const TGUIWidget* parent = widget->m_pParent;
    while (parent != 0) {
        x -= widget->m_sX;
        y -= widget->m_sY;
        widget = parent;
        parent = widget->m_pParent;
    }
    widgetX = x - widget->m_sX;
    widgetY = y - widget->m_sY;
}

void TGUIWidget::TransformWidgetToDevice(int x, int y, int& deviceX, int& deviceY) const
{
    const TGUIWidget* widget = this;
    const TGUIWidget* parent = widget->m_pParent;
    while (parent != 0) {
        x += widget->m_sX;
        y += widget->m_sY;
        widget = parent;
        parent = widget->m_pParent;
    }
    deviceX = x + widget->m_sX;
    deviceY = y + widget->m_sY;
}

// The widget class's properties are searched first, then the parameters of the style
const TGUIPropertySpec* TGUIWidget::FindPropertyInfo(const TPCString& name) const
{
    const TGUIPropertySpec* info = TGUIDeserialisable::FindPropertyInfo(name);
    if (info != 0) {
        return info;
    }
    if (m_pStyle != 0) {
        const TGUIStyleParameterInfo* parameter = m_pStyle->GetParameterInfo(name);
        if (parameter != 0) {
            return parameter->m_pPropertySpec;
        }
    }
    return 0;
}

} // namespace Toshi
