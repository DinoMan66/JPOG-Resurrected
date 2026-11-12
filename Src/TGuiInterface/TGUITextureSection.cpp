// Z:\Toshi\Source\TGUI - TGUITextureSection. The original file name is not in the binary's strings.
// The default constructor, the destructor, Assign and Clone are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TGUITextureSection.h"
#include "TNewDelete.h"

namespace Toshi {

TGUITextureSection::TGUITextureSection(const TGUITextureSection& other)
{
    Assign(other);
}

TClass TGUITextureSection::m_sClass("TGUITextureSection", &TObject::m_sClass, TGUITextureSection::CreateObject,
                                    TGUITextureSection::CreateObjectInPlace, TGUITextureSection::InitialiseStatic,
                                    TGUITextureSection::DeinitialiseStatic, 0x10000);

TClass& TGUITextureSection::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureSection::DeinitialiseStatic()
{
}

void __stdcall TGUITextureSection::InitialiseStatic()
{
}

TObject* __stdcall TGUITextureSection::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUITextureSection;
}

TObject* __stdcall TGUITextureSection::CreateObject()
{
    return new TGUITextureSection;
}

} // namespace Toshi
