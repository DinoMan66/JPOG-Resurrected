// PGUIToggleButton (PGUICore.dll): a button that stays down after it is pressed until it is pressed again.
// Only the accessors are written so far.
#ifndef PGUITOGGLEBUTTON_H
#define PGUITOGGLEBUTTON_H
#include "PGUIAPI.h"
#include "PGUIButton.h"

class PPropertyValue;

class PGUI_API PGUIToggleButton : public PGUIButton
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    bool Val_test_property(const PPropertyValue& value);
    PPropertyValue Get_test_property() const;
    void Set_test_property(const PPropertyValue& value);
    // Bit of the widget state, added to the ones PGUIButton defines
    enum
    {
        STATE_TOGGLED = 0x40
    };

    bool IsToggled() const;
    void SetToggled(bool toggled);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4

    virtual PGUIToggleButton* Clone() const;                            // slot 13

protected:
    PGUIToggleButton(const PGUIToggleButton& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
