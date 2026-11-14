// Z:\Toshi\Source\TGUI - TGUIDeserialisable. The original file name is not in the binary's strings.
// Deserialise, Serialise, Create, GetRequiredProperty, GetOptionalProperty and
// FindPropertyInfo are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIDeserialisable.h"
#include "TGUIPropertySpec.h"
#include "PPropertyValue.h"

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

bool TGUIDeserialisable::SetProperty(const TGUIPropertySpec* spec, const PPropertyValue& value)
{
    if (ValidatePropertyInfo(spec))
    {
        spec->set(this, value);
        return true;
    }
    return false;
}

bool TGUIDeserialisable::SetProperty(const TPCString& name, const PPropertyValue& value)
{
    const TGUIPropertySpec* spec = FindPropertyInfo(name);
    if (spec != 0)
    {
        spec->set(this, value);
        return true;
    }
    return false;
}

bool TGUIDeserialisable::ValidateProperty(const TPCString& name, const PPropertyValue& value) const
{
    const TGUIPropertySpec* spec = FindPropertyInfo(name);
    if (spec != 0)
    {
        return spec->validate(this, value);
    }
    return false;
}

// 'found' tells whether the property exists; a missing one yields an empty value
PPropertyValue TGUIDeserialisable::GetProperty(const TGUIPropertySpec* spec, bool& found) const
{
    if (ValidatePropertyInfo(spec))
    {
        found = true;
        return spec->get(this);
    }
    found = false;
    return PPropertyValue();
}

PPropertyValue TGUIDeserialisable::GetProperty(const TPCString& name, bool& found) const
{
    const TGUIPropertySpec* spec = FindPropertyInfo(name);
    if (spec != 0)
    {
        found = true;
        return spec->get(this);
    }
    found = false;
    return PPropertyValue();
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
