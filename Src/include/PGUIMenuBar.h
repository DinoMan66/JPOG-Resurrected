// PGUIMenuBar (PGUICore.dll): a panel that shows the top level of a PGUIMenuTree as a bar of buttons.
// Only the accessors are written so far.
#ifndef PGUIMENUBAR_H
#define PGUIMENUBAR_H
#include "PGUIAPI.h"
#include "PGUIPanel.h"
#include "PGUIItemData.h"

class PGUIMenuTree;
class PGUIMenuTreeItem;

class PGUI_API PGUIMenuBar : public PGUIPanel
{
public:
    virtual PGUIMenuBar* Clone() const;                                  // slot 13
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    Toshi::TGUIWidget* GetSelectedButton();
    PGUIMenuTreeItem* GetRootItem() const;
    PGUIMenuTree* GetMenuTree() const;
    void SetMenuTree(PGUIMenuTree* tree);
    void SetRootItem(PGUIMenuTreeItem* item);
    void UpdateMenu();
    virtual PGUIMenuTreeItem* FindItemData(Toshi::TGUIWidget* widget);

protected:
    PGUIMenuBar(const PGUIMenuBar& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

    void SetSelectedButton(Toshi::TGUIWidget* button);
    void UpdateSelection();
    void DiscardButton(Toshi::TGUIWidget* button);

private:
    PGUIMenuTree* m_pMenuTree;                  // +0x8C
    PGUIMenuTreeItem* m_pRootItem;              // +0x90
    PGUIMenuTreeItem* m_pSelectedItem;          // +0x94
    Toshi::TGUIWidget* m_pSelectedButton;       // +0x98
    Toshi::TNodeList<Toshi::TGUIWidget> m_oDiscardedButtons;    // +0x9C buttons kept for reuse
    unsigned char m_unkAC[0x10];                // +0xAC second list (owner pointer, callback, sentinel)

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
