// Toshi::TGUIStateVarInfo (TGuiInterface.dll): one state variable of a widget class, kept by
// TGUIWidgetInfo in a sorted array. 8 bytes; the destructor only releases the name.
#ifndef TGUISTATEVARINFO_H
#define TGUISTATEVARINFO_H
#include "TGUIAPI.h"
#include "TPString.h"

namespace Toshi {

class TGUIStateVarInfo
{
public:
    struct Comparator;      // orders the variables in TGUIWidgetInfo's set

    TPCString m_oName;      // +0x00
    /* 0x04 */ int m_unk04;
};

} // namespace Toshi
#endif
