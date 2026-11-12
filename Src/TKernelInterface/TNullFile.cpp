// Z:\Toshi\Source\TKernel\TNullFile.cpp - constructor/destructor of the null file and the null file system.
// These live in their own translation unit in the binary (TFile's constructor is called, not inlined).
#define TOSHI_API __declspec(dllexport)
#include <new.h>
#include "TKernelFileManager.h"
#include "TMemory.h"

namespace Toshi {

TNullFile::TNullFile(TNullFileSystem* fileSystem) : TFile(fileSystem)
{
    m_iBytesWritten = 0;
}

TNullFile::~TNullFile()
{
}

// ---- TNullFileSystem
TNullFileSystem* TNullFileSystem::s_pFileSystem;

TNullFileSystem::TNullFileSystem(const char* name) : TFileSystem(name)
{
    TFileManager::s_pFileManager->MountFileSystem(this);
    s_pFileSystem = this;
}

TNullFileSystem::~TNullFileSystem()
{
    TFileManager::s_pFileManager->UnmountFileSystem(this);
    s_pFileSystem = 0;
}

TFile* TNullFileSystem::CreateFile(const TCString& path, unsigned int flags)
{
    void* memory = tmalloc(sizeof(TNullFile), 0, -1);
    TNullFile* file;
    if (memory == 0) {
        file = 0;
    } else {
        file = new (memory) TNullFile(this);
    }
    if (file != 0) {
        if (file->Open(path, flags)) {
            return file;
        }
    }
    return 0;
}

void TNullFileSystem::DestroyFile(TFile* file)
{
    if (file != 0) {
        TNullFile* nullFile = (TNullFile*)file;
        nullFile->Close();
        delete nullFile;
    }
}

TCString TNullFileSystem::MakeInternalPath(const TCString& path) const
{
    return TCString();
}

TNullFileSystem* __stdcall TNullFileSystem::GetNullFileSystem()
{
    return s_pFileSystem;
}

} // namespace Toshi
