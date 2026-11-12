// Z:\Toshi\Source\TKernel\TFileManager.cpp - mounted file systems, the working directory and the system path.
// Not written: the path/prefix lookups that need the TDList<TFileSystem> template (FindFileSystem), CreateFile,
// ValidateSystemPath and the copy operators.
#define TOSHI_API __declspec(dllexport)
#include <new.h>
#include "TKernelFileManager.h"
#include "TMemory.h"

namespace Toshi {

TFileManager* TFileManager::s_pFileManager;

// ---- TFileSystem
TFileSystem::TFileSystem(const char* name) : m_oName(name)
{
}

TFileSystem::~TFileSystem()
{
}

const TCString& TFileSystem::GetPrefix() const
{
    return m_oPrefix;
}

const TCString& TFileSystem::GetName() const
{
    return m_oName;
}

bool TFileSystem::RemoveFile(const TCString& path)
{
    return true;
}

bool TFileSystem::GetFirstFile(const TCString& pattern, TCString& result, unsigned int flags)
{
    return false;
}

bool TFileSystem::GetNextFile(TCString& result, unsigned int flags)
{
    return false;
}

void TFileSystem::SetPrefix(const TCString& prefix)
{
    m_oPrefix = (const char*)prefix;
    int length = m_oPrefix.Length();
    for (int i = 0; i < length; i++) {
        if (m_oPrefix[i] == '/') {
            m_oPrefix[i] = '\\';
        }
    }
}

// ---- TFileManager::TSysPathIter
TFileManager::TSysPathIter::TSysPathIter(const TCString& path)
{
    m_pPath = &path;
    m_iPosition = -1;
}

TFileManager::TSysPathIter::TSysPathIter(const TSysPathIter& other)
{
    m_pPath = other.m_pPath;
    m_iPosition = other.m_iPosition;
}

bool TFileManager::TSysPathIter::First(TCString& result)
{
    if (m_pPath->Length() > 0) {
        m_iPosition = m_pPath->Find(';', 0);
        if (m_iPosition < 0) {
            result.Copy(*m_pPath, -1);
        } else {
            result.Copy(*m_pPath, m_iPosition);
        }
        return true;
    }
    m_iPosition = -1;
    return false;
}

bool TFileManager::TSysPathIter::Next(TCString& result)
{
    if (m_iPosition >= 0) {
        int start = m_iPosition + 1;
        m_iPosition = m_pPath->Find(';', start);
        if (m_iPosition < 0) {
            result.Copy(m_pPath->GetString(start), -1);
        } else {
            result.Copy(m_pPath->GetString(start), m_iPosition - start);
        }
        return true;
    }
    return false;
}

// ---- TFileManager
TFileManager::TFileManager() : m_bSystemPathValid(false), m_oWorkingDirectory("/")
{
    s_pFileManager = this;
    m_oMutex.Create();
}

TFileManager::~TFileManager()
{
    s_pFileManager = 0;
    m_oMutex.Destroy();
}

TFileManager* __stdcall TFileManager::GetFileManager()
{
    return s_pFileManager;
}

void TFileManager::InvalidateSystemPath()
{
    m_bSystemPathValid = false;
}

void TFileManager::FileSystemRelease()
{
    m_oMutex.Unlock();
}

void TFileManager::FileSystemWait()
{
    m_oMutex.Lock(0);
}

const TCString& TFileManager::GetWorkingDirectory() const
{
    return m_oWorkingDirectory;
}

const TCString& TFileManager::GetSystemPath() const
{
    return m_oSystemPath;
}

void TFileManager::SetSystemPath(const TCString& path)
{
    m_oSystemPath = (const char*)path;
    InvalidateSystemPath();
}

TCString TFileManager::MakeAbsolutePath(const TCString& path) const
{
    return TFile::ConcatPath(m_oWorkingDirectory, path);
}

void TFileManager::SetWorkingDirectory(const TCString& directory)
{
    TCString absolute = MakeAbsolutePath(directory);
    m_oWorkingDirectory = absolute;
}

void TFileManager::MountFileSystem(TFileSystem* fileSystem)
{
    TGenericDList::TNode* node = fileSystem;
    node->m_pNext = &m_oMountedSystems.m_oRoot;
    node->m_pPrev = m_oMountedSystems.m_oRoot.m_pPrev;
    m_oMountedSystems.m_oRoot.m_pPrev = node;
    node->m_pPrev->m_pNext = node;
    InvalidateSystemPath();
}

void TFileManager::UnmountFileSystem(TFileSystem* fileSystem)
{
    TGenericDList::TNode& node = *fileSystem;
    node.m_pPrev->m_pNext = node.m_pNext;
    node.m_pNext->m_pPrev = node.m_pPrev;
    node.m_pNext = &node;
    node.m_pPrev = &node;
}

void TFileManager::DestroyFile(TFile* file)
{
    if (file != 0) {
        file->GetFileSystem()->DestroyFile(file);
    }
}

} // namespace Toshi
