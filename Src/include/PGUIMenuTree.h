// PGUIMenuTree (PGUICore.dll): owns a tree of PGUIMenuTreeItem and shows the current level of it as menu dialogs
// on a screen. Only the plain accessors are written so far; the offset-named members stand in for the
// base class and the dialog bookkeeping that the unwritten functions use.
#ifndef PGUIMENUTREE_H
#define PGUIMENUTREE_H
#include "PGUIAPI.h"
#include "TGUIDeserialisable.h"
#include "TNodeList.h"

class PGUIMenuDialog;
class PGUIMenuTreeItem;

namespace Toshi {
class TGUIScreen;
class TGUIWidget;
}

class PGUI_API PGUIMenuTree : public Toshi::TGUIDeserialisable
{
public:
    virtual bool Deserialise(const PProperties* properties);            // slot 3
    virtual bool Serialise(PProperties* properties);                    // slot 4
    virtual void SetInterface(Toshi::TGUIInterface* gui);               // slot 9
    virtual Toshi::TGUIInterface* GetInterface() const;                 // slot 10

    PGUIMenuTreeItem* GetSelectedItem() const;
    PGUIMenuTreeItem* GetRootItem();
    bool IsInvoked();
    PGUIMenuDialog* GetCurrentMenu();
    Toshi::TGUIScreen* GetScreen() const;

    int GetScreenMarginLeft() const;
    int GetScreenMarginRight() const;
    int GetScreenMarginTop() const;
    int GetScreenMarginBottom() const;

    void SetScreenMarginLeft(int margin);
    void SetScreenMarginRight(int margin);
    void SetScreenMarginTop(int margin);
    void SetScreenMarginBottom(int margin);
    void SetScreenMargins(int left, int right, int top, int bottom);
    void SetScreen(Toshi::TGUIScreen* screen);
    void ScrollMenu(int direction);
    void UpdateMenu(PGUIMenuTreeItem* item);
    void PropagateState(unsigned int mask, unsigned int value, PGUIMenuTreeItem* from, PGUIMenuTreeItem* to);
    bool InvokeMenu(int index, int arg1, int arg2);
    bool InvokeMenu(PGUIMenuTreeItem* item, int arg1, int arg2);

private:
    void DiscardDialog(PGUIMenuDialog* dialog);

protected:
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

    void AddMenus();
    void RemoveMenus();

private:
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;

    unsigned char m_unk04[4];               // +0x04
    Toshi::TGUIInterface* m_pInterface;     // +0x08
    Toshi::TGUIScreen* m_pScreen;           // +0x0C
    PGUIMenuTreeItem* m_pRootItem;          // +0x10
    unsigned char m_unk14[8];               // +0x14
    PGUIMenuTreeItem* m_pSelectedItem;      // +0x1C
    unsigned char m_unk20[4];               // +0x20
    int m_iMenuCount;                       // +0x24 menus on the dialog stack
    unsigned char m_unk28[4];               // +0x28
    PGUIMenuDialog** m_ppMenus;             // +0x2C dialog stack
    unsigned char m_unk30[0x10];            // +0x30
    Toshi::TNodeList<Toshi::TGUIWidget> m_oDiscardedDialogs;    // +0x40 dialogs kept for reuse
    unsigned char m_unk50[4];               // +0x50
    int m_iMarginLeft;                      // +0x54
    int m_iMarginRight;                     // +0x58
    int m_iMarginTop;                       // +0x5C
    int m_iMarginBottom;                    // +0x60
    bool m_bUnk64;                          // +0x64
    bool m_bInvoked;                        // +0x65
};

#endif
