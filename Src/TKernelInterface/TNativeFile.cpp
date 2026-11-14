// Z:\Toshi\Source\TKernel\TNativeFile.cpp - buffered Win32 file and the native file system (one module in the
// original; functions in the original order).
#define TOSHI_API __declspec(dllexport)
#include <stdio.h>
#include "TNewDelete.h"
#include <string.h>
#include "TKernelMisc.h"
#include "TKernelFiles.h"
#include "TKernelFileManager.h"
#include "TMemory.h"
#include <windows.h>

namespace Toshi {

TFile* TNativeFileSystem::CreateFile(const TCString& path, unsigned int flags)
{
    TNativeFile* file = new TNativeFile(this);
    if (file != 0) {
        if (file->Open(path, flags)) {
            return file;
        }
        delete file;
    }
    return 0;
}

void TNativeFileSystem::DestroyFile(TFile* file)
{
    if (file != 0) {
        TNativeFile* nativeFile = (TNativeFile*)file;
        nativeFile->Close();
        delete nativeFile;
    }
}

TCString TNativeFileSystem::MakeInternalPath(const TCString& path) const
{
    TCString result(m_oPrefix);
    int length = result.Length();
    if (length > 0) {
        const char* last = &result[length - 1];
        if (*last == '/' || *last == '\\') {
            result.Truncate(length - 1);
        }
    }
    result += TFileManager::s_pFileManager->MakeAbsolutePath(path);
    length = result.Length();
    for (int i = 0; i < length; i++) {
        if (result[i] == '/') {
            result[i] = '\\';
        }
    }
    return result;
}

bool TNativeFileSystem::GetFirstFile(const TCString& pattern, TCString& result, unsigned int flags)
{
    bool found = false;
    TCString searchPath(pattern);
    if (pattern.Mid(pattern.Length() - 1, 1).Compare("\\", -1) == 0 || pattern.Mid(pattern.Length() - 1, 1).Compare("/", -1) == 0) {
        searchPath.Concat("*", -1);
    } else {
        searchPath.Concat("\\*", -1);
    }
    WIN32_FIND_DATAA findData;
    m_hFind = FindFirstFileA(searchPath.GetString(0), &findData);
    if (m_hFind != INVALID_HANDLE_VALUE) {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (flags & 2) {
                found = true;
                result = findData.cFileName;
            }
        } else if (flags & 1) {
            found = true;
            result = findData.cFileName;
        }
    }
    return found;
}

bool TNativeFileSystem::GetNextFile(TCString& result, unsigned int flags)
{
    bool found = false;
    if (m_hFind != INVALID_HANDLE_VALUE) {
        WIN32_FIND_DATAA findData;
        if (FindNextFileA(m_hFind, &findData)) {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (flags & 2) {
                    found = true;
                    result = findData.cFileName;
                }
            } else if (flags & 1) {
                found = true;
                result = findData.cFileName;
            }
        } else {
            m_hFind = INVALID_HANDLE_VALUE;
        }
    }
    return found;
}

int TNativeFile::Read(void* buffer, int size)
{
    if (size <= 0) {
        return 0;
    }
    if (!m_pReadBuffer) {
        return ReadUnbuffered(buffer, size);
    }
    char* destination = (char*)buffer;
    int total = 0;
    int block = m_iPosition & ~0x7FF;
    int endBlock = (m_iPosition + size) & ~0x7FF;
    if (block != endBlock) {
        // the request spans blocks: use what the cached block holds, then read whole blocks directly
        if (block == m_iBufferStart) {
            int index = m_iPosition - block;
            int available = m_iBufferLength - index;
            if (available > 0) {
                memcpy(destination, m_pReadBuffer + index, available);
                destination += available;
                m_iPosition += available;
                total = available;
            }
        }
        int direct = endBlock - m_iPosition;
        if (direct > 0) {
            int count = ReadUnbuffered(destination, direct);
            destination += count;
            total += count;
            if (count != direct) {
                return total;
            }
        }
        block = endBlock;
    }
    if (total != size) {
        if (!LoadBuffer(block)) {
            return total;
        }
        int index = m_iPosition - block;
        int remaining = size - total;
        int available = m_iBufferLength - index;
        int count = Min(available, remaining);
        if (count > 0) {
            memcpy(destination, m_pReadBuffer + index, count);
            m_iPosition += count;
            total += count;
        }
    }
    return total;
}

int TNativeFile::Write(const void* buffer, int size)
{
    if (m_iPosition != m_iFilePointer) {
        DWORD pointer = SetFilePointer(m_hFile, m_iPosition, 0, FILE_BEGIN);
        m_iFilePointer = pointer;
        if (pointer == -1) {
            if (GetLastError() != 0) {
                return 0;
            }
            pointer = m_iFilePointer;
        }
        m_iPosition = pointer;
    }
    if (m_bBuffered) {
        if (m_iWriteLength + size >= 0x800) {
            FlushWriteBuffer();
        }
        if (size >= 0x800) {
            DWORD bytesWritten;
            if (!WriteFile(m_hFile, buffer, size, &bytesWritten, 0)) {
                return 0;
            }
            m_iFilePointer += bytesWritten;
            m_iPosition = m_iFilePointer;
            return bytesWritten;
        }
        memcpy(m_pWriteBuffer + m_iWriteLength, buffer, size);
        m_iWriteLength += size;
        return size;
    }
    DWORD bytesWritten;
    if (!WriteFile(m_hFile, buffer, size, &bytesWritten, 0)) {
        return 0;
    }
    m_iFilePointer += bytesWritten;
    m_iPosition = m_iFilePointer;
    return bytesWritten;
}

bool TNativeFile::Seek(int offset, TSEEK origin)
{
    switch (origin) {
    case TSEEK_SET:
        if (offset < 0) {
            m_iPosition = 0;
        } else {
            m_iPosition = offset;
        }
        break;
    case TSEEK_CUR:
        if (offset + m_iPosition < 0) {
            m_iPosition = 0;
        } else {
            m_iPosition = offset + m_iPosition;
        }
        break;
    case TSEEK_END: {
        DWORD endPosition = SetFilePointer(m_hFile, offset, 0, FILE_END);
        m_iFilePointer = endPosition;
        if (endPosition == -1) {
            if (GetLastError() != 0) {
                return false;
            }
            endPosition = m_iFilePointer;
        }
        m_iPosition = endPosition;
        break;
    }
    }
    return true;
}

int TNativeFile::GetSize()
{
    DWORD size = SetFilePointer(m_hFile, 0, 0, FILE_END);
    m_iFilePointer = size;
    if (size == -1) {
        // -1 is also a valid position: only a set last error means failure
        if (GetLastError() == 0) {
            return m_iFilePointer;
        }
        return 0;
    }
    return size;
}

unsigned __int64 TNativeFile::GetDate()
{
    unsigned __int64 date = 0;
    if (m_hFile != INVALID_HANDLE_VALUE) {
        FILETIME created;
        FILETIME accessed;
        FILETIME written;
        GetFileTime(m_hFile, &created, &accessed, &written);
        date = *(unsigned __int64*)&written;
    }
    return date;
}

int TNativeFile::GetCChar()
{
    if (m_pReadBuffer) {
        int position = m_iPosition;
        int block = position & ~0x7FF;
        if (block == m_iBufferStart) {
            int index = position - block;
            if (index <= m_iBufferLength - 1) {
                unsigned char value = m_pReadBuffer[index];
                m_iPosition = position + 1;
                return value;
            }
        }
    }
    unsigned char value;
    if (Read(&value, 1) != 1) {
        return -1;
    }
    return value;
}

int TNativeFile::GetWChar()
{
    if (m_pReadBuffer) {
        int position = m_iPosition;
        int block = position & ~0x7FF;
        if (block == m_iBufferStart) {
            int index = position - block;
            if (index <= m_iBufferLength - 2) {
                unsigned char low = m_pReadBuffer[index];
                unsigned char high = m_pReadBuffer[index + 1];
                TWChar value = low | (high << 8);
                m_iPosition = position + 2;
                return value;
            }
        }
    }
    unsigned short value;
    if (Read(&value, 2) != 2) {
        return -1;
    }
    return value;
}

int TNativeFile::VCPrintf(const char* format, char* args)
{
    char buffer[512];
    int length = _vsnprintf(buffer, 512, format, args);
    if (length < 0) {
        length = 512;
    }
    return Write(buffer, length);
}

int TNativeFile::VWPrintf(const TWChar* format, char* args)
{
    TWChar buffer[512];
    int length = _vsnwprintf((wchar_t*)buffer, 512, (const wchar_t*)format, args);
    if (length < 0) {
        length = 512;
    }
    length = Write(buffer, length * 2);
    if (length >= 0) {
        length = length >> 1;
    }
    return length;
}

bool TNativeFile::Open(const TCString& path, unsigned int flags)
{
    TCString internalPath = m_pFileSystem->MakeInternalPath(path);
    DWORD access = 0;
    if (flags & 1) {
        access = GENERIC_READ;
    }
    if (flags & 2) {
        access |= GENERIC_WRITE;
    }
    if (flags & 4) {
        access |= GENERIC_READ | GENERIC_WRITE;
    }
    DWORD creation;
    if (flags & 8) {
        creation = CREATE_ALWAYS;
        if (access == 0) {
            access = GENERIC_WRITE;
        }
    } else {
        creation = OPEN_EXISTING;
    }
    HANDLE file = CreateFileA(internalPath.GetString(0), access, 0, 0, creation, 0, 0);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }
    m_hFile = file;
    m_iPosition = 0;
    m_iFilePointer = 0;
    m_iBufferStart = -1;
    m_iBufferLength = 0;
    if (flags & 0x10) {
        m_bBuffered = false;
    } else {
        m_pReadBuffer = (unsigned char*)tmalloc(0x800, 0, -1);
        m_bBuffered = false;
    }
    return true;
}

void TNativeFile::Close()
{
    FlushWriteBuffer();
    CloseHandle(m_hFile);
    m_hFile = INVALID_HANDLE_VALUE;
    m_iPosition = -1;
    m_iFilePointer = -1;
    m_iBufferStart = -1;
    m_iBufferLength = 0;
    if (m_pReadBuffer) {
        tfree(m_pReadBuffer);
        m_pReadBuffer = 0;
    }
    if (m_pWriteBuffer) {
        tfree(m_pWriteBuffer);
        m_pWriteBuffer = 0;
    }
}

int TNativeFile::ReadUnbuffered(void* buffer, int size)
{
    if (m_iPosition != m_iFilePointer) {
        DWORD pointer = SetFilePointer(m_hFile, m_iPosition, 0, FILE_BEGIN);
        m_iFilePointer = pointer;
        if (pointer == -1) {
            if (GetLastError() != 0) {
                return 0;
            }
            pointer = m_iFilePointer;
        }
        m_iPosition = pointer;
    }
    DWORD bytesRead;
    if (!ReadFile(m_hFile, buffer, size, &bytesRead, 0)) {
        return 0;
    }
    m_iFilePointer += bytesRead;
    m_iPosition = m_iFilePointer;
    return bytesRead;
}

bool TNativeFile::LoadBuffer(int offset)
{
    if (offset != m_iBufferStart) {
        if (offset != m_iFilePointer) {
            m_iFilePointer = SetFilePointer(m_hFile, offset, 0, FILE_BEGIN);
            if (m_iFilePointer != offset) {
                return false;
            }
        }
        DWORD bytesRead;
        if (!ReadFile(m_hFile, m_pReadBuffer, 0x800, &bytesRead, 0)) {
            return false;
        }
        m_iFilePointer += bytesRead;
        m_iBufferLength = bytesRead;
        m_iBufferStart = offset;
    }
    return true;
}

int TNativeFile::FlushWriteBuffer()
{
    if (m_iPosition != m_iFilePointer) {
        DWORD pointer = SetFilePointer(m_hFile, m_iPosition, 0, FILE_BEGIN);
        m_iFilePointer = pointer;
        if (pointer == -1) {
            if (GetLastError() != 0) {
                return 0;
            }
            pointer = m_iFilePointer;
        }
        m_iPosition = pointer;
    }
    DWORD bytesWritten;
    if (!WriteFile(m_hFile, m_pWriteBuffer, m_iWriteLength, &bytesWritten, 0)) {
        return 0;
    }
    m_iFilePointer += bytesWritten;
    m_iPosition = m_iFilePointer;
    m_iWriteLength = 0;
    return bytesWritten;
}

TNativeFile::~TNativeFile()
{
}

int TNativeFile::PutWChar(TWChar c)
{
    if (Write(&c, 2) != 2) {
        return -1;
    }
    return c;
}

int TNativeFile::PutCChar(char c)
{
    if (Write(&c, 1) != 1) {
        return -1;
    }
    return c;
}

int TNativeFile::Tell()
{
    return m_iPosition;
}

bool TNativeFileSystem::MakeDirectory(const TCString& path)
{
    return CreateDirectoryA(path.GetString(0), 0) != 0;
}

bool TNativeFileSystem::RemoveFile(const TCString& path)
{
    return DeleteFileA(path.GetString(0)) != 0;
}

TNativeFileSystem::~TNativeFileSystem()
{
    TFileManager::s_pFileManager->UnmountFileSystem(this);
}

TNativeFileSystem::TNativeFileSystem(const char* name) : TFileSystem(name)
{
    m_hFind = (void*)-1;
    TFileManager::s_pFileManager->MountFileSystem(this);
}

} // namespace Toshi
