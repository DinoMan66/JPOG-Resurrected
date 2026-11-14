// PGUIStackLayout (PGUICore.dll): a layout manager that lines the children up one after another in a
// flow direction, each justified inside its slot. Only the accessors are written so far.
#ifndef PGUISTACKLAYOUT_H
#define PGUISTACKLAYOUT_H
#include "PGUIAPI.h"
#include "PGUILayoutManager.h"

class PPropertyValue;

class PGUI_API PGUIStackLayout : public Toshi::PGUILayoutManager
{
public:
    bool Val_justifyhoriz_property(const PPropertyValue& value);
    bool Val_justifyvert_property(const PPropertyValue& value);
    bool Val_flow_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual PGUIStackLayout* Clone() const;                      // slot 13
    PGUIStackLayout();
    enum FlowDirection
    {
    };

    FlowDirection GetFlowDirection() const;
    Alignment GetJustifyVert() const;
    Alignment GetJustifyHoriz() const;
    void SetFlowDirection(FlowDirection direction);
    void SetJustifyHoriz(Alignment alignment);
    void SetJustifyVert(Alignment alignment);

    PPropertyValue Get_flow_property() const;
    void Set_flow_property(const PPropertyValue& value);
    PPropertyValue Get_justifyvert_property() const;
    void Set_justifyvert_property(const PPropertyValue& value);
    PPropertyValue Get_justifyhoriz_property() const;
    void Set_justifyhoriz_property(const PPropertyValue& value);

    virtual void DoPack(Toshi::TGUIWidget* widget) const;                           // slot 14
    virtual void DoLayout(Toshi::TGUIWidget* widget, int& arg1, int& arg2) const;   // slot 15

protected:
    PGUIStackLayout(const PGUIStackLayout& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    FlowDirection m_eFlowDirection;     // +0x14
    Alignment m_eJustifyHoriz;          // +0x18
    Alignment m_eJustifyVert;           // +0x1C

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
    static Toshi::TGUILayoutInfo* ms_layout_info;
};

#endif
