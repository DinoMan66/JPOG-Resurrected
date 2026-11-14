// PGUIPushButton (PGUICore.dll): a button that fires its action when it is pressed.
// Only the property-set accessors are written so far.
#ifndef PGUIPUSHBUTTON_H
#define PGUIPUSHBUTTON_H
#include "PGUIAPI.h"
#include "PGUIButton.h"

class PGUI_API PGUIPushButton : public PGUIButton
{
public:
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual void Pack();                                                // slot 33

    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    virtual PGUIPushButton* Clone() const;                                  // slot 13

protected:
    PGUIPushButton(const PGUIPushButton& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    static Toshi::TGUIWidgetInfo* ms_widget_info;

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
