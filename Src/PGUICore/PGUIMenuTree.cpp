// PGUIMenuTree accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIMenuTree.h"
#include "PGUIItemData.h"
#include "PGUIMenuDialog.h"
#include "TGUIScreen.h"

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIMenuTree::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIMenuTree::ms_oPropertySet;

Toshi::TGUIInterface* PGUIMenuTree::GetInterface() const
{
    return m_pInterface;
}

void PGUIMenuTree::SetInterface(Toshi::TGUIInterface* gui)
{
    m_pInterface = gui;
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIMenuTree::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIMenuTree::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIMenuTree::Serialise(PProperties* properties)
{
    if (!TGUIDeserialisable::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIMenuTree::Deserialise(const PProperties* properties)
{
    if (!TGUIDeserialisable::Deserialise(properties)) {
        return false;
    }
    return true;
}

PGUIMenuTreeItem* PGUIMenuTree::GetSelectedItem() const
{
    return m_pSelectedItem;
}

PGUIMenuTreeItem* PGUIMenuTree::GetRootItem()
{
    return m_pRootItem;
}

bool PGUIMenuTree::IsInvoked()
{
    return m_bInvoked;
}

Toshi::TGUIScreen* PGUIMenuTree::GetScreen() const
{
    return m_pScreen;
}

int PGUIMenuTree::GetScreenMarginBottom() const
{
    return m_iMarginBottom;
}

int PGUIMenuTree::GetScreenMarginTop() const
{
    return m_iMarginTop;
}

int PGUIMenuTree::GetScreenMarginRight() const
{
    return m_iMarginRight;
}

int PGUIMenuTree::GetScreenMarginLeft() const
{
    return m_iMarginLeft;
}

void PGUIMenuTree::SetScreenMarginBottom(int margin)
{
    m_iMarginBottom = margin;
}

void PGUIMenuTree::SetScreenMarginTop(int margin)
{
    m_iMarginTop = margin;
}

void PGUIMenuTree::SetScreenMarginRight(int margin)
{
    m_iMarginRight = margin;
}

void PGUIMenuTree::SetScreenMarginLeft(int margin)
{
    m_iMarginLeft = margin;
}

void PGUIMenuTree::SetScreenMargins(int left, int right, int top, int bottom)
{
    m_iMarginLeft = left;
    m_iMarginRight = right;
    m_iMarginTop = top;
    m_iMarginBottom = bottom;
}

PGUIMenuDialog* PGUIMenuTree::GetCurrentMenu()
{
    // the current menu is the second entry from the top of the stack
    if (m_iMenuCount >= 2)
    {
        return m_ppMenus[m_iMenuCount - 2];
    }

    return 0;
}

void PGUIMenuTree::SetScreen(Toshi::TGUIScreen* screen)
{
    if (m_pScreen != screen) {
        if (m_pScreen && m_bInvoked) {
            RemoveMenus();
        }
        m_pScreen = screen;
        if (screen && m_bInvoked) {
            AddMenus();
        }
    }
}

void PGUIMenuTree::RemoveMenus()
{
    for (int i = 0; i < m_iMenuCount; i++) {
        PGUIMenuDialog* menu = m_ppMenus[i];
        if (menu && menu->GetParentWidget()) {
            menu->GetParentWidget()->RemoveWidget(menu);
        }
    }
}

void PGUIMenuTree::AddMenus()
{
    for (int i = 0; i < m_iMenuCount; i++) {
        PGUIMenuDialog* menu = m_ppMenus[i];
        if (menu && menu->GetParentWidget() == 0) {
            m_pScreen->AddWidget(menu, false);
        }
    }
}

void PGUIMenuTree::DiscardDialog(PGUIMenuDialog* dialog)
{
    if (dialog->GetParentWidget()) {
        dialog->GetParentWidget()->RemoveWidget(dialog);
    }
    m_oDiscardedDialogs.InsertTail(dialog);
}

// Invokes the menu of the index-th child of the root item
bool PGUIMenuTree::InvokeMenu(int index, int arg1, int arg2)
{
    Toshi::TNodeList<PGUIItemData>::Iterator it(m_pRootItem->GetChildren().Begin());
    for (int i = 0; i < index; i++) {
        ++it;
    }
    return InvokeMenu(static_cast<PGUIMenuTreeItem*>(it.Get()), arg1, arg2);
}

// Sets the masked state bits on every item from 'from' up the parent chain to (not including) 'to'
void PGUIMenuTree::PropagateState(unsigned int mask, unsigned int value, PGUIMenuTreeItem* from, PGUIMenuTreeItem* to)
{
    for (; from != to; from = from->GetParent()) {
        from->SetState(mask, value);
    }
    UpdateMenu(0);
}
