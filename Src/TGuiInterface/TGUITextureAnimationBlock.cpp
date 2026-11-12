// Z:\Toshi\Source\TGUI - TGUITextureAnimationBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureAnimationBlock.h"

namespace Toshi {

TGUITextureAnimationBlock::~TGUITextureAnimationBlock()
{
}

TClass TGUITextureAnimationBlock::m_sClass("TGUITextureAnimationBlock", &PPropertyBlock::m_sClass,
                                           TGUITextureAnimationBlock::CreateObject,
                                           TGUITextureAnimationBlock::CreateObjectInPlace,
                                           TGUITextureAnimationBlock::InitialiseStatic,
                                           TGUITextureAnimationBlock::DeinitialiseStatic, 0x10000);

TClass& TGUITextureAnimationBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureAnimationBlock::DeinitialiseStatic()
{
}

void __stdcall TGUITextureAnimationBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUITextureAnimationBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUITextureAnimationBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
