// Z:\Toshi\Source\TKernel\TCString.cpp - copy/convert constructors, destructors and everything that
// returns a string by value (operator+, Mid).
// Kept in their own translation unit: the original calls the out-of-line Reset() from the copy and
// convert constructors, while the default and sized constructors (TCString.cpp) assign the fields
// themselves. The by-value functions live here too, because the original inlines the copy/convert
// constructor (Reset() + Copy()) and the destructor (FreeBuffer()) into them; that only happens when
// those are defined in the same file.
#define TOSHI_API __declspec(dllexport)
#include <string.h>
#include "TKernelMisc.h"
#include "TCString.h"
#include "TMemory.h"

namespace Toshi {

// ---- TCString

TCString::TCString(const TWString& rhs)
{
    Reset();
    Copy(rhs, -1);
}

TCString::TCString(const TCString& rhs)
{
    Reset();
    Copy(rhs, -1);
}

TCString::TCString(const TWChar* s)
{
    Reset();
    Copy(s, -1);
}

TCString::TCString(const char* s)
{
    Reset();
    Copy(s, -1);
}

TCString::~TCString()
{
    FreeBuffer();
}

TCString TCString::Mid(int start, int len) const
{
    if (start < 0) {
        start = 0;
    } else if (start >= m_iStrLen) {
        return TCString();
    }
    if (len < 0 || start + len > m_iStrLen) {
        len = m_iStrLen - start;
    }
    TCString part(len);
    TSystem::MemCopy(part.m_pBuffer, m_pBuffer + start, len);
    part.m_pBuffer[len] = 0;
    return part;
}

// There is no Concat for a C or wide string here: the right operand is converted to a TCString first.
TCString TCString::operator+(const char* s) const
{
    TCString result(*this);
    result.Concat(TCString(s), -1);
    return result;
}

TCString TCString::operator+(const TWChar* s) const
{
    TCString result(*this);
    result.Concat(TCString(s), -1);
    return result;
}

TCString TCString::operator+(const TWString& s) const
{
    TCString result(*this);
    result.Concat(s, -1);
    return result;
}

TCString TCString::operator+(const TCString& s) const
{
    TCString result(*this);
    result.Concat(s, -1);
    return result;
}

TCString __stdcall operator+(const char* a, const TCString& b)
{
    TCString result(a);
    result.Concat(b, -1);
    return result;
}

// ---- TWString

TWString::TWString(const TCString& rhs)
{
    Reset();
    Copy(rhs, -1);
}

TWString::TWString(const TWString& rhs)
{
    Reset();
    Copy(rhs, -1);
}

TWString::TWString(const char* s)
{
    Reset();
    Copy(s, -1);
}

TWString::TWString(const TWChar* s)
{
    Reset();
    Copy(s, -1);
}

TWString::~TWString()
{
    FreeBuffer();
}

TWString TWString::Mid(int start, int len) const
{
    if (start < 0) {
        start = 0;
    } else if ((unsigned int)start >= m_iStrLen) {
        return TWString();
    }
    if (len < 0 || (unsigned int)(start + len) > m_iStrLen) {
        len = m_iStrLen - start;
    }
    TWString part(len);
    wcsncpy((wchar_t*)part.m_pBuffer, (const wchar_t*)(m_pBuffer + start), len);
    part.m_pBuffer[len] = 0;
    return part;
}

TWString TWString::operator+(const TWChar* s) const
{
    TWString result(*this);
    result.Concat(s, -1);
    return result;
}

TWString TWString::operator+(const TWString& s) const
{
    TWString result(*this);
    result.Concat(s, -1);
    return result;
}

TWString __stdcall operator+(const TWChar* a, const TWString& b)
{
    TWString result(a);
    result.Concat(b, -1);
    return result;
}

// ---- TWString

void TWString::Copy(const TCString& s, int len)
{
    if (len > s.Length() || len == -1) {
        len = s.Length();
    }
    AllocBuffer(len, true);
    TSystem::StringCharToUnicode(m_pBuffer, (const char*)s, len);
    m_pBuffer[len] = 0;
}

} // namespace Toshi
