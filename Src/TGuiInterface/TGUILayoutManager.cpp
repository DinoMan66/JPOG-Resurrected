// Z:\Toshi\Source\TGUI - TGUILayoutManager. The original file name is not in the binary's strings.
// The default constructor is still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUILayoutManager.h"

namespace Toshi {

TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>* TGUILayoutManager::ms_oPropertySetOrdered;
TArray<TGUIPropertySpec*>* TGUILayoutManager::ms_oPropertySet;

TGUILayoutManager::TGUILayoutManager(const TGUILayoutManager& other)
    : TGUIDeserialisable(other), m_pInterface(other.m_pInterface), m_pLayoutInfo(other.m_pLayoutInfo)
{
}

TGUILayoutManager::~TGUILayoutManager()
{
}

bool TGUILayoutManager::Serialise(PProperties* properties)
{
    if (!TGUIDeserialisable::Serialise(properties))
    {
        return false;
    }
    return true;
}

bool TGUILayoutManager::Deserialise(const PProperties* properties)
{
    if (!TGUIDeserialisable::Deserialise(properties))
    {
        return false;
    }
    return true;
}

TClass TGUILayoutManager::m_sClass("TGUILayoutManager", &TGUIDeserialisable::m_sClass, TGUILayoutManager::CreateObject,
                                   TGUILayoutManager::CreateObjectInPlace, TGUILayoutManager::InitialiseStatic,
                                   TGUILayoutManager::DeinitialiseStatic, 0x10000);

TClass& TGUILayoutManager::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUILayoutManager::DeinitialiseStatic()
{
    for (TArray<TGUIPropertySpec*>::Iterator it(*ms_oPropertySet); it.IsValid(); ++it) {
        delete *it;
    }
    delete ms_oPropertySet;
    delete ms_oPropertySetOrdered;
    ms_oPropertySet = 0;
    ms_oPropertySetOrdered = 0;
}

void __stdcall TGUILayoutManager::InitialiseStatic()
{
    ms_oPropertySet = new TArray<TGUIPropertySpec*>;
    ms_oPropertySetOrdered = new TSortedArray<TGUIPropertySpec*, TGUIPropertySpec::Comparator>;
}

// TGUILayoutManager is abstract, so its factory functions create nothing
TObject* __stdcall TGUILayoutManager::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUILayoutManager::CreateObject()
{
    return 0;
}

} // namespace Toshi
