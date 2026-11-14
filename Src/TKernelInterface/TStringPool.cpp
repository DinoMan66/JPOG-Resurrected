// Z:\Toshi\Source\TKernel\TCStringPool.cpp, TWStringPool.cpp - the pooled string tables (wrappers and constructors).
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TCString.h"
#include "TPString.h"
#include "TNewDelete.h"

namespace Toshi {

// ---- TCStringPool
TCStringPool::TCStringPool(const char* name, int a, int b)
{
    m_unk04 = 0;
    m_unk00 = a;
    m_unk08 = b;
    if (b > 0) {
        m_unk0C = new Entry[b];
    } else {
        m_unk0C = 0;
    }
    ReadFile(name);
}

TCStringPool::TCStringPool(int a, int b)
{
    m_unk04 = 0;
    m_unk00 = a;
    m_unk08 = b;
    if (b > 0) {
        m_unk0C = new Entry[b];
    } else {
        m_unk0C = 0;
    }
}

TPCString TCStringPool::Get(const TCString& s)
{
    return Get(s.GetString(0));
}

TPCString TCStringPool::Get(int i)
{
    TCString text;
    text.Format("%d", i);
    return Get(text);
}

TPCString TCStringPool::GetOptional(const TCString& s)
{
    return GetOptional(s.GetString(0));
}

TPCString TCStringPool::GetOptional(int i)
{
    TCString text;
    text.Format("%d", i);
    return GetOptional(text);
}

TPCString TCStringPool::GetVolatile(const TCString& s)
{
    return GetVolatile(s.GetString(0));
}

TPCString TCStringPool::GetVolatile(int i)
{
    TCString text;
    text.Format("%d", i);
    return GetVolatile(text);
}

bool TCStringPool::IsPresent(const TCString& s)
{
    return IsPresent(s.GetString(0));
}

bool TCStringPool::IsPresent(int i)
{
    TCString text;
    text.Format("%d", i);
    return IsPresent(text);
}

void TCStringPool::Dump() const
{
}

// ---- TWStringPool
TWStringPool::TWStringPool()
{
    m_unk04 = 0;
    m_unk00 = 0x80;
    m_unk08 = 0xfa0;
    m_unk0C = new Entry[0xfa0];
}

TPWString TWStringPool::Get(const TWString& s)
{
    return Get(s.GetString(0));
}

TPWString TWStringPool::Get(int i)
{
    TWString text;
    text.Format(L"%d", i);
    return Get(text);
}

TPWString TWStringPool::GetVolatile(const TWString& s)
{
    return GetVolatile(s.GetString(0));
}

TPWString TWStringPool::GetVolatile(int i)
{
    TWString text;
    text.Format(L"%d", i);
    return GetVolatile(text);
}

} // namespace Toshi
