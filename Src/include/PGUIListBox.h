// PGUIListBox (PGUICore.dll): a widget that shows a scrollable list of PGUIListItem entries built from a
// list of PGUIItemData. Only the accessors are written so far; the bytes between the known members are unknown.
#ifndef PGUILISTBOX_H
#define PGUILISTBOX_H
#include "PGUIAPI.h"
#include "TGUIWidget.h"
#include "TNodeList.h"
#include "PGUIItemData.h"



namespace Toshi {
class TGUIStyle;
}
class PGUIListItem;
class PGUISliderBar;
class PPropertyValue;

class PGUI_API PGUIListBox : public Toshi::TGUIWidget
{
public:
    virtual PGUIListBox* Clone() const;                                  // slot 13
    bool Val_scrollbarpos_property(const PPropertyValue& value);
    bool Val_orientation_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    // How the items are arranged and how many can be selected; the enumerator values are not known yet
    enum ArrangeMode
    {
    };

    enum SelectionMode
    {
    };

    // Bits of the widget state, added to the ones TGUIWidget defines
    enum
    {
        STATE_SCROLLABLE_BACKWARD = 0x20,
        STATE_SCROLLABLE_FORWARD = 0x40
    };

    virtual bool ManagesChildren() const;                               // slot 14
    virtual bool AcceptsFocus() const;                                  // slot 16
    virtual Toshi::TGUIWidget* AllowsFocus(Toshi::TGUIWidget* from);    // slot 17
    void SelectItemAtPoint(int x, int y);

    Toshi::TNodeList<PGUIItemData>* GetItemData();
    PGUIItemData* GetSelectedItem();
    SelectionMode GetSelectionMode() const;
    bool GetHoverSelectMode() const;
    Toshi::TGUIStyle* GetScrollBarStyle() const;
    Toshi::TGUIStyle* GetListItemStyle() const;
    PGUIItemData* GetBlankItem();
    void SetBlankItem(PGUIItemData* item);
    void SetSelectionMode(SelectionMode mode);
    void SetHoverSelectMode(bool hover);
    void SetScrollBarPosition(int position);
    void SetOrientation(int mode);
    PGUISliderBar* GetScrollBar();

    PPropertyValue Get_scrollbarpos_property() const;
    void Set_scrollbarpos_property(const PPropertyValue& value);
    PPropertyValue Get_orientation_property() const;
    void Set_orientation_property(const PPropertyValue& value);
    bool Val_selectionmode_property(const PPropertyValue& value);
    PPropertyValue Get_selectionmode_property() const;
    void Set_selectionmode_property(const PPropertyValue& value);
    bool IsScrollableBackward() const;
    bool IsScrollableForward() const;
    void SetScrollableBackward(bool value);
    void SetScrollableForward(bool value);
    void SetListItemStyle(Toshi::TGUIStyle* style);
    void SetListItemStyle(const Toshi::TPCString& name);
    void SetScrollBarStyle(Toshi::TGUIStyle* style);
    void SetScrollBarStyle(const Toshi::TPCString& name);
    bool Val_scrollbarstyle_property(const PPropertyValue& value);
    PPropertyValue Get_scrollbarstyle_property() const;
    void Set_scrollbarstyle_property(const PPropertyValue& value);
    bool Val_listitemstyle_property(const PPropertyValue& value);
    PPropertyValue Get_listitemstyle_property() const;
    void Set_listitemstyle_property(const PPropertyValue& value);
    void DeleteItemList();
    bool IsItemVisible(PGUIItemData* item);
    void EnsureVisible(PGUIItemData* item);
    void SelectItem(PGUIItemData* item);
    void RemoveItem(PGUIItemData* item);
    void AddItem(PGUIItemData* item);
    void RemoveAllItems();
    PGUIListItem* GetFirstItemWidget();
    void SizeToFit(int rows, int columns);
    void RefreshItemList();
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();

protected:
    PGUIListBox(const PGUIListBox& other);
    virtual void NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to);       // slot 21
    virtual bool OnButtonRepeat(Toshi::TInputInterface::InputEvent* event, int doodad);  // slot 25
    virtual bool OnPointerMove(int x, int y);                           // slot 29
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

    bool DoButtonEvent(Toshi::TInputInterface::InputEvent* event, int doodad);
    void SetFirstItem(PGUIItemData* item);
    PGUIListItem* FindItemWidget(PGUIItemData* item);
    PGUIItemData* FindWidgetItem(PGUIListItem* widget);
    void AddItemImpl(PGUIItemData* item);
    void RemoveAllItemsImpl();
    void RemoveItemImpl(PGUIItemData* item);
    void SelectItemImpl(PGUIItemData* item);
    void EnsureVisibleImpl(PGUIItemData* item);

private:
    static Toshi::TGUIWidgetInfo* ms_widget_info;
    unsigned char m_unk8C[0x18];                    // +0x8C
    ArrangeMode m_eArrangeMode;                     // +0xA4
    Placement m_eScrollBarPosition;                 // +0xA8
    Toshi::TGUIStyle* m_pScrollBarStyle;            // +0xAC
    Toshi::TGUIStyle* m_pListItemStyle;             // +0xB0
    PGUIItemData* m_pBlankItem;                     // +0xB4
    PGUIItemData* m_pFirstItem;                     // +0xB8
    PGUIItemData* m_pSelectedItem;                  // +0xBC
    Toshi::TGUIWidget* m_unkC0;                     // +0xC0
    Toshi::TNodeList<PGUIItemData> m_oItemData;     // +0xC4
    int m_unkD4;                                    // +0xD4
    unsigned char m_unkD8[0xC];                     // +0xD8
    int m_unkE4;                                    // +0xE4
    bool m_bHasScrollBar;                           // +0xE8
    bool m_bHoverSelect;                            // +0xE9
    unsigned char m_unkEA[2];                       // +0xEA
    SelectionMode m_eSelectionMode;                 // +0xEC
    int m_unkF0;                                    // +0xF0
    int m_unkF4;                                    // +0xF4

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
