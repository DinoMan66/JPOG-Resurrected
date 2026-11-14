// PGUITableBox accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUITableBox.h"
#include "TMemory.h"
#include "PPropertyValue.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUITableBox::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUITableBox::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUITableBox::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUITableBox::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUITableBox::AcceptsFocus() const
{
    return true;
}

Toshi::TNodeList<PGUIRowData>* PGUITableBox::GetItemData()
{
    return &m_oRows;
}

PGUIRowData* PGUITableBox::GetSelectedItem()
{
    return m_pSelectedRow;
}

PGUITableBox::SelectionMode PGUITableBox::GetSelectionMode() const
{
    return m_eSelectionMode;
}

bool PGUITableBox::GetHoverSelectMode() const
{
    return m_bHoverSelect;
}

int PGUITableBox::GetColumnCount() const
{
    return m_iColumnCount;
}

void PGUITableBox::SetSelectionMode(SelectionMode mode)
{
    m_eSelectionMode = mode;
}

void PGUITableBox::SetHoverSelectMode(bool hover)
{
    m_bHoverSelect = hover;
}

bool PGUITableBox::IsScrollableBackward() const
{
    return IsState(STATE_SCROLLABLE_BACKWARD);
}

void PGUITableBox::SetFirstItem(PGUIRowData* row)
{
    m_pFirstRow = row;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUITableBox::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUITableBox::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUITableBox::Val_selectionmode_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT);
}

PPropertyValue PGUITableBox::Get_selectionmode_property() const
{
    return PPropertyValue((int)m_eSelectionMode);
}

void PGUITableBox::Set_selectionmode_property(const PPropertyValue& value)
{
    m_eSelectionMode = (SelectionMode)value.GetInteger();
}

bool PGUITableBox::Val_columns_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT);
}

PPropertyValue PGUITableBox::Get_columns_property() const
{
    return PPropertyValue(m_iColumnCount);
}

void PGUITableBox::Set_columns_property(const PPropertyValue& value)
{
    m_iColumnCount = value.GetInteger();
}

bool PGUITableBox::Serialise(PProperties* properties)
{
    if (!PGUIPanel::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUITableBox::Deserialise(const PProperties* properties)
{
    if (!PGUIPanel::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUITableBox::IsScrollableForward() const
{
    return IsState(STATE_SCROLLABLE_FORWARD);
}

void PGUITableBox::SetScrollableBackward(bool value)
{
    SetState(STATE_SCROLLABLE_BACKWARD, value);
}

void PGUITableBox::SetScrollableForward(bool value)
{
    SetState(STATE_SCROLLABLE_FORWARD, value);
}

void PGUITableBox::EnsureVisible(PGUIRowData* row)
{
    EnsureVisibleImpl(row);
    RefreshItemList();
}

void PGUITableBox::SelectItem(PGUIRowData* row)
{
    SelectItemImpl(row);
    RefreshItemList();
}

void PGUITableBox::RemoveAllItems()
{
    RemoveAllItemsImpl();
    RefreshItemList();
}

void PGUITableBox::RemoveItem(PGUIRowData* row)
{
    RemoveItemImpl(row);
    RefreshItemList();
}

void PGUITableBox::AddItem(PGUIRowData* row)
{
    AddItemImpl(row);
}

void PGUITableBox::NotifyFocusGained(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to)
{
    TGUIWidget::NotifyFocusGained(from, to);
}

void PGUITableBox::NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to)
{
    TGUIWidget::NotifyFocusLost(from, to);
}

bool PGUITableBox::OnPointerMove(int x, int y)
{
    if (m_bHoverSelect) {
        SelectItemAtPoint(x, y);
    }
    return false;
}

bool PGUITableBox::OnButtonRepeat(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    if (TGUIWidget::OnButtonRepeat(event, doodad) == true) {
        return true;
    }
    if (DoButtonEvent(event, doodad)) {
        return true;
    }
    return false;
}

void PGUITableBox::AddItemImpl(PGUIRowData* row)
{
    m_oRows.InsertTail(row);
    if (m_pFirstRow == 0) {
        m_pFirstRow = row;
    }
    if (m_pSelectedRow == 0) {
        SelectItemImpl(row);
    }
}

void PGUITableBox::RemoveAllItemsImpl()
{
    m_pFirstRow = 0;
    m_unkC4 = 0;
    m_pSelectedRow = 0;
    while (!m_oRows.IsEmpty()) {
        PGUIRowData* row = m_oRows.Head();
        m_oRows.Remove(row);
        delete row;
    }
    SelectItemImpl(0);
}

// Remembers the width of every column widget
void PGUITableBox::UpdateWidgetWidths()
{
    if (m_iColumnCount != 0 && m_ppStampWidgets != 0 && m_piColumnWidths != 0) {
        Toshi::TNodeList<Toshi::TGUIWidget>::Iterator widget(GetChildren().Begin());
        for (int i = 0; i < m_iColumnCount; i++) {
            m_piColumnWidths[i] = widget->GetWidth();
            ++widget;
        }
    }
}

bool PGUITableBox::IsItemVisible(PGUIRowData* row)
{
    if (m_pFirstRow == 0) {
        return false;
    }
    Toshi::TNodeList<PGUIRowData>::Iterator it(m_pFirstRow);
    Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
    int i = 0;
    for (; it != end && i < m_unkCC; ++it, i++) {
        if (it.Get() == row) {
            return true;
        }
    }
    return false;
}

// Scrolls the table so that the row is visible: a row above the first one becomes the first row, a row below
// the visible ones becomes the last visible row
void PGUITableBox::EnsureVisibleImpl(PGUIRowData* row)
{
    if (IsItemVisible(row)) {
        return;
    }
    Toshi::TNodeList<PGUIRowData>::Iterator it(row);
    Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
    for (; it != end; ++it) {
        if (it.Get() == m_pFirstRow) {
            m_pFirstRow = row;
            return;
        }
    }
    m_pFirstRow = row;
    for (int i = 0; i < m_unkCC - 1; i++) {
        m_pFirstRow = m_pFirstRow->Prev();
    }
}

// Creates the arrays that hold one stamp widget and one width per column
void PGUITableBox::Initialise()
{
    if (m_ppStampWidgets == 0) {
        m_ppStampWidgets = (Toshi::TGUIWidget**)tmalloc(m_iColumnCount * 4, 0, -1);
        m_piColumnWidths = (int*)tmalloc(m_iColumnCount * 4, 0, -1);
        RemoveStampWidgets();
    }
}

void PGUITableBox::InsertStampWidgets()
{
    if (m_ppStampWidgets != 0) {
        for (int i = 0; i < m_iColumnCount; i++) {
            AddWidget(m_ppStampWidgets[i], false);
        }
    }
}

PGUITableBox* PGUITableBox::Clone() const
{
    return new PGUITableBox(*this);
}
