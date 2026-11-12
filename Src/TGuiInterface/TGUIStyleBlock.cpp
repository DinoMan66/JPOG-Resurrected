// Z:\Toshi\Source\TGUI - TGUIStyleBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIStyleBlock.h"

namespace Toshi {

TGUIStyleBlock::~TGUIStyleBlock()
{
}

TClass TGUIStyleBlock::m_sClass("TGUIStyleBlock", &PPropertyBlock::m_sClass, TGUIStyleBlock::CreateObject,
                                TGUIStyleBlock::CreateObjectInPlace, TGUIStyleBlock::InitialiseStatic,
                                TGUIStyleBlock::DeinitialiseStatic, 0x10000);

TClass& TGUIStyleBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIStyleBlock::DeinitialiseStatic()
{
}

void __stdcall TGUIStyleBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUIStyleBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIStyleBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
