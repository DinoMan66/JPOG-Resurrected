// TGUIWidgetAction accessors. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TGUIWidgetAction.h"

namespace Toshi {

bool TGUIWidgetAction::IsEnabled() const
{
    return m_bEnabled;
}

void TGUIWidgetAction::SetEnabled(bool enabled)
{
    m_bEnabled = enabled;
}

int TGUIWidgetAction::GetCommandID() const
{
    return m_iCommandID;
}

int TGUIWidgetAction::GetDoodadID() const
{
    return m_iDoodadID;
}

} // namespace Toshi
