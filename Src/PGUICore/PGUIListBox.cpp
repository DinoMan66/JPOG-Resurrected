// PGUIListBox accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIListBox.h"
#include "PPropertyValue.h"
#include "PGUISliderBar.h"
#include "PGUIListItem.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIListBox::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIListBox::ms_oPropertySet;

bool PGUIListBox::ManagesChildren() const
{
    return true;
}

bool PGUIListBox::AcceptsFocus() const
{
    return true;
}

// The list box takes the focus itself, whatever the focus came from
Toshi::TGUIWidget* PGUIListBox::AllowsFocus(Toshi::TGUIWidget* from)
{
    return this;
}

Toshi::TNodeList<PGUIItemData>* PGUIListBox::GetItemData()
{
    return &m_oItemData;
}

PGUIItemData* PGUIListBox::GetSelectedItem()
{
    return m_pSelectedItem;
}

PGUIListBox::SelectionMode PGUIListBox::GetSelectionMode() const
{
    return m_eSelectionMode;
}

bool PGUIListBox::GetHoverSelectMode() const
{
    return m_bHoverSelect;
}

Toshi::TGUIStyle* PGUIListBox::GetScrollBarStyle() const
{
    return m_pScrollBarStyle;
}

Toshi::TGUIStyle* PGUIListBox::GetListItemStyle() const
{
    return m_pListItemStyle;
}

PGUIItemData* PGUIListBox::GetBlankItem()
{
    return m_pBlankItem;
}

void PGUIListBox::SetBlankItem(PGUIItemData* item)
{
    m_pBlankItem = item;
}

void PGUIListBox::SetSelectionMode(SelectionMode mode)
{
    m_eSelectionMode = mode;
}

void PGUIListBox::SetHoverSelectMode(bool hover)
{
    m_bHoverSelect = hover;
}

void PGUIListBox::Set_scrollbarpos_property(const PPropertyValue& value)
{
    SetScrollBarPosition(value.GetInteger());
}

void PGUIListBox::SetScrollBarPosition(int position)
{
    if (position == 0 || position == 1)
    {
        m_eScrollBarPosition = (Placement)position;
    }
}

void PGUIListBox::SetOrientation(int mode)
{
    if (mode == 0 || mode == 1 || mode == 2)
    {
        m_eArrangeMode = (ArrangeMode)mode;
    }

    PGUISliderBar* scrollBar = GetScrollBar();
    if (scrollBar != 0)
    {
        scrollBar->SetOrientation(mode);
    }
}

PGUISliderBar* PGUIListBox::GetScrollBar()
{
    if (m_bHasScrollBar)
    {
        // the scroll bar is the first child
        return (PGUISliderBar*)GetChildren().Head();
    }

    return 0;
}

bool PGUIListBox::IsScrollableBackward() const
{
    return IsState(STATE_SCROLLABLE_BACKWARD);
}

bool PGUIListBox::IsScrollableForward() const
{
    return IsState(STATE_SCROLLABLE_FORWARD);
}

void PGUIListBox::SetFirstItem(PGUIItemData* item)
{
    m_pFirstItem = item;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIListBox::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIListBox::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIListBox::IsItemVisible(PGUIItemData* item)
{
    return FindItemWidget(item) != 0;
}

void PGUIListBox::EnsureVisible(PGUIItemData* item)
{
    EnsureVisibleImpl(item);
    RefreshItemList();
}

void PGUIListBox::SelectItem(PGUIItemData* item)
{
    SelectItemImpl(item);
    RefreshItemList();
}

void PGUIListBox::RemoveItem(PGUIItemData* item)
{
    RemoveItemImpl(item);
    RefreshItemList();
}

void PGUIListBox::AddItem(PGUIItemData* item)
{
    AddItemImpl(item);
}

Toshi::TGUIWidgetInfo* PGUIListBox::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIListBox::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

void PGUIListBox::RemoveAllItems()
{
    RemoveAllItemsImpl();
}

void PGUIListBox::SetScrollableBackward(bool value)
{
    SetState(STATE_SCROLLABLE_BACKWARD, value);
}

void PGUIListBox::SetScrollableForward(bool value)
{
    SetState(STATE_SCROLLABLE_FORWARD, value);
}

void PGUIListBox::SetListItemStyle(Toshi::TGUIStyle* style)
{
    m_pListItemStyle = style;
    DeleteItemList();
}

PPropertyValue PGUIListBox::Get_scrollbarpos_property() const
{
    return PPropertyValue((int)m_eScrollBarPosition);
}

PPropertyValue PGUIListBox::Get_orientation_property() const
{
    return PPropertyValue((int)m_eArrangeMode);
}

void PGUIListBox::Set_orientation_property(const PPropertyValue& value)
{
    SetOrientation(value.GetInteger());
}

bool PGUIListBox::Val_selectionmode_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT);
}

PPropertyValue PGUIListBox::Get_selectionmode_property() const
{
    return PPropertyValue((int)m_eSelectionMode);
}

void PGUIListBox::Set_selectionmode_property(const PPropertyValue& value)
{
    m_eSelectionMode = (SelectionMode)value.GetInteger();
}

bool PGUIListBox::Serialise(PProperties* properties)
{
    if (!TGUIWidget::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIListBox::OnPointerMove(int x, int y)
{
    if (m_bHoverSelect) {
        SelectItemAtPoint(x, y);
    }
    return false;
}

void PGUIListBox::SelectItemAtPoint(int x, int y)
{
    Toshi::TGUIWidget* widget = GetChildAtPoint(x, y, 4, 4);
    PGUIItemData* item = widget ? FindWidgetItem(static_cast<PGUIListItem*>(widget)) : 0;
    SelectItemImpl(item);
    RefreshItemList();
}

bool PGUIListBox::Val_orientation_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (value.GetInteger() == 0 || value.GetInteger() == 1) {
        return true;
    }
    if (value.GetInteger() == 2) {
        return true;
    }
    return false;
}

bool PGUIListBox::Val_scrollbarpos_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (value.GetInteger() == 0) {
        return true;
    }
    if (value.GetInteger() == 1) {
        return true;
    }
    return false;
}

void PGUIListBox::NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to)
{
    if (m_unkC0) {
        m_unkC0->SetState(2, false);
    }
    TGUIWidget::NotifyFocusLost(from, to);
}

bool PGUIListBox::OnButtonRepeat(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    if (TGUIWidget::OnButtonRepeat(event, doodad) == true) {
        return true;
    }
    if (DoButtonEvent(event, doodad)) {
        return true;
    }
    return false;
}

// The list item widgets are the children of the list box, starting at the first visible one
PGUIListItem* PGUIListBox::GetFirstItemWidget()
{
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widget(GetChildren().Begin());
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widgetEnd(GetChildren().End());
    int i = 0;
    while (i < m_unkE4) {
        if (widget == widgetEnd) {
            return 0;
        }
        i++;
        ++widget;
    }
    return static_cast<PGUIListItem*>(widget.Get());
}

// Deletes the item widgets that RefreshItemList created
void PGUIListBox::DeleteItemList()
{
    if (m_unkD4 == 0) {
        return;
    }
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widget(GetFirstItemWidget());
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widgetEnd(GetChildren().End());
    while (widget != widgetEnd) {
        Toshi::TGUIWidget* itemWidget = widget.Get();
        ++widget;
        RemoveWidget(itemWidget);
        delete itemWidget;
    }
    m_unkD4 = 0;
}

PGUIListItem* PGUIListBox::FindItemWidget(PGUIItemData* target)
{
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widget(GetFirstItemWidget());
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widgetEnd(GetChildren().End());
    Toshi::TNodeList<PGUIItemData>::Iterator item(m_pFirstItem);
    Toshi::TNodeList<PGUIItemData>::Iterator itemEnd(m_oItemData.End());
    for (; widget != widgetEnd && item != itemEnd; ++widget, ++item) {
        if (item.Get() == target) {
            return static_cast<PGUIListItem*>(widget.Get());
        }
    }
    return 0;
}

PGUIItemData* PGUIListBox::FindWidgetItem(PGUIListItem* target)
{
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widget(GetFirstItemWidget());
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widgetEnd(GetChildren().End());
    Toshi::TNodeList<PGUIItemData>::Iterator item(m_pFirstItem);
    Toshi::TNodeList<PGUIItemData>::Iterator itemEnd(m_oItemData.End());
    for (; widget != widgetEnd && item != itemEnd; ++widget, ++item) {
        if (widget.Get() == target) {
            return item.Get();
        }
    }
    return 0;
}

void PGUIListBox::AddItemImpl(PGUIItemData* item)
{
    m_oItemData.InsertTail(item);
    if (m_pFirstItem == 0) {
        m_pFirstItem = item;
    }
    if (m_pSelectedItem == 0) {
        SelectItemImpl(item);
    }
}

void PGUIListBox::RemoveAllItemsImpl()
{
    m_pSelectedItem = 0;
    m_pFirstItem = 0;
    while (!m_oItemData.IsEmpty()) {
        PGUIItemData* item = m_oItemData.Head();
        m_oItemData.Remove(item);
        delete item;
    }
}

// Sizes the list box so that rows x columns items fit inside its interior
void PGUIListBox::SizeToFit(int rows, int columns)
{
    RefreshItemList();
    int left;
    int top;
    int right;
    int bottom;
    GetComponentInteriorBBox(1, left, top, right, bottom);
    SetFixedSize(columns * m_unkF0 - right + GetWidth(), rows * m_unkF4 - bottom + GetHeight());
}

bool PGUIListBox::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    if (!m_oItemData.IsEmpty()) {
        SelectItemImpl(m_oItemData.Head());
        RefreshItemList();
    }
    return true;
}

// Scrolls the list so that the item is visible: an item above the first one becomes the first item, an item
// below the visible ones becomes the last visible item
void PGUIListBox::EnsureVisibleImpl(PGUIItemData* item)
{
    if (FindItemWidget(item)) {
        return;
    }
    Toshi::TNodeList<PGUIItemData>::Iterator it(item);
    Toshi::TNodeList<PGUIItemData>::Iterator end(m_oItemData.End());
    for (; it != end; ++it) {
        if (it.Get() == m_pFirstItem) {
            m_pFirstItem = item;
            return;
        }
    }
    m_pFirstItem = item;
    for (int i = 0; i < m_unkD4 - 1; i++) {
        m_pFirstItem = m_pFirstItem->Prev();
    }
}

PGUIListBox* PGUIListBox::Clone() const
{
    return new PGUIListBox(*this);
}
