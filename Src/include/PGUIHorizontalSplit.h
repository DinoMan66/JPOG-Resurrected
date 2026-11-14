// PGUIHorizontalSplit (PGUICore.dll): a panel that splits its area between two child widgets.
// Only the property-set accessors are written so far.
#ifndef PGUIHORIZONTALSPLIT_H
#define PGUIHORIZONTALSPLIT_H
#include "PGUIAPI.h"
#include "PGUIPanel.h"

class PPropertyValue;

class PGUI_API PGUIHorizontalSplit : public PGUIPanel
{
public:
    bool Val_stretchtop_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual PGUIHorizontalSplit* Clone() const;                                   // slot 13
    virtual void Pack();                                                // slot 33
    Toshi::TGUIWidget* GetTopWidget() const;
    Toshi::TGUIWidget* GetBottomWidget() const;
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();

    PPropertyValue Get_stretchtop_property() const;
    void Set_stretchtop_property(const PPropertyValue& value);
    PPropertyValue Get_stretchbottom_property() const;
    void Set_stretchbottom_property(const PPropertyValue& value);

protected:
    PGUIHorizontalSplit(const PGUIHorizontalSplit& other);

    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    float m_fStretchTop;                     // +0x8C
    float m_fStretchBottom;                     // +0x90

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
