// Z:\Toshi\Source\TGUI - TGUIFontBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIFontBlock.h"

namespace Toshi {

TGUIFontBlock::~TGUIFontBlock()
{
}

TClass TGUIFontBlock::m_sClass("TGUIFontBlock", &PPropertyBlock::m_sClass, TGUIFontBlock::CreateObject,
                               TGUIFontBlock::CreateObjectInPlace, TGUIFontBlock::InitialiseStatic,
                               TGUIFontBlock::DeinitialiseStatic, 0x10000);

TClass& TGUIFontBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIFontBlock::DeinitialiseStatic()
{
}

void __stdcall TGUIFontBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUIFontBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIFontBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
