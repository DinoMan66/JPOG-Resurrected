// Z:\Toshi\Source\TGUI - TGUIWidget, property validation. The original file name is not in the binary's strings.
// Property validation, kept apart from TGUIWidget.cpp.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIWidget.h"
#include "TGUIStyle.h"
#include "TGUIPropertySpec.h"

namespace Toshi {

// A widget accepts the properties of its own class chain and those of the styles
bool TGUIWidget::ValidatePropertyInfo(const TGUIPropertySpec* info) const
{
    if (info != 0) {
        if (GetClass().IsA(*info->GetSourceClass())) {
            return true;
        }
        if (info->GetSourceClass()->IsA(TGUIStyle::m_sClass)) {
            return true;
        }
    }
    return false;
}

} // namespace Toshi
