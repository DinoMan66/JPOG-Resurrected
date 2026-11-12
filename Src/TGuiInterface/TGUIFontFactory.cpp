// Z:\Toshi\Source\TGUI - TGUIFontFactory. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIFontFactory.h"

namespace Toshi {

TGUIFontFactory::TGUIFontFactory()
{
}

TGUIFontFactory::~TGUIFontFactory()
{
}

TClass TGUIFontFactory::m_sClass("TGUIFontFactory", &TObject::m_sClass, TGUIFontFactory::CreateObject,
                                 TGUIFontFactory::CreateObjectInPlace, TGUIFontFactory::InitialiseStatic,
                                 TGUIFontFactory::DeinitialiseStatic, 0x10000);

TClass& TGUIFontFactory::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIFontFactory::DeinitialiseStatic()
{
}

void __stdcall TGUIFontFactory::InitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUIFontFactory::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIFontFactory::CreateObject()
{
    return 0;
}

} // namespace Toshi
