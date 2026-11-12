// Z:\Toshi\Source\TGUI - TGUIEffectManager's object factory functions.
// Kept in a second translation unit: the original calls the TGUIEffectManager constructor out of line from these,
// while the same-file definition in TGUIEffectManager.cpp would be expanded inline by the compiler.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIEffectManager.h"

namespace Toshi {

TObject* __stdcall TGUIEffectManager::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUIEffectManager;
}

TObject* __stdcall TGUIEffectManager::CreateObject()
{
    return new TGUIEffectManager;
}

} // namespace Toshi
