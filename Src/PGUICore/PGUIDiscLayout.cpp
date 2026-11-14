// PGUIDiscLayout accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIDiscLayout.h"
#include "PPropertyValue.h"
#include "TNewDelete.h"

PGUIDiscLayout::SlotAllocation PGUIDiscLayout::GetSlotAllocation() const
{
    return m_eSlotAllocation;
}

PGUIDiscLayout::FlowDirection PGUIDiscLayout::GetFlowDirection() const
{
    return m_eFlowDirection;
}

int PGUIDiscLayout::GetSlotCount() const
{
    return m_iSlotCount;
}

float PGUIDiscLayout::GetOffsetAngle() const
{
    return m_fOffsetAngle;
}

float PGUIDiscLayout::GetRadiusY() const
{
    return m_fRadiusY;
}

float PGUIDiscLayout::GetRadiusX() const
{
    return m_fRadiusX;
}

bool PGUIDiscLayout::GetForceSameHeight() const
{
    return m_bForceSameHeight;
}

bool PGUIDiscLayout::GetForceSameWidth() const
{
    return m_bForceSameWidth;
}

void PGUIDiscLayout::SetSlotAllocation(SlotAllocation allocation)
{
    m_eSlotAllocation = allocation;
}

void PGUIDiscLayout::SetFlowDirection(FlowDirection direction)
{
    m_eFlowDirection = direction;
}

void PGUIDiscLayout::SetSlotCount(int count)
{
    m_iSlotCount = count;
}

void PGUIDiscLayout::SetOffsetAngle(float angle)
{
    m_fOffsetAngle = angle;
}

void PGUIDiscLayout::SetRadiusY(float radius)
{
    m_fRadiusY = radius;
}

void PGUIDiscLayout::SetRadiusX(float radius)
{
    m_fRadiusX = radius;
}

void PGUIDiscLayout::SetForceSameHeight(bool force)
{
    m_bForceSameHeight = force;
}

void PGUIDiscLayout::SetForceSameWidth(bool force)
{
    m_bForceSameWidth = force;
}

bool PGUIDiscLayout::Val_slotcount_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_INT);
}

bool PGUIDiscLayout::Val_offsetangle_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUIDiscLayout::Get_slotcount_property() const
{
    return PPropertyValue(m_iSlotCount);
}

void PGUIDiscLayout::Set_slotcount_property(const PPropertyValue& value)
{
    m_iSlotCount = value.GetInteger();
}

PPropertyValue PGUIDiscLayout::Get_slotallocation_property() const
{
    return PPropertyValue((int)m_eSlotAllocation);
}

void PGUIDiscLayout::Set_slotallocation_property(const PPropertyValue& value)
{
    m_eSlotAllocation = (SlotAllocation)value.GetInteger();
}

PPropertyValue PGUIDiscLayout::Get_flowdirection_property() const
{
    return PPropertyValue((int)m_eFlowDirection);
}

void PGUIDiscLayout::Set_flowdirection_property(const PPropertyValue& value)
{
    m_eFlowDirection = (FlowDirection)value.GetInteger();
}

bool PGUIDiscLayout::Val_radiusy_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUIDiscLayout::Get_radiusy_property() const
{
    return PPropertyValue(m_fRadiusY);
}

void PGUIDiscLayout::Set_radiusy_property(const PPropertyValue& value)
{
    m_fRadiusY = value.GetFloat();
}

bool PGUIDiscLayout::Val_radiusx_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_FLOAT);
}

PPropertyValue PGUIDiscLayout::Get_radiusx_property() const
{
    return PPropertyValue(m_fRadiusX);
}

void PGUIDiscLayout::Set_radiusx_property(const PPropertyValue& value)
{
    m_fRadiusX = value.GetFloat();
}

bool PGUIDiscLayout::Val_fullheight_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIDiscLayout::Get_fullheight_property() const
{
    return PPropertyValue(m_bFullHeight);
}

void PGUIDiscLayout::Set_fullheight_property(const PPropertyValue& value)
{
    m_bFullHeight = value.GetBoolean();
}

bool PGUIDiscLayout::Val_fullwidth_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIDiscLayout::Get_fullwidth_property() const
{
    return PPropertyValue(m_bFullWidth);
}

void PGUIDiscLayout::Set_fullwidth_property(const PPropertyValue& value)
{
    m_bFullWidth = value.GetBoolean();
}

bool PGUIDiscLayout::Val_sameheight_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIDiscLayout::Get_sameheight_property() const
{
    return PPropertyValue(m_bForceSameHeight);
}

void PGUIDiscLayout::Set_sameheight_property(const PPropertyValue& value)
{
    m_bForceSameHeight = value.GetBoolean();
}

bool PGUIDiscLayout::Val_samewidth_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIDiscLayout::Get_samewidth_property() const
{
    return PPropertyValue(m_bForceSameWidth);
}

void PGUIDiscLayout::Set_samewidth_property(const PPropertyValue& value)
{
    m_bForceSameWidth = value.GetBoolean();
}

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIDiscLayout::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIDiscLayout::ms_oPropertySet;
Toshi::TGUILayoutInfo* PGUIDiscLayout::ms_layout_info;

PGUIDiscLayout::PGUIDiscLayout()
{
    m_bForceSameWidth = false;
    m_bForceSameHeight = false;
    m_bFullWidth = false;
    m_bFullHeight = false;
    m_fRadiusX = 100.0f;
    m_fRadiusY = 100.0f;
    m_fOffsetAngle = 0.0f;
    m_iSlotCount = 0;
    m_eFlowDirection = (FlowDirection)0;
    m_eSlotAllocation = (SlotAllocation)0;
    m_pLayoutInfo = ms_layout_info;
}

PGUIDiscLayout::PGUIDiscLayout(const PGUIDiscLayout& other)
    : TGUILayoutManager(other)
{
    m_bForceSameWidth = other.m_bForceSameWidth;
    m_bForceSameHeight = other.m_bForceSameHeight;
    m_bFullWidth = other.m_bFullWidth;
    m_bFullHeight = other.m_bFullHeight;
    m_fRadiusX = other.m_fRadiusX;
    m_fRadiusY = other.m_fRadiusY;
    m_fOffsetAngle = other.m_fOffsetAngle;
    m_iSlotCount = other.m_iSlotCount;
    m_eFlowDirection = other.m_eFlowDirection;
    m_eSlotAllocation = other.m_eSlotAllocation;
    m_pLayoutInfo = ms_layout_info;
}

PGUIDiscLayout* PGUIDiscLayout::Clone() const
{
    return new (tmalloc(sizeof(PGUIDiscLayout), 0, -1)) PGUIDiscLayout(*this);
}

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIDiscLayout::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIDiscLayout::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIDiscLayout::Serialise(PProperties* properties)
{
    if (!TGUILayoutManager::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIDiscLayout::Deserialise(const PProperties* properties)
{
    if (!TGUILayoutManager::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIDiscLayout::Val_flowdirection_property(const PPropertyValue& value)
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

bool PGUIDiscLayout::Val_slotallocation_property(const PPropertyValue& value)
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
