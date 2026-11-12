// Z:\Toshi\Source\TGUI - TGUITextureFactory. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUITextureFactory.h"

namespace Toshi {

TGUITextureFactory::TGUITextureFactory()
{
}

TGUITextureFactory::~TGUITextureFactory()
{
}

TClass TGUITextureFactory::m_sClass("TGUITextureFactory", &TObject::m_sClass, TGUITextureFactory::CreateObject,
                                    TGUITextureFactory::CreateObjectInPlace, TGUITextureFactory::InitialiseStatic,
                                    TGUITextureFactory::DeinitialiseStatic, 0x10000);

TClass& TGUITextureFactory::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUITextureFactory::DeinitialiseStatic()
{
}

void __stdcall TGUITextureFactory::InitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUITextureFactory::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUITextureFactory::CreateObject()
{
    return 0;
}

} // namespace Toshi
