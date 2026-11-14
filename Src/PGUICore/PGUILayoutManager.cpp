// PGUILayoutManager property accessors. The original file name is not in the binary's strings.
#define PGUICORE_EXPORTS
#include "PGUILayoutManager.h"
#include "PPropertyValue.h"

namespace Toshi {

TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* PGUILayoutManager::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* PGUILayoutManager::ms_oPropertySet;
TGUILayoutInfo* PGUILayoutManager::ms_layout_info;

PGUILayoutManager::PGUILayoutManager()
{
    m_sPadX = 0;
    m_sPadY = 0;
    m_bForceSameWidth = false;
    m_bForceSameHeight = false;
    m_bFillHorizontal = true;
    m_bFillVertical = true;
    m_pLayoutInfo = ms_layout_info;
}

PGUILayoutManager::PGUILayoutManager(const PGUILayoutManager& other)
    : TGUILayoutManager(other)
{
    m_sPadX = other.m_sPadX;
    m_sPadY = other.m_sPadY;
    m_bForceSameWidth = other.m_bForceSameWidth;
    m_bForceSameHeight = other.m_bForceSameHeight;
    m_bFillHorizontal = other.m_bFillHorizontal;
    m_bFillVertical = other.m_bFillVertical;
    m_pLayoutInfo = ms_layout_info;
}

bool PGUILayoutManager::GetForceSameHeight() const
{
    return m_bForceSameHeight;
}

bool PGUILayoutManager::GetForceSameWidth() const
{
    return m_bForceSameWidth;
}

int PGUILayoutManager::GetPadY() const
{
    return m_sPadY;
}

int PGUILayoutManager::GetPadX() const
{
    return m_sPadX;
}

void PGUILayoutManager::SetForceSameHeight(bool force)
{
    m_bForceSameHeight = force;
}

void PGUILayoutManager::SetForceSameWidth(bool force)
{
    m_bForceSameWidth = force;
}

void PGUILayoutManager::SetPad(int padX, int padY)
{
    m_sPadX = padX;
    m_sPadY = padY;
}

void PGUILayoutManager::SetPadY(int padY)
{
    m_sPadY = padY;
}

void PGUILayoutManager::SetPadX(int padX)
{
    m_sPadX = padX;
}

const TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* PGUILayoutManager::GetPropertyInfoOrderedSet() const
{
    return ms_oPropertySetOrdered;
}

const TArray<TGUIPropertySpec*>* PGUILayoutManager::GetPropertyInfoSet() const
{
    return ms_oPropertySet;
}

bool PGUILayoutManager::Val_fillvertical_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUILayoutManager::Get_fillvertical_property() const
{
    return PPropertyValue(m_bFillVertical);
}

void PGUILayoutManager::Set_fillvertical_property(const PPropertyValue& value)
{
    m_bFillVertical = value.GetBoolean();
}

bool PGUILayoutManager::Val_fillhorizontal_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUILayoutManager::Get_fillhorizontal_property() const
{
    return PPropertyValue(m_bFillHorizontal);
}

void PGUILayoutManager::Set_fillhorizontal_property(const PPropertyValue& value)
{
    m_bFillHorizontal = value.GetBoolean();
}

bool PGUILayoutManager::Val_sameheight_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUILayoutManager::Get_sameheight_property() const
{
    return PPropertyValue(m_bForceSameHeight);
}

void PGUILayoutManager::Set_sameheight_property(const PPropertyValue& value)
{
    m_bForceSameHeight = value.GetBoolean();
}

bool PGUILayoutManager::Val_samewidth_property(const PPropertyValue& value)
{
    return value.CanBeType(PPropertyValue::TYPE_BOOL);
}

PPropertyValue PGUILayoutManager::Get_samewidth_property() const
{
    return PPropertyValue(m_bForceSameWidth);
}

void PGUILayoutManager::Set_samewidth_property(const PPropertyValue& value)
{
    m_bForceSameWidth = value.GetBoolean();
}

PPropertyValue PGUILayoutManager::Get_pady_property() const
{
    return PPropertyValue((int)m_sPadY);
}

void PGUILayoutManager::Set_pady_property(const PPropertyValue& value)
{
    m_sPadY = (short)value.GetInteger();
}

PPropertyValue PGUILayoutManager::Get_padx_property() const
{
    return PPropertyValue((int)m_sPadX);
}

void PGUILayoutManager::Set_padx_property(const PPropertyValue& value)
{
    m_sPadX = (short)value.GetInteger();
}


bool PGUILayoutManager::Val_padx_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    return value.GetInteger() >= 0;
}

bool PGUILayoutManager::Val_pady_property(const PPropertyValue& value)
{
    if (!value.CanBeType(PPropertyValue::TYPE_INT)) {
        return false;
    }
    return value.GetInteger() >= 0;
}

TObject* __stdcall PGUILayoutManager::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall PGUILayoutManager::CreateObject()
{
    return 0;
}

} // namespace Toshi
