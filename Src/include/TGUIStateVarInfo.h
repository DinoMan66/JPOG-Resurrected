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
    unsigned int m_uiStateBits;     // +0x04, the bits of a widget's state this variable sets
};

} // namespace Toshi
#endif
