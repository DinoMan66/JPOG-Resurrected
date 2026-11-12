// Z:\Toshi\Source\TGUI - TGUISoundFactory. The original file name is not in the binary's strings.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUISoundFactory.h"

namespace Toshi {

TGUISoundFactory::TGUISoundFactory()
{
}

TGUISoundFactory::~TGUISoundFactory()
{
}

TClass TGUISoundFactory::m_sClass("TGUISoundFactory", &TObject::m_sClass, TGUISoundFactory::CreateObject,
                                  TGUISoundFactory::CreateObjectInPlace, TGUISoundFactory::InitialiseStatic,
                                  TGUISoundFactory::DeinitialiseStatic, 0x10000);

TClass& TGUISoundFactory::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUISoundFactory::DeinitialiseStatic()
{
}

void __stdcall TGUISoundFactory::InitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUISoundFactory::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUISoundFactory::CreateObject()
{
    return 0;
}

} // namespace Toshi
