// Toshi::TGUIMemory (TGuiInterface.dll): its only exported function is the compiler-generated operator=,
// so the class has no members that we know of.
#ifndef TGUIMEMORY_H
#define TGUIMEMORY_H
#include <stddef.h>
#include "TGUIAPI.h"

namespace Toshi {

class TGUI_API TGUIMemory
{
};

// Allocation and release for GUI objects (components, ...): they come from the GUI's own memory pile
// when it is enabled. TGUISetUseMemoryPile switches that on.
void* __stdcall TGUINew(unsigned int size);
void __stdcall TGUIDelete(void* memory);

} // namespace Toshi
#endif
