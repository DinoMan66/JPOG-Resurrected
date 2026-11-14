// PGUIPanel (PGUICore.dll): a widget that holds other widgets. Splits, menu bars, tables and owner-drawn
// areas are panels. It adds an "editing" state bit. Only the accessors are written so far.
#ifndef PGUIPANEL_H
#define PGUIPANEL_H
#include "PGUIAPI.h"
#include "TGUIWidget.h"

class PGUI_API PGUIPanel : public Toshi::TGUIWidget
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    virtual void Pack();                                                // slot 33
    // Bit of the widget state, added to the ones TGUIWidget defines
    enum
    {
        STATE_EDITING = 0x20
    };

    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual bool AllowsChildren() const;                                // slot 15

    bool IsEditing() const;
    void SetEditing(bool editing);

    virtual PGUIPanel* Clone() const;                                  // slot 13

protected:
    PGUIPanel(const PGUIPanel& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
