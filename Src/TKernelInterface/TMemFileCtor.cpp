// Z:\Toshi\Source\TKernel\TMemFile.cpp - constructor of the memory file.
// Kept in a second translation unit: the original calls the constructor out of line from CreateFile,
// while a same-file definition would be expanded inline by the compiler (same reason as TISOFileCtor.cpp).
#define TOSHI_API __declspec(dllexport)
#include "TKernelFileManager.h"

namespace Toshi {

TMemFile::TMemFile(TMemFileSystem* fileSystem) : TFile(fileSystem)
{
    m_pBuffer = 0;
    m_pCursor = 0;
    m_iSize = 0;
}

} // namespace Toshi
