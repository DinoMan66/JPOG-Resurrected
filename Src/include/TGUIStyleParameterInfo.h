// Toshi::TGUIStyleParameterInfo - one parameter a GUI style hands to the widgets that use it (TGuiInterface.dll).
// A style keeps an array of these, one per parameter (TGUIStyle::GetParameterInfo). Only the fields
// TGUIStyle::FindParameter, IsCompatibleWith and TGUIWidget::GetPropertyInfo read are placed so far.
#ifndef TGUISTYLEPARAMETERINFO_H
#define TGUISTYLEPARAMETERINFO_H
#include "TGUIAPI.h"
#include "TObject.h"
#include "TPString.h"

namespace Toshi {

class TGUIPropertySpec;

class TGUI_API TGUIStyleParameterInfo
{
public:
    /* 0x00 */ int m_unk00;
    TPCString m_oName;                          // +0x04, the parameter's name (TGUIStyle::FindParameter)
    /* 0x08 */ const TClass* m_pType;               // value type, TYPE_UNDEF accepts any
    int m_iIndex;                               // +0x0C, the parameter's position in the style
    /* 0x10 */ const TGUIPropertySpec* m_pPropertySpec;
};

} // namespace Toshi
#endif
