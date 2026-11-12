// Z:\Toshi\Source\TKernel\TCString.cpp - narrow string. Only the simple members are written.
// Layout: buffer pointer, then a 24-bit length and an 8-bit excess length (see TCString.h).
#define TOSHI_API __declspec(dllexport)
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "TKernelMisc.h"
#include "TCString.h"
#include "TMemory.h"

namespace Toshi {

int TCString::Length() const
{
    return m_iStrLen;
}

int TCString::ExcessLength() const
{
    return m_iExcess;
}

bool TCString::IsEmpty() const
{
    if (m_iStrLen == 0) {
        return true;
    }
    return false;
}

bool TCString::IsIndexValid(int i) const
{
    if (i > (int)m_iStrLen || i < 0) {
        return false;
    }
    return true;
}

void TCString::Reset()
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
}

TCString::TCString()
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
    AllocBuffer(0, true);
}

TCString::TCString(int reserve)
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
    AllocBuffer(reserve, true);
}

TWString::TWString()
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
    AllocBuffer(0, true);
}

TWString::TWString(int reserve)
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
    AllocBuffer(reserve, true);
}

void TCString::UndoForceSetData()
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
}

void TCString::FreeBuffer()
{
    if (m_iStrLen > 0) {
        tfree(m_pBuffer);
        m_pBuffer = 0;
    }
    Reset();
}

const TCString& TCString::Print() const
{
    return *this;
}

bool TCString::IsUnicode() const
{
    return false;
}

const char* TCString::GetString(int index) const
{
    if (!IsIndexValid(index)) {
        return 0;
    }
    return m_pBuffer + index;
}

TCString& TCString::MakeLower()
{
    if (m_pBuffer) {
        m_pBuffer = _strlwr(m_pBuffer);
    }
    return *this;
}

TCString& TCString::MakeUpper()
{
    if (m_pBuffer) {
        m_pBuffer = _strupr(m_pBuffer);
    }
    return *this;
}

bool TCString::IsAllLowerCase() const
{
    unsigned int len = m_iStrLen;
    if (len != 0) {
        const char* p = m_pBuffer;
        const char* end = p + len;
        do {
            char c = *p++;
            if (c >= 'A' && c <= 'Z') {
                return false;
            }
        } while (p < end);
    }
    return true;
}

bool TCString::IsAllUpperCase() const
{
    unsigned int len = m_iStrLen;
    if (len != 0) {
        const char* p = m_pBuffer;
        const char* end = p + len;
        do {
            char c = *p++;
            if (c >= 'a' && c <= 'z') {
                return false;
            }
        } while (p < end);
    }
    return true;
}

int TCString::Compare(const char* s, int len) const
{
    if (len != -1) {
        return strncmp(GetString(0), s, len);
    }
    return strcmp(GetString(0), s);
}

int TCString::CompareNoCase(const char* s, int len) const
{
    if (len != -1) {
        return _strnicmp(GetString(0), s, len);
    }
    return _stricmp(GetString(0), s);
}

int TWString::Length() const
{
    return m_iStrLen;
}

int TWString::ExcessLength() const
{
    return m_iExcess;
}

bool TWString::IsEmpty() const
{
    if (m_iStrLen == 0) {
        return true;
    }
    return false;
}

bool TWString::IsIndexValid(int i) const
{
    if (i > (int)m_iStrLen || i < 0) {
        return false;
    }
    return true;
}

void TWString::Reset()
{
    m_pBuffer = m_aNull;
    m_iStrLen = 0;
    m_iExcess = 0;
}

void TWString::FreeBuffer()
{
    if (m_iStrLen > 0) {
        tfree(m_pBuffer);
        m_pBuffer = 0;
    }
    Reset();
}

bool TWString::IsUnicode() const
{
    return true;
}

const TWChar* TWString::GetString(int index) const
{
    if (!IsIndexValid(index)) {
        return 0;
    }
    return m_pBuffer + index;
}

TWString& TWString::MakeLower()
{
    if (m_pBuffer) {
        _wcslwr((wchar_t*)m_pBuffer);
    }
    return *this;
}

TWString& TWString::MakeUpper()
{
    if (m_pBuffer) {
        _wcsupr((wchar_t*)m_pBuffer);
    }
    return *this;
}

int TWString::Compare(const TWChar* s, int len) const
{
    if (len != -1) {
        return wcsncmp((const wchar_t*)GetString(0), (const wchar_t*)s, len);
    }
    return wcscmp((const wchar_t*)GetString(0), (const wchar_t*)s);
}

int TWString::CompareNoCase(const TWChar* s, int len) const
{
    if (len != -1) {
        return _wcsnicmp((const wchar_t*)GetString(0), (const wchar_t*)s, len);
    }
    return _wcsicmp((const wchar_t*)GetString(0), (const wchar_t*)s);
}


// ---- allocation and searching
bool TCString::AllocBuffer(int len, bool freeOld)
{
    bool reallocated;
    int oldLen = m_iStrLen;
    if (len == oldLen) {
        reallocated = false;
    } else {
        if (len == 0) {
            if (freeOld == true) {
                tfree(m_pBuffer);
            }
            m_pBuffer = m_aNull;
            reallocated = true;
            m_iExcess = 0;
        } else {
            // The spare capacity left over after the resize; reallocate when it leaves 0..255.
            int excess = (oldLen - len) + m_iExcess;
            if (excess < 0 || excess > 255) {
                if (oldLen > 0 && freeOld == true) {
                    tfree(m_pBuffer);
                }
                m_pBuffer = (char*)tmalloc(len + 1, 0, -1);
                reallocated = true;
                m_iExcess = 0;
            } else {
                m_iExcess = excess;
                reallocated = false;
            }
        }
        m_iStrLen = len;
    }
    if (freeOld == true) {
        *m_pBuffer = 0;
    }
    return reallocated;
}

int TCString::Find(char c, int start) const
{
    if (!IsIndexValid(start)) {
        return -1;
    }
    char* found = strchr(GetString(0) + start, c);
    int result;
    if (found == 0) {
        result = -1;
    } else {
        result = found - GetString(0);
    }
    return result;
}

int TCString::Find(const char* s, int start) const
{
    if (!IsIndexValid(start)) {
        return -1;
    }
    char* found = strstr(GetString(0) + start, s);
    int result;
    if (found == 0) {
        result = -1;
    } else {
        result = found - GetString(0);
    }
    return result;
}

void TCString::Truncate(int len)
{
    int oldLen = m_iStrLen;
    if (len > oldLen) {
        len = oldLen;
    }
    char* oldBuffer = m_pBuffer;
    bool reallocated = AllocBuffer(len, false);
    if (reallocated == true) {
        TSystem::StringCopy(m_pBuffer, oldBuffer, len);
    }
    m_pBuffer[len] = 0;
    if (reallocated == true && oldLen > 0) {
        tfree(oldBuffer);
    }
}

void TCString::Copy(const TCString& s, int len)
{
    if (this == &s) {
        return;
    }
    if (len > (int)s.m_iStrLen || len == -1) {
        len = s.m_iStrLen;
    }
    AllocBuffer(len, true);
    TSystem::MemCopy(m_pBuffer, s.m_pBuffer, len);
    m_pBuffer[len] = 0;
}

void TCString::ForceSetData(char* data, int len)
{
    m_pBuffer = data;
    if (len < 0) {
        m_iStrLen = TSystem::StringLength(data);
    } else {
        m_iStrLen = len;
    }
    m_iExcess = 0;
}

void TCString::Copy(const TWString& s, int len)
{
    if (len > s.Length() || len == -1) {
        len = s.Length();
    }
    AllocBuffer(len, true);
    TSystem::StringUnicodeToChar(m_pBuffer, (const TWChar*)s, len);
    m_pBuffer[len] = 0;
}

void TCString::Copy(const TWChar* s, int len)
{
    int srcLen;
    if (s == 0) {
        srcLen = 0;
    } else {
        srcLen = TSystem::StringLength(s);
    }
    if (len > srcLen || len == -1) {
        len = srcLen;
    }
    AllocBuffer(len, true);
    TSystem::StringUnicodeToChar(m_pBuffer, s, len);
    m_pBuffer[len] = 0;
}

void TCString::Copy(const char* s, int len)
{
    if (s == m_pBuffer) {
        return;
    }
    unsigned int srcLen;
    if (s == 0) {
        srcLen = 0;
    } else {
        srcLen = TSystem::StringLength(s);
    }
    if (len > (int)srcLen || len == -1) {
        len = srcLen;
    }
    AllocBuffer(len, true);
    TSystem::MemCopy(m_pBuffer, s, len);
    m_pBuffer[len] = 0;
}

bool TWString::AllocBuffer(int len, bool freeOld)
{
    bool reallocated;
    int oldLen = m_iStrLen;
    if (len == oldLen) {
        reallocated = false;
    } else {
        if (len == 0) {
            if (freeOld == true) {
                tfree(m_pBuffer);
            }
            m_pBuffer = m_aNull;
            reallocated = true;
            m_iExcess = 0;
        } else {
            // The spare capacity left over after the resize; reallocate when it leaves 0..255.
            int excess = (oldLen - len) + m_iExcess;
            if (excess < 0 || excess > 255) {
                if (oldLen > 0 && freeOld == true) {
                    tfree(m_pBuffer);
                }
                m_pBuffer = (TWChar*)tmalloc(len * 2 + 2, 0, -1);
                reallocated = true;
                m_iExcess = 0;
            } else {
                m_iExcess = excess;
                reallocated = false;
            }
        }
        m_iStrLen = len;
    }
    if (freeOld == true) {
        *m_pBuffer = 0;
    }
    return reallocated;
}

int TWString::Find(TWChar c, int start) const
{
    if (!IsIndexValid(start)) {
        return -1;
    }
    wchar_t* found = wcschr((wchar_t*)(GetString(0) + start), c);
    int result;
    if (found == 0) {
        result = -1;
    } else {
        result = ((int)found - (int)GetString(0)) >> 1;
    }
    return result;
}

void TWString::Truncate(int len)
{
    int oldLen = m_iStrLen;
    if (len > oldLen) {
        len = oldLen;
    }
    TWChar* oldBuffer = m_pBuffer;
    bool reallocated = AllocBuffer(len, false);
    if (reallocated == true) {
        TSystem::StringCopy(m_pBuffer, oldBuffer, len);
    }
    m_pBuffer[len] = 0;
    if (reallocated == true && oldLen > 0) {
        tfree(oldBuffer);
    }
}

void TWString::Copy(const TWString& s, int len)
{
    if (len < 0 || len > (int)s.m_iStrLen) {
        len = s.m_iStrLen;
    }
    AllocBuffer(len, true);
    wcsncpy((wchar_t*)m_pBuffer, (const wchar_t*)s.m_pBuffer, len);
    m_pBuffer[len] = 0;
}

void TWString::Copy(const TWChar* s, int len)
{
    size_t srcLen;
    if (s == 0) {
        srcLen = 0;
    } else {
        srcLen = wcslen((const wchar_t*)s);
    }
    if (len > (int)srcLen || len == -1) {
        len = srcLen;
    }
    AllocBuffer(len, true);
    wcsncpy((wchar_t*)m_pBuffer, (const wchar_t*)s, len);
    m_pBuffer[len] = 0;
}


TCString& TCString::Concat(const TCString& s, int len)
{
    if (len > (int)s.m_iStrLen || len == -1) {
        len = s.m_iStrLen;
    }
    int oldLen = m_iStrLen;
    int newLen = len + oldLen;
    char* oldBuffer = m_pBuffer;
    bool reallocated = AllocBuffer(newLen, false);
    if (reallocated == true) {
        TSystem::StringCopy(m_pBuffer, oldBuffer, -1);
    }
    TSystem::StringCopy(m_pBuffer + oldLen, s.m_pBuffer, len);
    m_pBuffer[newLen] = 0;
    if (reallocated == true && oldLen > 0) {
        tfree(oldBuffer);
    }
    return *this;
}

TCString& TCString::Concat(const char* s, int len)
{
    int srcLen = TSystem::StringLength(s);
    if (len > srcLen || len == -1) {
        len = srcLen;
    }
    int oldLen = m_iStrLen;
    int newLen = len + oldLen;
    char* oldBuffer = m_pBuffer;
    bool reallocated = AllocBuffer(newLen, false);
    if (reallocated == true) {
        TSystem::StringCopy(m_pBuffer, oldBuffer, -1);
    }
    TSystem::StringCopy(m_pBuffer + oldLen, s, len);
    m_pBuffer[newLen] = 0;
    if (reallocated == true && oldLen > 0) {
        tfree(oldBuffer);
    }
    return *this;
}

TCString& TCString::VFormat(const char* fmt, char* args)
{
    char buffer[1024];
    _vsnprintf(buffer, 1024, fmt, args);
    Copy(buffer, -1);
    return *this;
}

TCString& __cdecl TCString::Format(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buffer[1024];
    _vsnprintf(buffer, 1024, fmt, args);
    Copy(buffer, -1);
    return *this;
}

int TCString::FindReverse(char c, int start) const
{
    if (start != -1) {
        if (!IsIndexValid(start)) {
            return -1;
        }
    } else {
        start = m_iStrLen;
    }
    const char* str = GetString(0);
    for (; start >= 0; start--) {
        if (str[start] == c) {
            return start;
        }
    }
    return -1;
}

TWString& TWString::Concat(const TWString& s, int len)
{
    if (len > (int)s.m_iStrLen || len == -1) {
        len = s.m_iStrLen;
    }
    int oldLen = m_iStrLen;
    int newLen = len + oldLen;
    TWChar* oldBuffer = m_pBuffer;
    bool reallocated = AllocBuffer(newLen, false);
    if (reallocated == true) {
        TSystem::StringCopy(m_pBuffer, oldBuffer, -1);
    }
    TSystem::StringCopy(m_pBuffer + oldLen, s.m_pBuffer, len);
    m_pBuffer[newLen] = 0;
    if (reallocated == true && oldLen > 0) {
        tfree(oldBuffer);
    }
    return *this;
}

TWString& TWString::Concat(const TWChar* s, int len)
{
    int srcLen = TSystem::StringLength(s);
    if (len > srcLen || len == -1) {
        len = srcLen;
    }
    int oldLen = m_iStrLen;
    int newLen = len + oldLen;
    TWChar* oldBuffer = m_pBuffer;
    bool reallocated = AllocBuffer(newLen, false);
    if (reallocated == true) {
        TSystem::StringCopy(m_pBuffer, oldBuffer, -1);
    }
    TSystem::StringCopy(m_pBuffer + oldLen, s, len);
    m_pBuffer[newLen] = 0;
    if (reallocated == true && oldLen > 0) {
        tfree(oldBuffer);
    }
    return *this;
}

TWString& TWString::VFormat(const TWChar* fmt, char* args)
{
    TWChar buffer[1024];
    _vsnwprintf((wchar_t*)buffer, 1024, (const wchar_t*)fmt, args);
    Copy(buffer, -1);
    return *this;
}

TWString& __cdecl TWString::Format(const TWChar* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    TWChar buffer[1024];
    _vsnwprintf((wchar_t*)buffer, 1024, (const wchar_t*)fmt, args);
    Copy(buffer, -1);
    return *this;
}

int TWString::FindReverse(TWChar c, int start) const
{
    if (start != -1) {
        if (!IsIndexValid(start)) {
            return -1;
        }
    } else {
        start = m_iStrLen;
    }
    const TWChar* str = GetString(0);
    for (; start >= 0; start--) {
        if (str[start] == c) {
            return start;
        }
    }
    return -1;
}


const char& TCString::operator[](int i) const
{
    return m_pBuffer[i];
}

TCString::operator const char*() const
{
    return m_pBuffer;
}

TWChar& TWString::operator[](int i) const
{
    return m_pBuffer[i];
}

TWString::operator const TWChar*() const
{
    return m_pBuffer;
}

// ---- free comparison operators (the C string is the left operand, the comparison is made against it)

bool __stdcall operator>=(const char* a, const TCString& b)
{
    int r = b.Compare(a, -1);
    if (r > -1) {
        return true;
    }
    return false;
}

bool __stdcall operator<=(const char* a, const TCString& b)
{
    int r = b.Compare(a, -1);
    if (r > 0) {
        return false;
    }
    return true;
}

bool __stdcall operator>(const char* a, const TCString& b)
{
    int r = b.Compare(a, -1);
    if (r > 0) {
        return true;
    }
    return false;
}

bool __stdcall operator<(const char* a, const TCString& b)
{
    int r = b.Compare(a, -1);
    if (r > -1) {
        return false;
    }
    return true;
}

bool __stdcall operator!=(const char* a, const TCString& b)
{
    int r = b.Compare(a, -1);
    if (r != 0) {
        return true;
    }
    return false;
}

bool __stdcall operator==(const char* a, const TCString& b)
{
    int r = b.Compare(a, -1);
    if (r == 0) {
        return true;
    }
    return false;
}

bool __stdcall operator>=(const TWChar* a, const TWString& b)
{
    int r = b.Compare(a, -1);
    if (r > -1) {
        return true;
    }
    return false;
}

bool __stdcall operator<=(const TWChar* a, const TWString& b)
{
    int r = b.Compare(a, -1);
    if (r > 0) {
        return false;
    }
    return true;
}

bool __stdcall operator>(const TWChar* a, const TWString& b)
{
    int r = b.Compare(a, -1);
    if (r > 0) {
        return true;
    }
    return false;
}

bool __stdcall operator<(const TWChar* a, const TWString& b)
{
    int r = b.Compare(a, -1);
    if (r > -1) {
        return false;
    }
    return true;
}

bool __stdcall operator!=(const TWChar* a, const TWString& b)
{
    int r = b.Compare(a, -1);
    if (r != 0) {
        return true;
    }
    return false;
}

bool __stdcall operator==(const TWChar* a, const TWString& b)
{
    int r = b.Compare(a, -1);
    if (r == 0) {
        return true;
    }
    return false;
}


// ---- member comparison operators (compare against a C string or another TCString)

bool TCString::operator>=(const char* s) const
{
    int r = Compare(s, -1);
    if (r >= 0) {
        return true;
    }
    return false;
}

bool TCString::operator>=(const TCString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r >= 0) {
        return true;
    }
    return false;
}

bool TCString::operator<=(const char* s) const
{
    int r = Compare(s, -1);
    if (r <= 0) {
        return true;
    }
    return false;
}

bool TCString::operator<=(const TCString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r <= 0) {
        return true;
    }
    return false;
}

bool TCString::operator>(const char* s) const
{
    int r = Compare(s, -1);
    if (r > 0) {
        return true;
    }
    return false;
}

bool TCString::operator>(const TCString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r > 0) {
        return true;
    }
    return false;
}

bool TCString::operator<(const char* s) const
{
    int r = Compare(s, -1);
    if (r < 0) {
        return true;
    }
    return false;
}

bool TCString::operator<(const TCString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r < 0) {
        return true;
    }
    return false;
}

bool TCString::operator!=(const char* s) const
{
    int r = Compare(s, -1);
    if (r != 0) {
        return true;
    }
    return false;
}

bool TCString::operator!=(const TCString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r != 0) {
        return true;
    }
    return false;
}

bool TCString::operator==(const char* s) const
{
    int r = Compare(s, -1);
    if (r == 0) {
        return true;
    }
    return false;
}

bool TCString::operator==(const TCString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r == 0) {
        return true;
    }
    return false;
}

bool TCString::operator!() const
{
    if (m_iStrLen == 0) {
        return true;
    }
    return false;
}

TCString& TCString::operator+=(const char* s)
{
    Concat(s, -1);
    return *this;
}

TCString& TCString::operator+=(const TWString& s)
{
    Concat(s, -1);
    return *this;
}

TCString& TCString::operator+=(const TCString& s)
{
    Concat(s, -1);
    return *this;
}

TCString& TCString::operator=(const char* s)
{
    Copy(s, -1);
    return *this;
}

TCString& TCString::operator=(const TWChar* s)
{
    Copy(s, -1);
    return *this;
}

TCString& TCString::operator=(TWString& s)
{
    Copy(s, -1);
    return *this;
}

TCString& TCString::operator=(TCString& s)
{
    Copy(s, -1);
    return *this;
}


// ---- TWString member comparison operators

bool TWString::operator>=(const TWChar* s) const
{
    int r = Compare(s, -1);
    if (r >= 0) {
        return true;
    }
    return false;
}

bool TWString::operator>=(const TWString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r >= 0) {
        return true;
    }
    return false;
}

bool TWString::operator<=(const TWChar* s) const
{
    int r = Compare(s, -1);
    if (r <= 0) {
        return true;
    }
    return false;
}

bool TWString::operator<=(const TWString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r <= 0) {
        return true;
    }
    return false;
}

bool TWString::operator>(const TWChar* s) const
{
    int r = Compare(s, -1);
    if (r > 0) {
        return true;
    }
    return false;
}

bool TWString::operator>(const TWString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r > 0) {
        return true;
    }
    return false;
}

bool TWString::operator<(const TWChar* s) const
{
    int r = Compare(s, -1);
    if (r < 0) {
        return true;
    }
    return false;
}

bool TWString::operator<(const TWString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r < 0) {
        return true;
    }
    return false;
}

bool TWString::operator!=(const TWChar* s) const
{
    int r = Compare(s, -1);
    if (r != 0) {
        return true;
    }
    return false;
}

bool TWString::operator!=(const TWString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r != 0) {
        return true;
    }
    return false;
}

bool TWString::operator==(const TWChar* s) const
{
    int r = Compare(s, -1);
    if (r == 0) {
        return true;
    }
    return false;
}

bool TWString::operator==(const TWString& s) const
{
    int r = Compare(s.m_pBuffer, -1);
    if (r == 0) {
        return true;
    }
    return false;
}

bool TWString::operator!() const
{
    if (m_iStrLen == 0) {
        return true;
    }
    return false;
}

TWString& TWString::operator+=(const TWChar* s)
{
    Concat(s, -1);
    return *this;
}

TWString& TWString::operator+=(const TWString& s)
{
    Concat(s, -1);
    return *this;
}

TWString& TWString::operator=(const char* s)
{
    Copy(s, -1);
    return *this;
}

TWString& TWString::operator=(const TWChar* s)
{
    Copy(s, -1);
    return *this;
}

TWString& TWString::operator=(TCString& s)
{
    Copy(s, -1);
    return *this;
}

TWString& TWString::operator=(TWString& s)
{
    Copy(s, -1);
    return *this;
}

} // namespace Toshi
