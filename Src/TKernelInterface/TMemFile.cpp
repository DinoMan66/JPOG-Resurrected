// Z:\Toshi\Source\TKernel\TMemFile.cpp - constructor/destructor and a few members of the memory file, and TMemFileSystem.
// These live in their own translation unit in the binary (TFile's constructor is called, not inlined).
#define TOSHI_API __declspec(dllexport)
#include <new.h>
#include "TKernelFileManager.h"
#include "TMemory.h"

namespace Toshi {

TMemFile::TMemFile(TMemFileSystem* fileSystem) : TFile(fileSystem)
{
    m_pBuffer = 0;
    m_pCursor = 0;
    m_iSize = 0;
}

TMemFile::~TMemFile()
{
}

// Evidence: the binary does nothing here but rewind the file (virtual Seek(0, SET)).
void TMemFile::DumpFile()
{
    Seek(0, TSEEK_SET);
}

int TMemFile::Tell()
{
    return m_pCursor - m_pBuffer;
}

int TMemFile::Write(const void* buffer, int size)
{
    return size;
}

// Note: the source file opened here is never destroyed again (the original leaks it).
bool TMemFile::Open(const TCString& path, unsigned int flags)
{
    bool ok = true;
    TFile* file = TFileManager::s_pFileManager->CreateFile(path, flags);
    if (file) {
        m_iSize = file->GetSize();
        if (m_iSize > 0) {
            m_pBuffer = (char*)tmalloc(m_iSize, 0, -1);
            m_pCursor = m_pBuffer;
            if (file->Read(m_pBuffer, m_iSize) != m_iSize) {
                ok = false;
            }
        }
    }
    return ok;
}

// ---- TMemFileSystem
TMemFileSystem::TMemFileSystem(const char* name) : TFileSystem(name)
{
    TFileManager* manager = TFileManager::s_pFileManager;
    manager->MountFileSystem(this);
    m_pParent = manager->FindFileSystem(TCString("local"));
}

TMemFileSystem::~TMemFileSystem()
{
    TFileManager::s_pFileManager->UnmountFileSystem(this);
}

TFile* TMemFileSystem::CreateFile(const TCString& path, unsigned int flags)
{
    void* memory = tmalloc(sizeof(TMemFile), 0, -1);
    TMemFile* file;
    if (memory == 0) {
        file = 0;
    } else {
        file = new (memory) TMemFile(this);
    }
    if (file != 0) {
        if (file->Open(path, flags)) {
            return file;
        }
    }
    return 0;
}

TFile* TMemFileSystem::CreateFile(TFile* source)
{
    void* memory = tmalloc(sizeof(TMemFile), 0, -1);
    TMemFile* file;
    if (memory == 0) {
        file = 0;
    } else {
        file = new (memory) TMemFile(this);
    }
    if (file != 0) {
        if (file->Open(source)) {
            return file;
        }
    }
    return 0;
}

void TMemFileSystem::DestroyFile(TFile* file)
{
    if (file != 0) {
        TMemFile* memFile = (TMemFile*)file;
        memFile->Close();
        delete memFile;
    }
}

TCString TMemFileSystem::MakeInternalPath(const TCString& path) const
{
    return m_pParent->MakeInternalPath(path);
}

} // namespace Toshi
