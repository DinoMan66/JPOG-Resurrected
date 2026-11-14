// PGUISliderBar (PGUICore.dll): a widget with a draggable handle that picks a value between a minimum and
// a maximum, in steps. Only the accessors are written so far.
#ifndef PGUISLIDERBAR_H
#define PGUISLIDERBAR_H
#include "PGUIAPI.h"
#include "TGUIWidget.h"

class PPropertyValue;

class PGUI_API PGUISliderBar : public Toshi::TGUIWidget
{
public:
    virtual PGUISliderBar* Clone() const;                                  // slot 13
    static const Toshi::TGUIWidgetInfo* GetStaticWidgetInfo();
    bool Val_orientation_property(const PPropertyValue& value);
    // Bits of the widget state, added to the ones TGUIWidget defines
    enum
    {
        STATE_DRAGGING = 0x20,
        STATE_INCREMENTING = 0x40,
        STATE_DECREMENTING = 0x80,
        STATE_CAN_INCREMENT = 0x100,
        STATE_CAN_DECREMENT = 0x200
    };

    virtual bool Deserialise(const PProperties* properties);     // slot 3
    virtual bool Serialise(PProperties* properties);             // slot 4
    virtual void Pack();                                                // slot 33
    virtual bool AcceptsFocus() const;                                  // slot 16

    float GetStepValue() const;
    float GetMaximumValue() const;
    float GetMinimumValue() const;
    float GetCurrentValue() const;
    bool IsCanIncrement() const;
    bool IsCanDecrement() const;
    bool IsIncrementing() const;
    bool IsDragging() const;
    bool IsDecrementing() const;
    void SetMinimumValue(float value);
    void SetMaximumValue(float value);
    void SetCurrentValue(float value);
    void SetRange(float minimum, float maximum);
    void SetCanIncrement(bool value);
    void SetCanDecrement(bool value);
    void SetIncrementing(bool value);
    void SetDecrementing(bool value);
    void SetDragging(bool value);
    void SetOrientation(int orientation);
    void SetStepValue(float value);

    PPropertyValue Get_orientation_property() const;
    void Set_orientation_property(const PPropertyValue& value);
    bool Val_valuestep_property(const PPropertyValue& value);
    PPropertyValue Get_valuestep_property() const;
    void Set_valuestep_property(const PPropertyValue& value);
    bool Val_valuecurr_property(const PPropertyValue& value);
    PPropertyValue Get_valuecurr_property() const;
    void Set_valuecurr_property(const PPropertyValue& value);
    bool Val_valuemax_property(const PPropertyValue& value);
    PPropertyValue Get_valuemax_property() const;
    void Set_valuemax_property(const PPropertyValue& value);
    bool Val_valuemin_property(const PPropertyValue& value);
    PPropertyValue Get_valuemin_property() const;
    void Set_valuemin_property(const PPropertyValue& value);

protected:
    PGUISliderBar(const PGUISliderBar& other);
    virtual void NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to);       // slot 21
    void PackComponents();
    void UpdateKnob();

    virtual const Toshi::TArray<Toshi::TGUIPropertySpec*>* GetPropertyInfoSet() const;      // slot 11
    virtual const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* GetPropertyInfoOrderedSet() const;   // slot 12

private:
    unsigned char m_unk8C[0x14];        // +0x8C
    float m_fMinimumValue;              // +0xA0
    float m_fMaximumValue;              // +0xA4
    float m_fCurrentValue;              // +0xA8
    float m_fStepValue;                 // +0xAC
    int m_iOrientation;                 // +0xB0
    int m_unkB4;                        // +0xB4

    static Toshi::TGUIWidgetInfo* ms_widget_info;
    static Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* ms_oPropertySetOrdered;
    static Toshi::TArray<Toshi::TGUIPropertySpec*>* ms_oPropertySet;
};

#endif
