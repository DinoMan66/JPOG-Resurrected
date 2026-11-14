// Z:\Toshi\Source\TGUI - TGUIComponentInfo. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#define SETCAP 6
#include "TGUIComponentInfo.h"

namespace Toshi {

TGUIComponentInfo::TGUIComponentInfo()
    : m_pClass(0)
    , m_aElementNames(3)
{
}

TGUIComponentInfo::~TGUIComponentInfo()
{
    if (IsLinked()) {
        GetList()->Remove(this);
    }
}

void TGUIComponentInfo::SetComponentName(const TPCString& name)
{
    m_oComponentName = name;
    m_pClass = TClass::Find(m_oComponentName.GetCString().GetString(0), 0);
}

void TGUIComponentInfo::SetComponentLabel(const TPCString& label)
{
    m_oComponentLabel = label;
}

void TGUIComponentInfo::AddElementName(const TPCString& name)
{
    m_aElementNames.AddEmpty() = name;
}

const TPCString& TGUIComponentInfo::GetComponentName() const
{
    return m_oComponentName;
}

const TPCString& TGUIComponentInfo::GetComponentLabel() const
{
    return m_oComponentLabel;
}

const TClass* TGUIComponentInfo::GetTClass() const
{
    return m_pClass;
}

} // namespace Toshi
