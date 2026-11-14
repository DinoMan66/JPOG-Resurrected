// PGUIDiscMenuDialog (PGUICore.dll): a menu dialog that arranges its entries on a disc (see PGUIDiscLayout).
// Only the property-set accessors are written so far.
#ifndef PGUIDISCMENUDIALOG_H
#define PGUIDISCMENUDIALOG_H
#include "PGUIAPI.h"
#include "PGUIMenuDialog.h"

class PGUI_API PGUIDiscMenuDialog : public PGUIMenuDialog
{
public:
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual bool OnButtonPress(Toshi::TInputInterface::InputEvent* event, int doodad);      // slot 24
    virtual bool OnButtonRelease(Toshi::TInputInterface::InputEvent* event, int doodad);    // slot 26
    virtual PGUIDiscMenuDialog* Clone() const;                          // slot 13
    virtual void Pack();                                                // slot 33
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();

protected:
    PGUIDiscMenuDialog(const PGUIDiscMenuDialog& other);

    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    void* m_unkF4;                                          // +0xF4 (cleared by the copy constructor)
    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
