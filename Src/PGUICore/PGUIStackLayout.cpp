// PGUIStackLayout accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIStackLayout.h"
#include "PPropertyValue.h"
#include "TNewDelete.h"

PGUIStackLayout::FlowDirection PGUIStackLayout::GetFlowDirection() const
{
    return m_eFlowDirection;
}

PGUIStackLayout::Alignment PGUIStackLayout::GetJustifyVert() const
{
    return m_eJustifyVert;
}

PGUIStackLayout::Alignment PGUIStackLayout::GetJustifyHoriz() const
{
    return m_eJustifyHoriz;
}

void PGUIStackLayout::SetFlowDirection(FlowDirection direction)
{
    m_eFlowDirection = direction;
}

void PGUIStackLayout::SetJustifyVert(Alignment alignment)
{
    m_eJustifyVert = alignment;
}

void PGUIStackLayout::SetJustifyHoriz(Alignment alignment)
{
    m_eJustifyHoriz = alignment;
}

PPropertyValue PGUIStackLayout::Get_flow_property() const
{
    return PPropertyValue((int)m_eFlowDirection);
}

void PGUIStackLayout::Set_flow_property(const PPropertyValue& value)
{
    m_eFlowDirection = (FlowDirection)value.GetInteger();
}

PPropertyValue PGUIStackLayout::Get_justifyvert_property() const
{
    return PPropertyValue((int)m_eJustifyVert);
}

void PGUIStackLayout::Set_justifyvert_property(const PPropertyValue& value)
{
    m_eJustifyVert = (Alignment)value.GetInteger();
}

PPropertyValue PGUIStackLayout::Get_justifyhoriz_property() const
{
    return PPropertyValue((int)m_eJustifyHoriz);
}

void PGUIStackLayout::Set_justifyhoriz_property(const PPropertyValue& value)
{
    m_eJustifyHoriz = (Alignment)value.GetInteger();
}

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIStackLayout::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIStackLayout::ms_oPropertySet;
Toshi::TGUILayoutInfo* PGUIStackLayout::ms_layout_info;

PGUIStackLayout::PGUIStackLayout()
{
    m_eFlowDirection = (FlowDirection)0;
    m_eJustifyHoriz = (Alignment)0;
    m_eJustifyVert = (Alignment)0;
    m_pLayoutInfo = ms_layout_info;
}

PGUIStackLayout::PGUIStackLayout(const PGUIStackLayout& other)
    : PGUILayoutManager(other)
{
    m_eFlowDirection = other.m_eFlowDirection;
    m_eJustifyHoriz = other.m_eJustifyHoriz;
    m_eJustifyVert = other.m_eJustifyVert;
    m_pLayoutInfo = ms_layout_info;
}

PGUIStackLayout* PGUIStackLayout::Clone() const
{
    return new (tmalloc(sizeof(PGUIStackLayout), 0, -1)) PGUIStackLayout(*this);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIStackLayout::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIStackLayout::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIStackLayout::Serialise(PProperties* properties)
{
    if (!TGUILayoutManager::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIStackLayout::Deserialise(const PProperties* properties)
{
    if (!TGUILayoutManager::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIStackLayout::Val_justifyhoriz_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (value.GetInteger() == 0 || value.GetInteger() == 1) {
        return true;
    }
    if (value.GetInteger() == 2) {
        return true;
    }
    return false;
}

bool PGUIStackLayout::Val_justifyvert_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    if (value.GetInteger() == 0 || value.GetInteger() == 1) {
        return true;
    }
    if (value.GetInteger() == 2) {
        return true;
    }
    return false;
}

bool PGUIStackLayout::Val_flow_property(const PPropertyValue& value)
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
