// PGUISliderBar accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUISliderBar.h"
#include "PPropertyValue.h"

static inline const float& Min(const float& a, const float& b)
{
    return (b < a) ? b : a;
}

static inline const float& Max(const float& a, const float& b)
{
    return (a < b) ? b : a;
}

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUISliderBar::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUISliderBar::ms_oPropertySet;

Toshi::TGUIWidgetInfo* PGUISliderBar::ms_widget_info;

const Toshi::TGUIWidgetInfo* PGUISliderBar::GetStaticWidgetInfo()
{
    return ms_widget_info;
}

bool PGUISliderBar::AcceptsFocus() const
{
    return true;
}

float PGUISliderBar::GetStepValue() const
{
    return m_fStepValue;
}

float PGUISliderBar::GetMaximumValue() const
{
    return m_fMaximumValue;
}

float PGUISliderBar::GetMinimumValue() const
{
    return m_fMinimumValue;
}

float PGUISliderBar::GetCurrentValue() const
{
    return m_fCurrentValue;
}

bool PGUISliderBar::IsCanIncrement() const
{
    return IsState(STATE_CAN_INCREMENT);
}

bool PGUISliderBar::IsCanDecrement() const
{
    return IsState(STATE_CAN_DECREMENT);
}

bool PGUISliderBar::IsIncrementing() const
{
    return IsState(STATE_INCREMENTING);
}

bool PGUISliderBar::IsDragging() const
{
    return IsState(STATE_DRAGGING);
}

void PGUISliderBar::Set_orientation_property(const PPropertyValue& value)
{
    SetOrientation(value.GetInteger());
}

void PGUISliderBar::SetOrientation(int orientation)
{
    if (orientation == 0 || orientation == 1)
    {
        m_iOrientation = orientation;
    }
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUISliderBar::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUISliderBar::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUISliderBar::IsDecrementing() const
{
    return IsState(STATE_DECREMENTING);
}

void PGUISliderBar::SetCanIncrement(bool value)
{
    SetState(STATE_CAN_INCREMENT, value);
}

void PGUISliderBar::SetCanDecrement(bool value)
{
    SetState(STATE_CAN_DECREMENT, value);
}

void PGUISliderBar::SetDecrementing(bool value)
{
    SetState(STATE_DECREMENTING, value);
}

void PGUISliderBar::SetIncrementing(bool value)
{
    SetState(STATE_INCREMENTING, value);
}

void PGUISliderBar::SetDragging(bool value)
{
    SetState(STATE_DRAGGING, value);
}

void PGUISliderBar::SetMaximumValue(float value)
{
    m_fMaximumValue = Max(value, m_fMinimumValue);
    m_fCurrentValue = Min(m_fCurrentValue, m_fMaximumValue);
    UpdateKnob();
}

void PGUISliderBar::SetMinimumValue(float value)
{
    m_fMinimumValue = Min(value, m_fMaximumValue);
    m_fCurrentValue = Max(m_fCurrentValue, m_fMinimumValue);
    UpdateKnob();
}

void PGUISliderBar::SetCurrentValue(float value)
{
    m_fCurrentValue = Max(m_fMinimumValue, Min(m_fMaximumValue, value));
    UpdateKnob();
}

void PGUISliderBar::SetRange(float minimum, float maximum)
{
    m_fMinimumValue = minimum;
    m_fMaximumValue = Max(minimum, maximum);
    m_fCurrentValue = Max(m_fMinimumValue, Min(m_fMaximumValue, m_fCurrentValue));
    UpdateKnob();
}

void PGUISliderBar::SetStepValue(float value)
{
    m_fStepValue = Max(0.0f, value);
}

PPropertyValue PGUISliderBar::Get_orientation_property() const
{
    return PPropertyValue(m_iOrientation);
}

bool PGUISliderBar::Val_valuestep_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUISliderBar::Get_valuestep_property() const
{
    return PPropertyValue(m_fStepValue);
}

void PGUISliderBar::Set_valuestep_property(const PPropertyValue& value)
{
    SetStepValue(value.GetFloat());
}

bool PGUISliderBar::Val_valuecurr_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUISliderBar::Get_valuecurr_property() const
{
    return PPropertyValue(m_fCurrentValue);
}

void PGUISliderBar::Set_valuecurr_property(const PPropertyValue& value)
{
    SetCurrentValue(value.GetFloat());
    Pack();
}

bool PGUISliderBar::Val_valuemax_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUISliderBar::Get_valuemax_property() const
{
    return PPropertyValue(m_fMaximumValue);
}

void PGUISliderBar::Set_valuemax_property(const PPropertyValue& value)
{
    SetMaximumValue(value.GetFloat());
    Pack();
}

bool PGUISliderBar::Val_valuemin_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUISliderBar::Get_valuemin_property() const
{
    return PPropertyValue(m_fMinimumValue);
}

void PGUISliderBar::Set_valuemin_property(const PPropertyValue& value)
{
    SetMinimumValue(value.GetFloat());
    Pack();
}

bool PGUISliderBar::Serialise(PProperties* properties)
{
    if (!TGUIWidget::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUISliderBar::Deserialise(const PProperties* properties)
{
    if (!TGUIWidget::Deserialise(properties)) {
        return false;
    }
    return true;
}

void PGUISliderBar::Pack()
{
    PackComponents();
}

bool PGUISliderBar::Val_orientation_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (value.GetInteger() == 0) {
        return true;
    }
    if (value.GetInteger() == 1) {
        return true;
    }
    return false;
}

void PGUISliderBar::NotifyFocusLost(Toshi::TGUIWidget* from, Toshi::TGUIWidget* to)
{
    SetIncrementing(false);
    SetDecrementing(false);
    SetDragging(false);
    TGUIWidget::NotifyFocusLost(from, to);
}

PGUISliderBar* PGUISliderBar::Clone() const
{
    return new PGUISliderBar(*this);
}
