// Z:\Toshi\Source\TKernel\TObject.cpp - root of the Toshi class hierarchy.
#define TOSHI_API __declspec(dllexport)
#include <new.h>
#include <stdlib.h>
#include "TKernelObject.h"
#include "TMemory.h"

void* __cdecl operator new(size_t size)
{
    return tmalloc((int)size, 0, -1);
}

void __cdecl operator delete(void* p)
{
    tfree(p);
}

namespace Toshi {

TClass TObject::m_sClass("TObject", 0, TObject::CreateObject, TObject::CreateObjectInPlace,
                         TObject::InitialiseStatic, TObject::DeinitialiseStatic, 0x20000);

TClass& TObject::GetClass() const
{
    return m_sClass;
}

void TObject::Delete()
{
    delete this;
}

bool TObject::IsExactly(const TClass& cls) const
{
    if (&GetClass() != &cls)
    {
        return false;
    }
    return true;
}

bool TObject::IsA(const TClass& cls) const
{
    return GetClass().IsA(cls);
}

void __stdcall TObject::InitialiseStatic()
{
}

void __stdcall TObject::DeinitialiseStatic()
{
}

TObject* __stdcall TObject::CreateObjectInPlace(void* memory)
{
    return new (memory) TObject;
}

TObject* __stdcall TObject::CreateObject()
{
    return new TObject;
}

TObject::~TObject()
{
}

} // namespace Toshi
