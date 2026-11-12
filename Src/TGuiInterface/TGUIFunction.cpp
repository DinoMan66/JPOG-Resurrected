// Z:\Toshi\Source\TGUI - the TGUIFunction classes. The original file name is not in the binary's strings;
// the code sits just before TGUIEffectManager in the DLL. Serialise and Deserialise are still to do.
#define TGUIINTERFACE_EXPORTS
#include "TNewDelete.h"
#include "TGUIFunction.h"

namespace Toshi {

// ---- TGUIFunction (abstract)

TClass TGUIFunction::m_sClass("TGUIFunction", &TObject::m_sClass, TGUIFunction::CreateObject,
                              TGUIFunction::CreateObjectInPlace, TGUIFunction::InitialiseStatic,
                              TGUIFunction::DeinitialiseStatic, 0x10000);

TClass& TGUIFunction::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIFunction::DeinitialiseStatic()
{
}

void __stdcall TGUIFunction::InitialiseStatic()
{
}

TObject* __stdcall TGUIFunction::CreateObjectInPlace(void* memory)
{
    return 0;
}

TObject* __stdcall TGUIFunction::CreateObject()
{
    return 0;
}

// ---- TGUIConstantFunction

TClass TGUIConstantFunction::m_sClass("TGUIConstantFunction", &TGUIFunction::m_sClass, TGUIConstantFunction::CreateObject,
                                      TGUIConstantFunction::CreateObjectInPlace, TGUIConstantFunction::InitialiseStatic,
                                      TGUIConstantFunction::DeinitialiseStatic, 0x10000);

TClass& TGUIConstantFunction::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUIConstantFunction::DeinitialiseStatic()
{
}

void __stdcall TGUIConstantFunction::InitialiseStatic()
{
}

TObject* __stdcall TGUIConstantFunction::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUIConstantFunction;
}

TObject* __stdcall TGUIConstantFunction::CreateObject()
{
    return new TGUIConstantFunction;
}

// ---- TGUISineFunction

TClass TGUISineFunction::m_sClass("TGUISineFunction", &TGUIFunction::m_sClass, TGUISineFunction::CreateObject,
                                  TGUISineFunction::CreateObjectInPlace, TGUISineFunction::InitialiseStatic,
                                  TGUISineFunction::DeinitialiseStatic, 0x10000);

TClass& TGUISineFunction::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUISineFunction::DeinitialiseStatic()
{
}

void __stdcall TGUISineFunction::InitialiseStatic()
{
}

TObject* __stdcall TGUISineFunction::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUISineFunction;
}

TObject* __stdcall TGUISineFunction::CreateObject()
{
    return new TGUISineFunction;
}

// ---- TGUISawtoothFunction

TClass TGUISawtoothFunction::m_sClass("TGUISawtoothFunction", &TGUIFunction::m_sClass, TGUISawtoothFunction::CreateObject,
                                      TGUISawtoothFunction::CreateObjectInPlace, TGUISawtoothFunction::InitialiseStatic,
                                      TGUISawtoothFunction::DeinitialiseStatic, 0x10000);

TClass& TGUISawtoothFunction::GetClass() const
{
    return m_sClass;
}

void __stdcall TGUISawtoothFunction::DeinitialiseStatic()
{
}

void __stdcall TGUISawtoothFunction::InitialiseStatic()
{
}

TObject* __stdcall TGUISawtoothFunction::CreateObjectInPlace(void* memory)
{
    return new (memory) TGUISawtoothFunction;
}

TObject* __stdcall TGUISawtoothFunction::CreateObject()
{
    return new TGUISawtoothFunction;
}

} // namespace Toshi
