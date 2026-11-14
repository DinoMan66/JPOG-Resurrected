// PGUIOverlayLayout accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUIOverlayLayout.h"
#include "PPropertyValue.h"
#include "TNewDelete.h"

Toshi::TGUILayoutInfo* PGUIOverlayLayout::ms_layout_info;

PGUIOverlayLayout::PGUIOverlayLayout(const PGUIOverlayLayout& other)
    : TGUILayoutManager(other)
{
    m_bForceSameWidth = other.m_bForceSameWidth;
    m_bForceSameHeight = other.m_bForceSameHeight;
    m_bFillHorizontal = other.m_bFillHorizontal;
    m_bFillVertical = other.m_bFillVertical;
    m_eJustifyHoriz = other.m_eJustifyHoriz;
    m_eJustifyVert = other.m_eJustifyVert;
    m_pLayoutInfo = ms_layout_info;
}

PGUIOverlayLayout* PGUIOverlayLayout::Clone() const
{
    return new (tmalloc(sizeof(PGUIOverlayLayout), 0, -1)) PGUIOverlayLayout(*this);
}

PGUIOverlayLayout::Alignment PGUIOverlayLayout::GetJustifyVert() const
{
    return m_eJustifyVert;
}

PGUIOverlayLayout::Alignment PGUIOverlayLayout::GetJustifyHoriz() const
{
    return m_eJustifyHoriz;
}

bool PGUIOverlayLayout::GetForceSameHeight() const
{
    return m_bForceSameHeight;
}

bool PGUIOverlayLayout::GetForceSameWidth() const
{
    return m_bForceSameWidth;
}

void PGUIOverlayLayout::SetJustifyHoriz(Alignment alignment)
{
    m_eJustifyHoriz = alignment;
}

void PGUIOverlayLayout::SetJustifyVert(Alignment alignment)
{
    m_eJustifyVert = alignment;
}

void PGUIOverlayLayout::SetForceSameHeight(bool force)
{
    m_bForceSameHeight = force;
}

void PGUIOverlayLayout::SetForceSameWidth(bool force)
{
    m_bForceSameWidth = force;
}

PPropertyValue PGUIOverlayLayout::Get_justifyvert_property() const
{
    return PPropertyValue((int)m_eJustifyVert);
}

void PGUIOverlayLayout::Set_justifyvert_property(const PPropertyValue& value)
{
    m_eJustifyVert = (Alignment)value.GetInteger();
}

PPropertyValue PGUIOverlayLayout::Get_justifyhoriz_property() const
{
    return PPropertyValue((int)m_eJustifyHoriz);
}

void PGUIOverlayLayout::Set_justifyhoriz_property(const PPropertyValue& value)
{
    m_eJustifyHoriz = (Alignment)value.GetInteger();
}

bool PGUIOverlayLayout::Val_fillvertical_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIOverlayLayout::Get_fillvertical_property() const
{
    return PPropertyValue(m_bFillVertical);
}

void PGUIOverlayLayout::Set_fillvertical_property(const PPropertyValue& value)
{
    m_bFillVertical = value.GetBoolean();
}

bool PGUIOverlayLayout::Val_fillhorizontal_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIOverlayLayout::Get_fillhorizontal_property() const
{
    return PPropertyValue(m_bFillHorizontal);
}

void PGUIOverlayLayout::Set_fillhorizontal_property(const PPropertyValue& value)
{
    m_bFillHorizontal = value.GetBoolean();
}

bool PGUIOverlayLayout::Val_sameheight_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIOverlayLayout::Get_sameheight_property() const
{
    return PPropertyValue(m_bForceSameHeight);
}

void PGUIOverlayLayout::Set_sameheight_property(const PPropertyValue& value)
{
    m_bForceSameHeight = value.GetBoolean();
}

bool PGUIOverlayLayout::Val_samewidth_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUIOverlayLayout::Get_samewidth_property() const
{
    return PPropertyValue(m_bForceSameWidth);
}

void PGUIOverlayLayout::Set_samewidth_property(const PPropertyValue& value)
{
    m_bForceSameWidth = value.GetBoolean();
}

Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIOverlayLayout::ms_oPropertySetOrdered;
Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIOverlayLayout::ms_oPropertySet;

const Toshi::TArray<Toshi::TGUIPropertySpec*>* PGUIOverlayLayout::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

const Toshi::TSortedArray<Toshi::TGUIPropertySpec*, Toshi::TGUIPropertySpec::Comparator>* PGUIOverlayLayout::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

bool PGUIOverlayLayout::Serialise(PProperties* properties)
{
    if (!TGUILayoutManager::Serialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIOverlayLayout::Deserialise(const PProperties* properties)
{
    if (!TGUILayoutManager::Deserialise(properties)) {
        return false;
    }
    return true;
}

bool PGUIOverlayLayout::Val_justifyhoriz_property(const PPropertyValue& value)
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

bool PGUIOverlayLayout::Val_justifyvert_property(const PPropertyValue& value)
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
