// Z:\Toshi\Source\TGUI - TGUIStringBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIStringBlock.h"

namespace Toshi {

TGUIStringBlock::~TGUIStringBlock()
{
}

TClass TGUIStringBlock::m_sClass("TGUIStringBlock", &PPropertyBlock::m_sClass, TGUIStringBlock::CreateObject,
                                 TGUIStringBlock::CreateObjectInPlace, TGUIStringBlock::InitialiseStatic,
                                 TGUIStringBlock::DeinitialiseStatic, 0x10000);

TClass& TGUIStringBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIStringBlock::DeinitialiseStatic()
{
}

void __stdcall TGUIStringBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUIStringBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIStringBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
