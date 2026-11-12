// TDebug and TDLL - kernel-internal declarations (only the trivial members written so far).
#ifndef TKERNELDEBUG_H
#define TKERNELDEBUG_H
#include "TKernelFiles.h"
#include "TKernelDLL.h"

namespace Toshi {

class __declspec(dllexport) TDebug
{
public:
    // Message verbosity. The binary only shows that the default level is 2; the enumerator names are invented.
    enum MSGLEVEL
    {
        MSGLEVEL_INFO = 0,
        MSGLEVEL_NOTICE = 1,
        MSGLEVEL_WARNING = 2,
        MSGLEVEL_ERROR = 3
    };

    static bool __stdcall IsValidAddress(const void* address);
    static void __stdcall PrintIndent();
    static void __stdcall ResetOutput();
    static bool __stdcall IsDebugFileEnabled();
    static TFile* __stdcall GetDebugFile();
    static bool __stdcall OpenDebugFile(char* filename);
    static bool __stdcall EnableDebugFile(bool enable);
    static void __stdcall CloseDebugFile();
    static void __stdcall DebugFilePrintString(char* text);

    friend void TDebug_Message(MSGLEVEL level, const char* format, ...);

private:
    static MSGLEVEL s_iMessageLevel;
    static bool m_bEnableDebugFile;
    static TFile* m_pDebugFile;
};

// Prints the message when 'level' is at least the current verbosity (printf-style arguments).
void TDebug_Message(TDebug::MSGLEVEL level, const char* format, ...);

} // namespace Toshi
#endif
