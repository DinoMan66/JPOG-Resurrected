// Z:\Toshi\Source\TGUI\TGUILayoutManager.cpp - TGUILayoutInfo.
#define TGUIINTERFACE_EXPORTS
#include "TGUILayoutInfo.h"

namespace Toshi {

TGUILayoutInfo::TGUILayoutInfo(const TPCString& name, const TPCString& label, TArray<TGUIPropertySpec*>* properties)
    : m_oLayoutName(name), m_oLayoutLabel(label), m_paProperties(properties)
{
    m_pClass = TClass::Find(m_oLayoutName.GetCString().GetString(0), 0);
}

TGUILayoutInfo::~TGUILayoutInfo()
{
    if (IsLinked() == true) {
        GetList()->Remove(this);
    }
}

const TPCString& TGUILayoutInfo::GetLayoutName() const
{
    return m_oLayoutName;
}

const TPCString& TGUILayoutInfo::GetLayoutLabel() const
{
    return m_oLayoutLabel;
}

const TClass* TGUILayoutInfo::GetTClass() const
{
    return m_pClass;
}

int TGUILayoutInfo::GetPropertyCount() const
{
    return m_paProperties->Count();
}

const TGUIPropertySpec* TGUILayoutInfo::GetPropertyInfo(int index) const
{
    return (*m_paProperties)[index];
}

} // namespace Toshi
