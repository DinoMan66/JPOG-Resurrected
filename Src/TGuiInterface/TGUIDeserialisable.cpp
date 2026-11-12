// Z:\Toshi\Source\TGUI - TGUIDeserialisable. The original file name is not in the binary's strings.
// Deserialise, Serialise, Create, Set/GetProperty, GetRequiredProperty, GetOptionalProperty and
// FindPropertyInfo are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIDeserialisable.h"
#include "TGUIPropertySpec.h"

namespace Toshi {

TGUIDeserialisable::TGUIDeserialisable()
{
}

TGUIDeserialisable::~TGUIDeserialisable()
{
}

int TGUIDeserialisable::GetPropertyCount() const
{
    return GetPropertyInfoSet()->Count();
}

const TGUIPropertySpec* TGUIDeserialisable::GetPropertyInfo(int index) const
{
    return (*GetPropertyInfoSet())[index];
}

bool TGUIDeserialisable::ValidatePropertyInfo(const TGUIPropertySpec* info) const
{
    return info != 0 && GetClass().IsA(*info->GetSourceClass());
}

TClass TGUIDeserialisable::m_sClass("TGUIDeserialisable", &TObject::m_sClass, TGUIDeserialisable::CreateObject,
                                    TGUIDeserialisable::CreateObjectInPlace, TGUIDeserialisable::InitialiseStatic,
                                    TGUIDeserialisable::DeinitialiseStatic, 0x10000);

TClass& TGUIDeserialisable::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIDeserialisable::DeinitialiseStatic()
{
}

void __stdcall TGUIDeserialisable::InitialiseStatic()
{
}

// The class is abstract, so the factory functions create nothing
TObject* __stdcall TGUIDeserialisable::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIDeserialisable::CreateObject()
{
    return 0;
}

} // namespace Toshi
