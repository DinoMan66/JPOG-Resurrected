// PGUIListItem (PGUICore.dll): one entry of a list box. It points at the item's data and remembers its
// position in the list. Only the accessors are written so far.
#ifndef PGUILISTITEM_H
#define PGUILISTITEM_H
#include "PGUIAPI.h"
#include "TGUIWidget.h"

class PGUIItemData;

class PGUI_API PGUIListItem : public Toshi::TGUIWidget
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    virtual void Pack();                                                // slot 33
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual bool AcceptsFocus() const;                                  // slot 16

    void SetIndex(int index);
    int GetIndex() const;
    void SetData(PGUIItemData* data);

    virtual PGUIListItem* Clone() const;                                  // slot 13

protected:
    PGUIListItem(const PGUIListItem& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    PGUIItemData* m_pData;      // +0x8C
    int m_iIndex;               // +0x90

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
