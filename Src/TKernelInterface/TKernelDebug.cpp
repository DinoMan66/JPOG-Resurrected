// Z:\Toshi\Source\TKernel\TDebug.cpp, TDLL.cpp - trivial members and the debug file hooks (TDebug_Message and OpenDebugFile included).
#define TOSHI_API __declspec(dllexport)
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include "TKernelDebug.h"

namespace Toshi {

class TFile;

// Call-stack walking is compiled out of the release build: the originals are empty.
void DumpCallStackToFile(TFile* file, int skip, int* stack, int depth)
{
}

void DumpCallStack(int skip, int* stack, int depth)
{
}

void GetCallStack(int skip, int* stack)
{
}

TDebug::MSGLEVEL TDebug::s_iMessageLevel = TDebug::MSGLEVEL_WARNING;

void TDebug_Message(TDebug::MSGLEVEL level, const char* format, ...)
{
    if (level >= TDebug::s_iMessageLevel) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

bool __stdcall TDebug::IsValidAddress(const void* address)
{
    return true;
}

void __stdcall TDebug::PrintIndent()
{
}

void __stdcall TDebug::ResetOutput()
{
}

const void* TDLL::GetDLL()
{
    return m_hModule;
}

bool TDebug::m_bEnableDebugFile;
TFile* TDebug::m_pDebugFile;

bool __stdcall TDebug::IsDebugFileEnabled()
{
    return m_bEnableDebugFile;
}

TFile* __stdcall TDebug::GetDebugFile()
{
    return m_pDebugFile;
}

bool __stdcall TDebug::OpenDebugFile(char* filename)
{
    CloseDebugFile();
    m_pDebugFile = TFile::Create(TCString(filename), 12);
    if (m_pDebugFile == 0) {
        return false;
    }
    EnableDebugFile(true);

    // The formatted date is not used afterwards: the buffer is never written to the file.
    char date[1000] = "";
    SYSTEMTIME time;
    GetLocalTime(&time);
    GetDateFormatA(LOCALE_SYSTEM_DEFAULT, LOCALE_NOUSEROVERRIDE, &time, 0, date, 1000);
    return true;
}

bool __stdcall TDebug::EnableDebugFile(bool enable)
{
    bool previous = m_bEnableDebugFile;
    m_bEnableDebugFile = enable;
    return previous;
}

} // namespace Toshi
