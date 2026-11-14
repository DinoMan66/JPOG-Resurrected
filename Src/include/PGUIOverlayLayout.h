// PGUIOverlayLayout (PGUICore.dll): a layout manager that stacks all children on top of each other, each
// justified inside the parent. Only the accessors are written so far.
#ifndef PGUIOVERLAYLAYOUT_H
#define PGUIOVERLAYLAYOUT_H
#include "PGUIAPI.h"
#include "TGUILayoutManager.h"

class PPropertyValue;

class PGUI_API PGUIOverlayLayout : public Toshi::TGUILayoutManager
{
public:
    virtual PGUIOverlayLayout* Clone() const;                    // slot 13
    virtual void DoPack(Toshi::TGUIWidget* widget) const;                           // slot 14
    virtual void DoLayout(Toshi::TGUIWidget* widget, int& arg1, int& arg2) const;   // slot 15
    bool Val_justifyhoriz_property(const PPropertyValue& value);
    bool Val_justifyvert_property(const PPropertyValue& value);
    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    Alignment GetJustifyVert() const;
    Alignment GetJustifyHoriz() const;
    bool GetForceSameHeight() const;
    bool GetForceSameWidth() const;
    void SetJustifyHoriz(Alignment alignment);
    void SetJustifyVert(Alignment alignment);
    void SetForceSameHeight(bool force);
    void SetForceSameWidth(bool force);

    PPropertyValue Get_justifyvert_property() const;
    void Set_justifyvert_property(const PPropertyValue& value);
    PPropertyValue Get_justifyhoriz_property() const;
    void Set_justifyhoriz_property(const PPropertyValue& value);
    bool Val_fillvertical_property(const PPropertyValue& value);
    PPropertyValue Get_fillvertical_property() const;
    void Set_fillvertical_property(const PPropertyValue& value);
    bool Val_fillhorizontal_property(const PPropertyValue& value);
    PPropertyValue Get_fillhorizontal_property() const;
    void Set_fillhorizontal_property(const PPropertyValue& value);
    bool Val_sameheight_property(const PPropertyValue& value);
    PPropertyValue Get_sameheight_property() const;
    void Set_sameheight_property(const PPropertyValue& value);
    bool Val_samewidth_property(const PPropertyValue& value);
    PPropertyValue Get_samewidth_property() const;
    void Set_samewidth_property(const PPropertyValue& value);

protected:
    PGUIOverlayLayout(const PGUIOverlayLayout& other);
    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    bool m_bForceSameWidth;             // +0x0C
    bool m_bForceSameHeight;            // +0x0D
    bool m_bFillHorizontal;             // +0x0E
    bool m_bFillVertical;               // +0x0F
    Alignment m_eJustifyHoriz;          // +0x10
    Alignment m_eJustifyVert;           // +0x14

    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
    static Toshi::TGUILayoutInfo* ms_layout_info;
};

#endif
