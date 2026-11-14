// PGUIDiscLayout (PGUICore.dll): a layout manager that places a widget's children on the edge of an ellipse
// (a "disc"), used for radial menus. The property names in the exported functions (slotcount, slotallocation,
// flowdirection, offsetangle, radiusx, radiusy, samewidth, sameheight) name the settings below.
// Only the accessors are written so far; the enumerator values of the two enums are not known yet.
#ifndef PGUIDISCLAYOUT_H
#define PGUIDISCLAYOUT_H
#include "PGUIAPI.h"
#include "TGUILayoutManager.h"

class PPropertyValue;

class PGUI_API PGUIDiscLayout : public Toshi::TGUILayoutManager
{
public:
    PGUIDiscLayout();
    virtual PGUIDiscLayout* Clone() const;                       // slot 13
    virtual void DoPack(Toshi::TGUIWidget* widget) const;                           // slot 14
    virtual void DoLayout(Toshi::TGUIWidget* widget, int& arg1, int& arg2) const;   // slot 15
    bool Val_flowdirection_property(const PPropertyValue& value);
    bool Val_slotallocation_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    enum SlotAllocation
    {
    };

    enum FlowDirection
    {
    };

    SlotAllocation GetSlotAllocation() const;
    FlowDirection GetFlowDirection() const;
    int GetSlotCount() const;
    float GetOffsetAngle() const;
    float GetRadiusY() const;
    float GetRadiusX() const;
    bool GetForceSameHeight() const;
    bool GetForceSameWidth() const;
    void SetSlotAllocation(SlotAllocation allocation);
    void SetFlowDirection(FlowDirection direction);
    void SetSlotCount(int count);
    void SetOffsetAngle(float angle);
    void SetRadiusY(float radius);
    void SetRadiusX(float radius);
    void SetForceSameHeight(bool force);
    void SetForceSameWidth(bool force);

    bool Val_slotcount_property(const PPropertyValue& value);
    bool Val_offsetangle_property(const PPropertyValue& value);
    PPropertyValue Get_slotcount_property() const;
    void Set_slotcount_property(const PPropertyValue& value);
    PPropertyValue Get_slotallocation_property() const;
    void Set_slotallocation_property(const PPropertyValue& value);
    PPropertyValue Get_flowdirection_property() const;
    void Set_flowdirection_property(const PPropertyValue& value);
    bool Val_radiusy_property(const PPropertyValue& value);
    PPropertyValue Get_radiusy_property() const;
    void Set_radiusy_property(const PPropertyValue& value);
    bool Val_radiusx_property(const PPropertyValue& value);
    PPropertyValue Get_radiusx_property() const;
    void Set_radiusx_property(const PPropertyValue& value);
    bool Val_fullheight_property(const PPropertyValue& value);
    PPropertyValue Get_fullheight_property() const;
    void Set_fullheight_property(const PPropertyValue& value);
    bool Val_fullwidth_property(const PPropertyValue& value);
    PPropertyValue Get_fullwidth_property() const;
    void Set_fullwidth_property(const PPropertyValue& value);
    bool Val_sameheight_property(const PPropertyValue& value);
    PPropertyValue Get_sameheight_property() const;
    void Set_sameheight_property(const PPropertyValue& value);
    bool Val_samewidth_property(const PPropertyValue& value);
    PPropertyValue Get_samewidth_property() const;
    void Set_samewidth_property(const PPropertyValue& value);

protected:
    PGUIDiscLayout(const PGUIDiscLayout& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    bool m_bForceSameWidth;             // +0x0C
    bool m_bForceSameHeight;            // +0x0D
    bool m_bFullWidth;                  // +0x0E
    bool m_bFullHeight;                 // +0x0F
    float m_fRadiusX;                   // +0x10
    float m_fRadiusY;                   // +0x14
    float m_fOffsetAngle;               // +0x18
    int m_iSlotCount;                   // +0x1C
    FlowDirection m_eFlowDirection;     // +0x20
    SlotAllocation m_eSlotAllocation;   // +0x24

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
    static Toshi::TGUILayoutInfo* ms_layout_info;
};

#endif
