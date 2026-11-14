// PGUIMenuDialog accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIMenuDialog.h"
#include "PGUIMenuTree.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIMenuDialog::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIMenuDialog::ms_oPropertySet;

bool PGUIMenuDialog::AcceptsFocus() const
{
    return true;
}

PGUIMenuTreeItem* PGUIMenuDialog::GetRootItem() const
{
    return m_pRootItem;
}

Toshi::TGUIWidget* PGUIMenuDialog::GetSelectedButton()
{
    return m_pSelectedButton;
}

void PGUIMenuDialog::SetDisplayMode(PGUIMenuTreeItemStyle::DisplayLevel level)
{
    m_eDisplayLevel = level;
}

void PGUIMenuDialog::SetMenuTree(PGUIMenuTree* tree)
{
    m_pMenuTree = tree;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIMenuDialog::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIMenuDialog::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

Toshi::TGUIWidgetInfo* PGUIMenuDialog::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUIMenuDialog::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

void PGUIMenuDialog::NotifyFocusGained(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to)
{
    TGUIWindow::NotifyFocusGained(from, to);
}

void PGUIMenuDialog::NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to)
{
    TGUIWindow::NotifyFocusLost(from, to);
}

bool PGUIMenuDialog::OnButtonRelease(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    return TGUIWidget::OnButtonRelease(event, doodad);
}

bool PGUIMenuDialog::Serialise(PProperties* properties)
{
    if (!PGUIDialog::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIMenuDialog::Deserialise(const PProperties* properties)
{
    if (!PGUIDialog::Deserialise(properties)) {
        return false;
    }
    return true;
}

// Items that have bit 2 of the state set are the ones shown as buttons of the dialog
PGUIMenuTreeItem* PGUIMenuDialog::GetItemAtIndex(int index) const
{
    Toshi::TNodeList<PGUIItemData>::Iterator it(m_pRootItem->GetChildren().Begin());
    Toshi::TNodeList<PGUIItemData>::Iterator end(m_pRootItem->GetChildren().End());
    for (; it != end; ++it) {
        if (it->GetState() & 4) {
            if (index-- == 0) {
                return static_cast<PGUIMenuTreeItem*>(it.Get());
            }
        }
    }
    return 0;
}

// The buttons are the children of the menu panel, in the same order as the shown items
PGUIMenuTreeItem* PGUIMenuDialog::FindItemData(Toshi::TGUIWidget* widget)
{
    Toshi::TNodeList<PGUIItemData>::Iterator it(m_pRootItem->GetChildren().Begin());
    Toshi::TNodeList<PGUIItemData>::Iterator end(m_pRootItem->GetChildren().End());
    Toshi::TNodeList<Toshi::TGUIWidget>::Iterator button(m_pMenuPanel->GetChildren().Begin());
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

void PGUIMenuDialog::Pack()
{
    PGUIDialog::Pack();

    if (GetStyle() != 0)
    {
        SetComponentBBox(0, 0, 0, GetWidth(), GetHeight());
        SetComponentBBox(1, 0, 0, GetWidth(), GetHeight());
    }

    SetValidated(true);
}

// Up and down on the pad scroll the menu tree
bool PGUIMenuDialog::OnButtonRepeat(Toshi::TInputInterface::InputEvent* event, int doodad)
{
    if (TGUIWidget::OnButtonRepeat(event, doodad) == true) {
        return true;
    }
    if (doodad & 0x200) {
        m_pMenuTree->ScrollMenu(-1);
        return true;
    }
    if (doodad & 0x800) {
        m_pMenuTree->ScrollMenu(1);
        return true;
    }
    return false;
}

void PGUIMenuDialog::DiscardButton(Toshi::TGUIWidget* button)
{
    if (button->GetParentWidget()) {
        button->GetParentWidget()->RemoveWidget(button);
    }
    m_oDiscardedButtons.InsertTail(button);
}

PGUIMenuDialog* PGUIMenuDialog::Clone() const
{
    return new PGUIMenuDialog(*this);
}
