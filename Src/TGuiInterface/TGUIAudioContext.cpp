// Z:\Toshi\Source\TGUI - TGUIAudioContext. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIAudioContext.h"

namespace Toshi {

TGUIAudioContext::TGUIAudioContext()
{
}

TGUIAudioContext::~TGUIAudioContext()
{
}

TClass TGUIAudioContext::m_sClass("TGUIAudioContext", &TObject::m_sClass, TGUIAudioContext::CreateObject,
                                  TGUIAudioContext::CreateObjectInPlace, TGUIAudioContext::InitialiseStatic,
                                  TGUIAudioContext::DeinitialiseStatic, 0x10000);

TClass& TGUIAudioContext::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIAudioContext::DeinitialiseStatic()
{
}

void __stdcall TGUIAudioContext::InitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUIAudioContext::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIAudioContext::CreateObject()
{
    return 0;
}

} // namespace Toshi
