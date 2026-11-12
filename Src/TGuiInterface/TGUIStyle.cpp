// Z:\Toshi\Source\TGUI - TGUIStyle. The original file name is not in the binary's strings.
// Only the accessors and the class boilerplate are written so far; the constructor is still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIStyle.h"

namespace Toshi {

TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUIStyle::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUIStyle::ms_oPropertySet;

TClass TGUIStyle::m_sClass("TGUIStyle", &TGUIDeserialisable::m_sClass, TGUIStyle::CreateObject,
                           TGUIStyle::CreateObjectInPlace, TGUIStyle::InitialiseStatic,
                           TGUIStyle::DeinitialiseStatic, 0x10000);

TClass& TGUIStyle::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIStyle::DeinitialiseStatic()
{
    for (TArray<TGUIPropertySpec*>::Iterator it(*ms_oPropertySet); it.IsValid(); ++it) {
        delete *it;
    }
    delete ms_oPropertySet;
    delete ms_oPropertySetOrdered;
    ms_oPropertySet = 0;
    ms_oPropertySetOrdered = 0;
}

void __stdcall TGUIStyle::InitialiseStatic()
{
}

TObject* __stdcall TGUIStyle::CreateObjectInPlace(void* memory)
{
    return memory ? new (memory) TGUIStyle : 0;
}

TObject* __stdcall TGUIStyle::CreateObject()
{
    return new TGUIStyle;
}

} // namespace Toshi
