// PGUITableBox (PGUICore.dll): a panel that shows rows of PGUIRowData in columns, with a selection.
// Only the accessors are written so far; the bytes between the known members are unknown.
#ifndef PGUITABLEBOX_H
#define PGUITABLEBOX_H
#include "PGUIAPI.h"
#include "PGUIPanel.h"
#include "PGUIRowData.h"

class PPropertyValue;

class PGUI_API PGUITableBox : public PGUIPanel
{
public:
    virtual PGUITableBox* Clone() const;                                  // slot 13
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    // How many rows can be selected; the enumerator values are not known yet
    enum SelectionMode
    {
    };

    // Bit of the widget state, added to the ones TGUIWidget defines
    enum
    {
        STATE_SCROLLABLE_BACKWARD = 0x40,
        STATE_SCROLLABLE_FORWARD = 0x80
    };

    virtual bool AcceptsFocus() const;                                  // slot 16

    Toshi::TNodeList<PGUIRowData>* GetItemData();
    PGUIRowData* GetSelectedItem();
    SelectionMode GetSelectionMode() const;
    bool GetHoverSelectMode() const;
    int GetColumnCount() const;
    void SetSelectionMode(SelectionMode mode);

    bool Val_selectionmode_property(const PPropertyValue& value);
    PPropertyValue Get_selectionmode_property() const;
    void Set_selectionmode_property(const PPropertyValue& value);
    bool Val_columns_property(const PPropertyValue& value);
    PPropertyValue Get_columns_property() const;
    void Set_columns_property(const PPropertyValue& value);
    void SetHoverSelectMode(bool hover);
    bool IsScrollableBackward() const;
    bool IsScrollableForward() const;
    void SetScrollableBackward(bool value);
    void SetScrollableForward(bool value);
    void EnsureVisible(PGUIRowData* row);
    void SelectItem(PGUIRowData* row);
    void RemoveAllItems();
    void RemoveItem(PGUIRowData* row);
    void AddItem(PGUIRowData* row);
    void RefreshItemList();
    bool IsItemVisible(PGUIRowData* row);
    void SelectItemAtPoint(int x, int y);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4

    void Initialise();

protected:
    PGUITableBox(const PGUITableBox& other);
    virtual void NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to);       // slot 21
    virtual void NotifyFocusGained(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to);     // slot 22
    virtual bool OnButtonRepeat(Toshi::TInputInterface::InputEvent* event, int doodad);  // slot 25
    virtual bool OnPointerMove(int x, int y);                                           // slot 29
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

    bool DoButtonEvent(Toshi::TInputInterface::InputEvent* event, int doodad);
    void SetFirstItem(PGUIRowData* row);
    void EnsureVisibleImpl(PGUIRowData* row);
    void SelectItemImpl(PGUIRowData* row);
    void RemoveAllItemsImpl();
    void RemoveItemImpl(PGUIRowData* row);
    void AddItemImpl(PGUIRowData* row);
    void UpdateWidgetWidths();
    void InsertStampWidgets();
    void RemoveStampWidgets();

private:
    unsigned char m_unk8C[0x18];                    // +0x8C
    int m_iColumnCount;                             // +0xA4
    Toshi::TNodeList<PGUIRowData> m_oRows;          // +0xA8
    Toshi::TGUIWidget** m_ppStampWidgets;           // +0xB8 one stamp widget per column; name: export InsertStampWidgets (high)
    int* m_piColumnWidths;                          // +0xBC width of each column widget; name: export UpdateWidgetWidths (high)
    PGUIRowData* m_pFirstRow;                       // +0xC0
    PGUIRowData* m_unkC4;                           // +0xC4
    PGUIRowData* m_pSelectedRow;                    // +0xC8
    int m_unkCC;                                    // +0xCC
    unsigned char m_unkD0[4];                       // +0xD0
    bool m_bHoverSelect;                            // +0xD4
    unsigned char m_unkD5[3];                       // +0xD5
    SelectionMode m_eSelectionMode;                 // +0xD8
    int m_unkDC;                                    // +0xDC set to 10 by the constructor
    int m_unkE0;                                    // +0xE0
    int m_unkE4;                                    // +0xE4
    int m_unkE8;                                    // +0xE8 end of object (0xEC bytes)

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
