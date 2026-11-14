// Z:\Toshi\Source\TKernel\TNativeFile.cpp - constructor of the native file.
// Kept in a second translation unit: the original calls the constructor out of line from CreateFile,
// while a same-file definition would be expanded inline by the compiler (same reason as TISOFileCtor.cpp).
#define TOSHI_API __declspec(dllexport)
#include "TKernelFileManager.h"

namespace Toshi {

TNativeFile::TNativeFile(TNativeFileSystem* fileSystem) : TFile(fileSystem)
{
    m_hFile = INVALID_HANDLE_VALUE;
    m_iPosition = -1;
    m_iFilePointer = -1;
    m_iBufferStart = -1;
    m_iBufferLength = 0;
    m_pReadBuffer = 0;
    m_pWriteBuffer = 0;
    m_iWriteLength = 0;
    m_bBuffered = true;
}

} // namespace Toshi
