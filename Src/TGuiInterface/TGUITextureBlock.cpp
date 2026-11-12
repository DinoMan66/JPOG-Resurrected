// Z:\Toshi\Source\TGUI - TGUITextureBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureBlock.h"

namespace Toshi {

TGUITextureBlock::~TGUITextureBlock()
{
}

TClass TGUITextureBlock::m_sClass("TGUITextureBlock", &PPropertyBlock::m_sClass, TGUITextureBlock::CreateObject,
                                  TGUITextureBlock::CreateObjectInPlace, TGUITextureBlock::InitialiseStatic,
                                  TGUITextureBlock::DeinitialiseStatic, 0x10000);

TClass& TGUITextureBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureBlock::DeinitialiseStatic()
{
}

void __stdcall TGUITextureBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUITextureBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUITextureBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
