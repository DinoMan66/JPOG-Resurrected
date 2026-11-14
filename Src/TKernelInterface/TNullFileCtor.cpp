// Z:\Toshi\Source\TKernel\TNullFile.cpp - constructor of the null file.
// Kept in a second translation unit: the original calls the constructor out of line from CreateFile,
// while a same-file definition would be expanded inline by the compiler (same reason as TISOFileCtor.cpp).
#define TOSHI_API __declspec(dllexport)
#include "TKernelFileManager.h"

namespace Toshi {

TNullFile::TNullFile(TNullFileSystem* fileSystem) : TFile(fileSystem)
{
    m_iBytesWritten = 0;
}

} // namespace Toshi
