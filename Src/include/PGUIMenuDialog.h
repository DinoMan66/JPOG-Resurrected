// PGUIMenuDialog (PGUICore.dll): a dialog that shows a PGUIMenuTree. It remembers the menu tree, the root
// item that is shown and the button that is selected. Only the accessors are written so far.
#ifndef PGUIMENUDIALOG_H
#define PGUIMENUDIALOG_H
#include "PGUIAPI.h"
#include "PGUIDialog.h"
#include "PGUIItemData.h"

class PGUIMenuTree;

class PGUI_API PGUIMenuDialog : public PGUIDialog
{
public:
    virtual PGUIMenuDialog* Clone() const;                                  // slot 13
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual bool AcceptsFocus() const;                                  // slot 16
    virtual void NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to);       // slot 21
    virtual void NotifyFocusGained(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to);     // slot 22
    virtual bool OnButtonPress(Toshi::TInputInterface::InputEvent* event, int doodad);      // slot 24
    virtual bool OnButtonRepeat(Toshi::TInputInterface::InputEvent* event, int doodad);     // slot 25
    virtual bool OnButtonRelease(Toshi::TInputInterface::InputEvent* event, int doodad);    // slot 26
    virtual void Pack();                                                // slot 33
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();

    PGUIMenuTreeItem* GetRootItem() const;
    Toshi::TGUIWidget* GetSelectedButton();
    void SetDisplayMode(PGUIMenuTreeItemStyle::DisplayLevel level);
    void SetMenuTree(PGUIMenuTree* tree);
    PGUIMenuTreeItem* GetItemAtIndex(int index) const;
    virtual PGUIMenuTreeItem* FindItemData(Toshi::TGUIWidget* widget);

protected:
    PGUIMenuDialog(const PGUIMenuDialog& other);

    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    void DiscardButton(Toshi::TGUIWidget* button);
    static Toshi::TGUIWidgetInfo* ms_widget_info;
    PGUIMenuTree* m_pMenuTree;                              // +0xB0
    PGUIMenuTreeItem* m_pRootItem;                          // +0xB4
    unsigned char m_unkB8[4];                               // +0xB8
    Toshi::TGUIWidget* m_pSelectedButton;                   // +0xBC
    Toshi::TGUIWidget* m_pMenuPanel;                        // +0xC0
    unsigned char m_unkC4[0xC];                             // +0xC4
    PGUIMenuTreeItemStyle::DisplayLevel m_eDisplayLevel;    // +0xD0
    Toshi::TNodeList<Toshi::TGUIWidget> m_oDiscardedButtons;    // +0xD4 buttons kept for reuse
    unsigned char m_unkE4[0x10];                            // +0xE4 second list (owner pointer, callback, sentinel)

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
