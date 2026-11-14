// PGUIItemData / PGUIMenuTreeItem / PGUIMenuTreeItemStyle (PGUICore.dll): the data behind the menu widgets.
// An item has a set of state flags (bit 0 and bit 2 together mean it can be selected) and a list of
// parameter values; a menu tree item adds a style, a parent and a list of child items.
// Only the accessors are written so far; the bytes before the known members are unknown.
#ifndef PGUIITEMDATA_H
#define PGUIITEMDATA_H
#include "PGUIAPI.h"
#include "TNodeList.h"
#include "TObject.h"

class PPropertyValue;
class PGUIMenuTreeItemStyle;

namespace Toshi {
class TGUIStyle;
class TGUIWidget;
}

// Base of the item and row data classes: a Toshi object that supplies property values (the exported
// constructors and the three vtable slots are not written yet)
class PGUI_API PGUIPropertyValueFactory : public Toshi::TObject
{
public:
    PPropertyValue* AllocateValueArray(int count);
};

class PGUI_API PGUIItemData : public PGUIPropertyValueFactory, public Toshi::TNodeList<PGUIItemData>::TNode
{
public:
    bool CanSelect() const;
    // Replaces the bits in the mask by the same bits of the value
    void SetState(unsigned int mask, unsigned int value) { m_uState = (m_uState & ~mask) | (value & mask); }
    void SetState(unsigned int mask, bool set);
    void RemoveState(unsigned int mask);
    void AddState(unsigned int mask);
    void SetState(unsigned int state);
    unsigned int GetState() { return m_uState; }
    PPropertyValue* GetParameterValues();

private:
    PPropertyValue* m_pParameterValues;         // +0x10
    unsigned int m_uState;                      // +0x14
};

class PGUI_API PGUIMenuTreeItem : public PGUIItemData
{
public:
    PGUIMenuTreeItemStyle* GetStyle() const;
    PGUIMenuTreeItem* GetParent() const;
    void SetStyle(PGUIMenuTreeItemStyle* style);
    void SetParent(PGUIMenuTreeItem* parent);
    bool IsParentOf(PGUIMenuTreeItem* item) const;
    void AddItem(PGUIMenuTreeItem* item);
    void RemoveItem(PGUIMenuTreeItem* item);
    void DeleteItem(PGUIMenuTreeItem* item);
    PGUIMenuTreeItem* ChooseNextItem(int direction);
    PGUIMenuTreeItem* ChooseChildItem();
    PGUIMenuTreeItem* FindChildItem(int index);
    const Toshi::TNodeList<PGUIItemData>& GetChildren() const { return m_oChildren; }

private:
    PGUIMenuTreeItemStyle* m_pStyle;            // +0x18
    PGUIMenuTreeItem* m_pParent;                // +0x1C
    Toshi::TNodeList<PGUIItemData> m_oChildren; // +0x20
};

class PGUI_API PGUIMenuTreeItemStyle : public Toshi::TNodeList<PGUIMenuTreeItemStyle>::TNode
{
public:
    // Which level of a menu tree is shown; the enumerator values are not known yet
    enum DisplayLevel
    {
    };

    PGUIMenuTreeItemStyle(Toshi::TGUIStyle* currentItemStyle, Toshi::TGUIStyle* currentItemSelectedStyle, Toshi::TGUIStyle* nextItemStyle,
        Toshi::TGUIWidget* previousMenuTemplate, Toshi::TGUIWidget* currentMenuTemplate, Toshi::TGUIWidget* nextMenuTemplate);
    ~PGUIMenuTreeItemStyle();

    Toshi::TGUIWidget* GetNextMenuTemplate() const;
    Toshi::TGUIWidget* GetCurrentMenuTemplate() const;
    Toshi::TGUIWidget* GetPreviousMenuTemplate() const;
    Toshi::TGUIStyle* GetNextItemStyle() const;
    Toshi::TGUIStyle* GetCurrentItemSelectedStyle() const;
    Toshi::TGUIStyle* GetCurrentItemStyle() const;
    int GetParameterCount() const;
    Toshi::TGUIStyle* GetItemStyle(DisplayLevel level) const;
    Toshi::TGUIStyle* GetSelectedItemStyle(DisplayLevel level) const;

private:
    Toshi::TGUIStyle* m_pCurrentItemStyle;              // +0x0C
    Toshi::TGUIStyle* m_pCurrentItemSelectedStyle;      // +0x10
    Toshi::TGUIStyle* m_pNextItemStyle;                 // +0x14
    Toshi::TGUIWidget* m_pPreviousMenuTemplate;         // +0x18
    Toshi::TGUIWidget* m_pCurrentMenuTemplate;          // +0x1C
    Toshi::TGUIWidget* m_pNextMenuTemplate;             // +0x20
};

#endif
