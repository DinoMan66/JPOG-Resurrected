// Z:\Toshi\Source\TKernel\TSystem.cpp - string and memory helpers. Only the simple members are written.
// Wide characters are unsigned short (VC6 mode: wchar_t is a typedef of unsigned short).
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <time.h>
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TCString.h"
#include "TPString.h"
#include "TKernelLocale.h"
#include "TNewDelete.h"

namespace Toshi {

bool __stdcall TSystem::GetLocalTime(TDateTime& dateTime)
{
    time_t now;
    time(&now);
    const tm* local = localtime(&now);
    dateTime.hour = local->tm_hour;
    dateTime.minute = local->tm_min;
    dateTime.second = local->tm_sec;
    dateTime.day = local->tm_mday;
    dateTime.month = local->tm_mon;
    dateTime.year = local->tm_year + 1900;
    return true;
}

void __stdcall TSystem::StringFormatDateTime(const TDateTime& dateTime, TCString& result)
{
    result.Format("%2d:%02d:%02d %d/%d/%d", dateTime.hour, dateTime.minute, dateTime.second, dateTime.day,
                  dateTime.month, dateTime.year);
}

TSysWChar* __stdcall TSystem::GetTempWString()
{
    return (TSysWChar*)ms_aScratchMem;
}

unsigned char* __stdcall TSystem::GetScratchMem()
{
    return ms_aScratchMem;
}

const char* __stdcall TSystem::StringFindChar(const char* s, char c)
{
    while (*s) {
        if (*s == c) {
            return s;
        }
        s++;
    }
    return 0;
}

unsigned int __stdcall TSystem::HashString(const char* s)
{
    unsigned int hash = 0;
    while (*s) {
        hash = hash * 5 + *s;
        s++;
    }
    return hash;
}

const TSysWChar* __stdcall TSystem::StringFindChar(const TSysWChar* s, TSysWChar c)
{
    while (*s) {
        if (*s == c) {
            return s;
        }
        s++;
    }
    return 0;
}

unsigned int __stdcall TSystem::HashString(const TSysWChar* s)
{
    unsigned int hash = 0;
    while (*s) {
        hash = hash * 5 + *s;
        s++;
    }
    return hash;
}

int __cdecl TSystem::StringFormat(TSysWChar* buffer, const TSysWChar* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    return vswprintf((wchar_t*)buffer, (const wchar_t*)fmt, args);
}

int __stdcall TSystem::StringLength(const TSysWChar* s)
{
    return wcslen((const wchar_t*)s);
}

const TSysWChar* __stdcall TSystem::StringCopy(TSysWChar* dst, const TSysWChar* src, int count)
{
    if (count != -1) {
        return (const TSysWChar*)wcsncpy((wchar_t*)dst, (const wchar_t*)src, count);
    }
    return (const TSysWChar*)wcscpy((wchar_t*)dst, (const wchar_t*)src);
}

int __stdcall TSystem::StringCompareNoCase(const TSysWChar* a, const TSysWChar* b, int count)
{
    if (count != -1) {
        return _wcsnicmp((const wchar_t*)a, (const wchar_t*)b, count);
    }
    return _wcsicmp((const wchar_t*)a, (const wchar_t*)b);
}

int __stdcall TSystem::StringCompare(const TSysWChar* a, const TSysWChar* b, int count)
{
    if (count != -1) {
        return wcsncmp((const wchar_t*)a, (const wchar_t*)b, count);
    }
    return wcscmp((const wchar_t*)a, (const wchar_t*)b);
}

int __cdecl TSystem::StringFormat(char* buffer, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    return vsprintf(buffer, fmt, args);
}

int __stdcall TSystem::StringLength(const char* s)
{
    return strlen(s);
}

const char* __stdcall TSystem::StringCopy(char* dst, const char* src, int count)
{
    if (count != -1) {
        return strncpy(dst, src, count);
    }
    return strcpy(dst, src);
}

int __stdcall TSystem::StringCompareNoCase(const char* a, const char* b, int count)
{
    if (count != -1) {
        return _strnicmp(a, b, count);
    }
    return _stricmp(a, b);
}

int __stdcall TSystem::StringCompare(const char* a, const char* b, int count)
{
    if (count != -1) {
        return strncmp(a, b, count);
    }
    return strcmp(a, b);
}

void* __stdcall TSystem::MemSet(void* dst, int value, int count)
{
    return memset(dst, value, count);
}

void* __stdcall TSystem::MemCopy(void* dst, const void* src, unsigned int count)
{
    return memcpy(dst, src, count);
}


// Formats an integer as octal, decimal or hexadecimal text (any other radix leaves the buffer untouched).
// name: unknown, only called from TSystem::StringIntToString
static char* f257c0(int value, char* buffer, int radix)
{
    if (radix == 8) {
        sprintf(buffer, "%o", value);
    } else if (radix == 10) {
        sprintf(buffer, "%d", value);
    } else if (radix == 16) {
        sprintf(buffer, "%x", value);
    }
    return buffer;
}

const char* __stdcall TSystem::StringIntToString(int value, char* buffer, int radix)
{
    return f257c0(value, buffer, radix);
}

unsigned int __stdcall TSystem::BCDToInteger(unsigned int value)
{
    unsigned int result = 0;
    int multiplier = 1;
    while (value != 0) {
        result += (value & 0xf) * multiplier;
        value >>= 4;
        multiplier *= 10;
    }
    return result;
}

const TSysWChar* __stdcall TSystem::StringCharToUnicode(TSysWChar* dst, const char* src, int count)
{
    int length = strlen(src);
    if (count > length || count == -1) {
        count = length;
    }
    int i;
    for (i = 0; i < count; i++) {
        dst[i] = (unsigned char)src[i];
    }
    dst[i] = 0;
    return dst;
}

// The three pools are created the first time somebody asks for them.
TCStringPool* __stdcall TSystem::CreateCStringPoolExplicit(int a, int b)
{
    if (ms_poTCStringPool == 0) {
        ms_poTCStringPool = new TCStringPool(a, b);
    }
    return ms_poTCStringPool;
}

TCStringPool* __stdcall TSystem::CreateCStringPoolExplicit(const char* name, int a, int b)
{
    if (ms_poTCStringPool == 0) {
        ms_poTCStringPool = new TCStringPool(name, a, b);
    }
    return ms_poTCStringPool;
}

TCStringPool* __stdcall TSystem::GetCStringPool()
{
    if (ms_poTCStringPool == 0) {
        ms_poTCStringPool = new TCStringPool(0x400, 0);
    }
    return ms_poTCStringPool;
}

TLocale* __stdcall TSystem::GetLocale()
{
    if (ms_poLocale == 0) {
        ms_poLocale = new TLocale;
    }
    return ms_poLocale;
}

TWStringPool* __stdcall TSystem::GetWStringPool()
{
    if (ms_poTWStringPool == 0) {
        ms_poTWStringPool = new TWStringPool;
    }
    return ms_poTWStringPool;
}

} // namespace Toshi
