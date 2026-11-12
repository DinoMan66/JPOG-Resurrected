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

} // namespace Toshi
