// Z:\Toshi\Source\TGUI - TGUIEffectManager. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIEffectManager.h"

namespace Toshi {

TClass TGUIEffectManager::m_sClass("TGUIEffectManager", &TObject::m_sClass, TGUIEffectManager::CreateObject,
                                   TGUIEffectManager::CreateObjectInPlace, TGUIEffectManager::InitialiseStatic,
                                   TGUIEffectManager::DeinitialiseStatic, 0x10000);

TGUIEffectManager::~TGUIEffectManager()
{
}

TGUIEffectManager::TGUIEffectManager()
{
}

void __stdcall TGUIEffectManager::DeinitialiseStatic()
{
}

void __stdcall TGUIEffectManager::InitialiseStatic()
{
}

TClass& TGUIEffectManager::GetClass() const
{
    return m_sClass;
}

} // namespace Toshi
