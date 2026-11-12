// Z:\Toshi\Source\TKernel\TDebug.cpp - closing and writing the debug file.
// Kept in a second translation unit: the original calls EnableDebugFile out of line from CloseDebugFile.
#define TOSHI_API __declspec(dllexport)
#include <stdio.h>
#include "TKernelDebug.h"

namespace Toshi {

void __stdcall TDebug::CloseDebugFile()
{
    if (m_pDebugFile != 0) {
        TFile::Destroy(m_pDebugFile);
        m_pDebugFile = 0;
        EnableDebugFile(false);
    }
}

void __stdcall TDebug::DebugFilePrintString(char* text)
{
    if (m_pDebugFile == 0 || m_bEnableDebugFile != true) {
        printf("%s", text);
        return;
    }
    m_pDebugFile->CPrintf(text);
}

} // namespace Toshi
