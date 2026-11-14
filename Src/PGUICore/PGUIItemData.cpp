// PGUIItemData, PGUIMenuTreeItem and PGUIMenuTreeItemStyle accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIItemData.h"
#include "PPropertyValue.h"
#include "TGUIStyle.h"

// An item can be selected when bit 0 and bit 2 of its state are both set
bool PGUIItemData::CanSelect() const
{
    return (m_uState & 5) == 5;
}

void PGUIItemData::SetState(unsigned int mask, bool set)
{
    if (set) {
        m_uState |= mask;
    } else {
        m_uState &= ~mask;
    }
}

void PGUIItemData::RemoveState(unsigned int mask)
{
    m_uState &= ~mask;
}

void PGUIItemData::AddState(unsigned int mask)
{
    m_uState |= mask;
}

void PGUIItemData::SetState(unsigned int state)
{
    m_uState = state;
}

PPropertyValue* PGUIItemData::GetParameterValues()
{
    return m_pParameterValues;
}

PGUIMenuTreeItemStyle* PGUIMenuTreeItem::GetStyle() const
{
    return m_pStyle;
}

PGUIMenuTreeItem* PGUIMenuTreeItem::GetParent() const
{
    return m_pParent;
}

void PGUIMenuTreeItem::SetStyle(PGUIMenuTreeItemStyle* style)
{
    m_pStyle = style;
}

void PGUIMenuTreeItem::SetParent(PGUIMenuTreeItem* parent)
{
    m_pParent = parent;
}

Toshi::TGUIWidget* PGUIMenuTreeItemStyle::GetNextMenuTemplate() const
{
    return m_pNextMenuTemplate;
}

Toshi::TGUIWidget* PGUIMenuTreeItemStyle::GetCurrentMenuTemplate() const
{
    return m_pCurrentMenuTemplate;
}

Toshi::TGUIWidget* PGUIMenuTreeItemStyle::GetPreviousMenuTemplate() const
{
    return m_pPreviousMenuTemplate;
}

Toshi::TGUIStyle* PGUIMenuTreeItemStyle::GetNextItemStyle() const
{
    return m_pNextItemStyle;
}

Toshi::TGUIStyle* PGUIMenuTreeItemStyle::GetCurrentItemSelectedStyle() const
{
    return m_pCurrentItemSelectedStyle;
}

Toshi::TGUIStyle* PGUIMenuTreeItemStyle::GetCurrentItemStyle() const
{
    return m_pCurrentItemStyle;
}

int PGUIMenuTreeItemStyle::GetParameterCount() const
{
    return m_pCurrentItemStyle->GetParameterCount();
}

bool PGUIMenuTreeItem::IsParentOf(PGUIMenuTreeItem* item) const
{
    // walks up from the item through its ancestors
    for (PGUIMenuTreeItem* ancestor = item->m_pParent; ancestor != 0; ancestor = ancestor->m_pParent)
    {
        if (ancestor == this)
        {
            return true;
        }
    }

    return false;
}

PGUIMenuTreeItemStyle::PGUIMenuTreeItemStyle(Toshi::TGUIStyle* currentItemStyle, Toshi::TGUIStyle* currentItemSelectedStyle, Toshi::TGUIStyle* nextItemStyle,
    Toshi::TGUIWidget* previousMenuTemplate, Toshi::TGUIWidget* currentMenuTemplate, Toshi::TGUIWidget* nextMenuTemplate)
{
    m_pCurrentItemStyle = currentItemStyle;
    m_pCurrentItemSelectedStyle = currentItemSelectedStyle;
    m_pNextItemStyle = nextItemStyle;
    m_pPreviousMenuTemplate = previousMenuTemplate;
    m_pCurrentMenuTemplate = currentMenuTemplate;
    m_pNextMenuTemplate = nextMenuTemplate;
}

PGUIMenuTreeItemStyle::~PGUIMenuTreeItemStyle()
{
}

Toshi::TGUIStyle* PGUIMenuTreeItemStyle::GetItemStyle(DisplayLevel level) const
{
    switch (level) {
    case 0:
    case 1:
        return m_pCurrentItemStyle;
    case 2:
        return m_pNextItemStyle;
    }
    return 0;
}

Toshi::TGUIStyle* PGUIMenuTreeItemStyle::GetSelectedItemStyle(DisplayLevel level) const
{
    if (level == 0 || level == 1) {
        return m_pCurrentItemSelectedStyle;
    }
    return 0;
}

void PGUIMenuTreeItem::AddItem(PGUIMenuTreeItem* item)
{
    item->m_pParent = this;
    m_oChildren.InsertTail(item);
}

void PGUIMenuTreeItem::RemoveItem(PGUIMenuTreeItem* item)
{
    item->m_pParent = 0;
    m_oChildren.Remove(item);
}

void PGUIMenuTreeItem::DeleteItem(PGUIMenuTreeItem* item)
{
    item->m_pParent = 0;
    m_oChildren.Remove(item);
    delete item;
}

PGUIMenuTreeItem* PGUIMenuTreeItem::ChooseChildItem()
{
    if (m_oChildren.IsEmpty()) {
        return 0;
    }
    PGUIMenuTreeItem* item = static_cast<PGUIMenuTreeItem*>(m_oChildren.Head());
    if ((item->GetState() & 5) == 5) {
        return item;
    }
    return item->ChooseNextItem(1);
}

PGUIMenuTreeItem* PGUIMenuTreeItem::FindChildItem(int index)
{
    Toshi::TNodeList<PGUIItemData>::Iterator it(m_oChildren.Begin());
    Toshi::TNodeList<PGUIItemData>::Iterator end(m_oChildren.End());
    while (index > 0 && it != end) {
        ++it;
        index--;
    }
    if (it != end) {
        return static_cast<PGUIMenuTreeItem*>(it.Get());
    }
    return 0;
}

// Steps to the next (direction > 0) or previous (direction < 0) sibling that can be chosen, wrapping around
PGUIMenuTreeItem* PGUIMenuTreeItem::ChooseNextItem(int direction)
{
    PGUIMenuTreeItem* item = this;
    do {
        if (direction > 0) {
            if (item == m_pParent->m_oChildren.Tail()) {
                item = static_cast<PGUIMenuTreeItem*>(m_pParent->m_oChildren.Head());
            } else {
                item = static_cast<PGUIMenuTreeItem*>(item->Next());
            }
        } else if (direction < 0) {
            if (item == m_pParent->m_oChildren.Head()) {
                item = static_cast<PGUIMenuTreeItem*>(m_pParent->m_oChildren.Tail());
            } else {
                item = static_cast<PGUIMenuTreeItem*>(item->Prev());
            }
        }
        if ((item->GetState() & 5) == 5) {
            return item;
        }
    } while (item != this);
    return 0;
}

PPropertyValue* PGUIPropertyValueFactory::AllocateValueArray(int count)
{
    return new PPropertyValue[count];
}
