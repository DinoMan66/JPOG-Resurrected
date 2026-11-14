// Z:\Toshi\Source\TGUI - TGUIWidgetInfo. The original file name is not in the binary's strings.
// The state variable functions and the property lookups are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIWidgetInfo.h"

namespace Toshi {

TGUIWidgetInfo::TGUIWidgetInfo()
    : m_pClass(0), m_oStateVars(10)
{
    m_pProperties = 0;
    m_uiInputActions = 0;
    m_bConcrete = false;
}

TGUIWidgetInfo::~TGUIWidgetInfo()
{
    if (IsLinked() == true) {
        GetList()->Remove(this);
    }
}

// The widget class is looked up by the widget's name
void TGUIWidgetInfo::SetWidgetName(const TPCString& name)
{
    m_oWidgetName = name;
    m_pClass = TClass::Find(m_oWidgetName.GetCString().GetString(0), 0);
}

// Index of the component name in this widget's component list, or -1
int TGUIWidgetInfo::GetComponentIndex(const TPCString& name) const
{
    for (int i = 0; i < GetComponentCount(); i++) {
        if (GetComponentName(i) == name) {
            return i;
        }
    }
    return -1;
}

const TGUIStateVarInfo* TGUIWidgetInfo::GetStateVarInfo(const TPCString& name) const
{
    for (int i = 0; i < GetStateVarCount(); i++) {
        if (name == m_oStateVars[i].m_oName) {
            return &m_oStateVars[i];
        }
    }
    return 0;
}

unsigned int TGUIWidgetInfo::GetStateVarMask(const TPCString& name) const
{
    for (int i = 0; i < GetStateVarCount(); i++) {
        if (name == m_oStateVars[i].m_oName) {
            return m_oStateVars[i].m_uiStateBits;
        }
    }
    return 0;
}

} // namespace Toshi
