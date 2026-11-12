// Z:\Toshi\Source\TKernel\TFile.cpp - TISOFile construction.
// Kept in a second translation unit: the original calls TFile::TFile out of line from this constructor,
// while the same-file definition in TKernelFiles.cpp would be expanded inline by the compiler.
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"
#include "TKernelFiles.h"
#include "TKernelSystem.h"

namespace Toshi {

TISOFile::TISOFile(TISOFileSystem* fileSystem) : TFile(fileSystem)
{
    m_uStart = 0;
    m_iSize = 0;
    m_iPos = 0;
    m_iFilePointer = -1;
    m_iBufferStart = -1;
    m_iBufferLength = 0;
    m_pBuffer = 0;
}

} // namespace Toshi
