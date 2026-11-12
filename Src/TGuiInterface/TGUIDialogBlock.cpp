// Z:\Toshi\Source\TGUI - TGUIDialogBlock. The original file name is not in the binary's strings.
// The constructor, Load and Save are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUIDialogBlock.h"

namespace Toshi {

TGUIDialogBlock::~TGUIDialogBlock()
{
}

TClass TGUIDialogBlock::m_sClass("TGUIDialogBlock", &PPropertyBlock::m_sClass, TGUIDialogBlock::CreateObject,
                                 TGUIDialogBlock::CreateObjectInPlace, TGUIDialogBlock::InitialiseStatic,
                                 TGUIDialogBlock::DeinitialiseStatic, 0x10000);

TClass& TGUIDialogBlock::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIDialogBlock::DeinitialiseStatic()
{
}

void __stdcall TGUIDialogBlock::InitialiseStatic()
{
}

// Blocks are created by the GUI interface, which passes itself to the constructor, so the factory functions create nothing
TObject* __stdcall TGUIDialogBlock::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIDialogBlock::CreateObject()
{
    return 0;
}

} // namespace Toshi
