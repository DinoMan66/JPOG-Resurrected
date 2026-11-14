// PGUIMenuBar accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIMenuBar.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIMenuBar::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIMenuBar::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUIMenuBar::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIMenuBar::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

Toshi::TGUIWidget* PGUIMenuBar::GetSelectedButton()
{
    return m_pSelectedButton;
}

PGUIMenuTreeItem* PGUIMenuBar::GetRootItem() const
{
    return m_pRootItem;
}

PGUIMenuTree* PGUIMenuBar::GetMenuTree() const
{
    return m_pMenuTree;
}

void PGUIMenuBar::SetMenuTree(PGUIMenuTree* tree)
{
    m_pMenuTree = tree;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIMenuBar::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIMenuBar::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIMenuBar::Serialise(PProperties* properties)
{
    if (!PGUIPanel::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIMenuBar::Deserialise(const PProperties* properties)
{
    if (!PGUIPanel::Deserialise(properties)) {
        return false;
    }
    return true;
}

void PGUIMenuBar::SetRootItem(PGUIMenuTreeItem* item)
{
    m_pRootItem = item;
    m_pSelectedItem = 0;
    UpdateMenu();
    SetSelectedButton(0);
}

void PGUIMenuBar::SetSelectedButton(Toshi::TGUIWidget* button)
{
    if (button) {
        UpdateSelection();
    }
}

// The buttons of the bar are the children of the bar, in the same order as the shown items
PGUIMenuTreeItem* PGUIMenuBar::FindItemData(Toshi::TGUIWidget* widget)
{
    Toshi::TNodeList<PGUIItemData>::Iterator it(m_pRootItem->GetChildren().Begin());
    Toshi::TNodeList<PGUIItemData>::Iterator end(m_pRootItem->GetChildren().End());
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator button(GetChildren().Begin());
    for (; it != end; ++it) {
        if (it->GetState() & 4) {
            Toshi::TGUIWidget* current = button.Get();
            ++button;
            if (current == widget) {
                return static_cast<PGUIMenuTreeItem*>(it.Get());
            }
        }
    }
    return 0;
}

void PGUIMenuBar::DiscardButton(Toshi::TGUIWidget* button)
{
    if (button->GetParentWidget()) {
        button->GetParentWidget()->RemoveWidget(button);
    }
    m_oDiscardedButtons.InsertTail(button);
}

PGUIMenuBar* PGUIMenuBar::Clone() const
{
    return new PGUIMenuBar(*this);
}
