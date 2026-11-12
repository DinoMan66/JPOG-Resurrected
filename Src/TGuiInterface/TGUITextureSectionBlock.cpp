// Z:\Toshi\Source\TGUI - TGUITextureSectionBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureSectionBlock.h"

namespace Toshi {

TGUITextureSectionBlock::~TGUITextureSectionBlock()
{
}

TClass TGUITextureSectionBlock::m_sClass("TGUITextureSectionBlock", &PPropertyBlock::m_sClass,
                                         TGUITextureSectionBlock::CreateObject,
                                         TGUITextureSectionBlock::CreateObjectInPlace,
                                         TGUITextureSectionBlock::InitialiseStatic,
                                         TGUITextureSectionBlock::DeinitialiseStatic, 0x10000);

TClass& TGUITextureSectionBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureSectionBlock::DeinitialiseStatic()
{
}

void __stdcall TGUITextureSectionBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUITextureSectionBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUITextureSectionBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
