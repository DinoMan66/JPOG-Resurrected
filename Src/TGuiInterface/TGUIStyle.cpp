// Z:\Toshi\Source\TGUI - TGUIStyle. The original file name is not in the binary's strings.
// Only the accessors and the class boilerplate are written so far; the constructor is still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "PPropertyValue.h"
#include "TGUIStyle.h"
#include "TGUIWidgetInfo.h"
#include "TGUIWidget.h"
#include "PPropertyValue.h"

namespace Toshi {

TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIStyle::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUIStyle::ms_oPropertySet;

TClass TGUIStyle::m_sClass("TGUIStyle", &TGUIDeserialisable::m_sClass, TGUIStyle::CreateObject,
                           TGUIStyle::CreateObjectInPlace, TGUIStyle::InitialiseStatic,
                           TGUIStyle::DeinitialiseStatic, 0x10000);

void TGUIStyle::Set_name_property(const PPropertyValue& value)
{
    m_oName = value.GetTPCString();
}

bool TGUIStyle::Val_margintop_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && value.GetInteger() >= 0;
}

bool TGUIStyle::Val_marginbottom_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && value.GetInteger() >= 0;
}

bool TGUIStyle::Val_marginleft_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && value.GetInteger() >= 0;
}

bool TGUIStyle::Val_marginright_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT) && value.GetInteger() >= 0;
}

// The component is named, the first state whose rule accepts the state bits is returned
TGUIStyleState* TGUIStyle::GetState(const TPCString& component, unsigned int stateBits) const
{
    int index = m_pWidgetInfo->GetComponentIndex(component);
    if (index < 0) {
        return 0;
    }
    return GetState(index, stateBits);
}

TGUIStyleState* TGUIStyle::GetState(int component, unsigned int stateBits) const
{
    TGUIStyleRootComponent& root = m_pRootComponents[component];
    for (TNodeList<TGUIStyleState>::Iterator it(root.Begin()); it != root.End(); ++it) {
        if (it->AppliesTo(stateBits)) {
            return it.Get();
        }
    }
    return 0;
}

// A style fits a widget when it was made for the widget's class (or the widget's own style fits)
bool TGUIStyle::IsCompatibleWith(TGUIWidget* widget)
{
    if (widget == 0) {
        return false;
    }
    if (widget->GetStyle() != 0) {
        return IsCompatibleWith(widget->GetStyle());
    }
    return m_pWidgetInfo == widget->GetWidgetInfo();
}

// Two styles are compatible when they belong to the same widget class and their parameters agree
bool TGUIStyle::IsCompatibleWith(TGUIStyle* style)
{
    if (m_pWidgetInfo != style->m_pWidgetInfo) {
        return false;
    }
    bool compatible = false;
    if (m_ucParameterCount == style->m_ucParameterCount) {
        compatible = true;
        for (int i = 0; i < m_ucParameterCount && compatible; i++) {
            const TGUIStyleParameterInfo* mine = GetParameterInfo(i);
            const TGUIStyleParameterInfo* theirs = style->GetParameterInfo(i);
            if (mine->m_oName != theirs->m_oName) {
                compatible = false;
            } else if (mine->m_pType != PPropertyValue::TYPE_UNDEF
                       && theirs->m_pType != PPropertyValue::TYPE_UNDEF
                       && mine->m_pType != theirs->m_pType) {
                compatible = false;
            }
        }
    }
    return compatible;
}

const TGUIStyleParameterInfo* TGUIStyle::GetParameterInfo(int index) const
{
    return &m_pParameterInfos[index];
}

const TGUIStyleParameterInfo* TGUIStyle::GetParameterInfo(const TPCString& name) const
{
    int index = FindParameter(name);
    if (index == -1) {
        return 0;
    }
    return GetParameterInfo(index);
}

int TGUIStyle::FindParameter(const TPCString& name) const
{
    int count = m_ucParameterCount;
    if (count != 0) {
        for (int i = 0; i < count; i++) {
            if (m_pParameterInfos[i].m_oName == name) {
                return i;
            }
        }
    }
    return -1;
}

PPropertyValue TGUIStyle::Get_margintop_property() const
{
    return PPropertyValue(m_sMarginTop);
}

void TGUIStyle::Set_margintop_property(const PPropertyValue& value)
{
    m_sMarginTop = value.GetInteger();
}

PPropertyValue TGUIStyle::Get_marginbottom_property() const
{
    return PPropertyValue(m_sMarginBottom);
}

void TGUIStyle::Set_marginbottom_property(const PPropertyValue& value)
{
    m_sMarginBottom = value.GetInteger();
}

PPropertyValue TGUIStyle::Get_marginleft_property() const
{
    return PPropertyValue(m_sMarginLeft);
}

void TGUIStyle::Set_marginleft_property(const PPropertyValue& value)
{
    m_sMarginLeft = value.GetInteger();
}

PPropertyValue TGUIStyle::Get_marginright_property() const
{
    return PPropertyValue(m_sMarginRight);
}

void TGUIStyle::Set_marginright_property(const PPropertyValue& value)
{
    m_sMarginRight = value.GetInteger();
}

bool TGUIStyle::IsWidgetStyle(const TPCString& widgetName) const
{
    return m_pWidgetInfo->GetWidgetName() == widgetName;
}

PPropertyValue TGUIStyle::GetFixedWidgetProperty(const TPCString& name) const
{
    TGUIPairNode<TPCString, PPropertyValue>* pair = FindFixedWidgetPropertyPair(name);
    if (pair != 0) {
        return pair->m_oValue;
    }
    return PPropertyValue();
}

void TGUIStyle::ApplyFixedWidgetProperties(TGUIWidget* widget)
{
    for (TNodeList<TGUIPairNode<TPCString, PPropertyValue> >::Iterator it(m_oFixedProperties.Begin());
         it != m_oFixedProperties.End();
         ++it) {
        widget->SetProperty(it->m_oKey, it->m_oValue);
    }
}

// Forgets the fixed value of a widget property
void TGUIStyle::ReleaseFixedWidgetProperty(const TPCString& name)
{
    TGUIPairNode<TPCString, PPropertyValue>* pair = FindFixedWidgetPropertyPair(name);
    if (pair != 0) {
        m_oFixedProperties.Remove(pair);
        delete pair;
    }
}

bool TGUIStyle::IsWidgetPropertyFixed(const TPCString& name) const
{
    if (FindFixedWidgetPropertyPair(name) != 0) {
        return true;
    }
    return false;
}

TGUIPairNode<TPCString, PPropertyValue>* TGUIStyle::FindFixedWidgetPropertyPair(const TPCString& name) const
{
    for (TNodeList<TGUIPairNode<TPCString, PPropertyValue> >::Iterator it(m_oFixedProperties.Begin());
         it != m_oFixedProperties.End();
         ++it) {
        if (name == it->m_oKey) {
            return it.Get();
        }
    }
    return 0;
}

bool TGUIStyle::Val_name_property() const
{
    return true;
}

PPropertyValue TGUIStyle::Get_name_property() const
{
    return PPropertyValue(m_oName);
}

TGUIStyle* TGUIStyle::Clone() const
{
    return new TGUIStyle(*this);
}

TClass& TGUIStyle::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIStyle::DeinitialiseStatic()
{
    for (TArray<TGUIPropertySpec*>::Iterator it(*ms_oPropertySet); it.IsValid(); ++it) {
        delete *it;
    }
    delete ms_oPropertySet;
    delete ms_oPropertySetOrdered;
    ms_oPropertySet = 0;
    ms_oPropertySetOrdered = 0;
}

void __stdcall TGUIStyle::InitialiseStatic()
{
}

TObject* __stdcall TGUIStyle::CreateObjectInPlace(void* memory)
{
    return memory ? new (memory) TGUIStyle : 0;
}

TObject* __stdcall TGUIStyle::CreateObject()
{
    return new TGUIStyle;
}

TGUIStyle::TGUIStyle()
    : m_pInterface(0)
    , m_pRootComponents(0)
    , m_pWidgetInfo(0)
    , m_ucParameterCount(0)
    , m_pParameterInfos(0)
    , m_sMarginTop(0)
    , m_sMarginBottom(0)
    , m_sMarginLeft(0)
    , m_sMarginRight(0)
{
}

} // namespace Toshi
