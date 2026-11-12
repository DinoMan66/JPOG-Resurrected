// Z:\Toshi\Source\TGUI - TGUITextureAnimation. The original file name is not in the binary's strings.
// The constructors, the destructor, Clone and the bounding box functions are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureAnimation.h"
#include "TNewDelete.h"

namespace Toshi {

TClass TGUITextureAnimation::m_sClass("TGUITextureAnimation", &TGUITextureSection::m_sClass,
                                      TGUITextureAnimation::CreateObject, TGUITextureAnimation::CreateObjectInPlace,
                                      TGUITextureAnimation::InitialiseStatic, TGUITextureAnimation::DeinitialiseStatic,
                                      0x10000);

TClass& TGUITextureAnimation::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureAnimation::DeinitialiseStatic()
{
}

void __stdcall TGUITextureAnimation::InitialiseStatic()
{
}

TObject* __stdcall TGUITextureAnimation::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUITextureAnimation;
}

TObject* __stdcall TGUITextureAnimation::CreateObject()
{
    return new TGUITextureAnimation;
}

} // namespace Toshi
