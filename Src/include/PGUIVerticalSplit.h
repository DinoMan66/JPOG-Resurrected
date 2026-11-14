// PGUIVerticalSplit (PGUICore.dll): a panel that splits its area between two child widgets.
// Only the property-set accessors are written so far.
#ifndef PGUIVERTICALSPLIT_H
#define PGUIVERTICALSPLIT_H
#include "PGUIAPI.h"
#include "PGUIPanel.h"

class PPropertyValue;

class PGUI_API PGUIVerticalSplit : public PGUIPanel
{
public:
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    bool Val_stretchleft_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual PGUIVerticalSplit* Clone() const;                                   // slot 13
    virtual void Pack();                                                // slot 33
    Toshi::TGUIWidget* GetLeftWidget() const;
    Toshi::TGUIWidget* GetRightWidget() const;

    PPropertyValue Get_stretchleft_property() const;
    void Set_stretchleft_property(const PPropertyValue& value);
    PPropertyValue Get_stretchright_property() const;
    void Set_stretchright_property(const PPropertyValue& value);

protected:
    PGUIVerticalSplit(const PGUIVerticalSplit& other);

    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    float m_fStretchLeft;                     // +0x8C
    float m_fStretchRight;                     // +0x90

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
