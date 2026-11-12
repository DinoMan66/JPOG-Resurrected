// Z:\Toshi\Source\TKernel\TFile.cpp - file base class and the null / memory / ISO files.
// Not written: Create, Open(TCString), path helpers, ISO buffering.
#define TOSHI_API __declspec(dllexport)
#include <stdio.h>
#include <stdarg.h>
#include "TKernelMisc.h"
#include "TKernelFiles.h"
#include "TKernelFileManager.h"
#include "TKernelSystem.h"
#include "TMemory.h"

namespace Toshi {

// ---- TFile
TFile::TFile(TFileSystem* fileSystem)
{
    m_pFileSystem = fileSystem;
}

TFile::~TFile()
{
}

unsigned __int64 TFile::GetDate()
{
    return 0;
}

void TFile::PrintFileAccess(bool enable)
{
}

TFile* __stdcall TFile::Create(const TCString& path, unsigned int flags)
{
    return TFileManager::s_pFileManager->CreateFile(path, flags);
}

void TFile::Destroy()
{
    if (this) {
        m_pFileSystem->DestroyFile(this);
    }
}

void __stdcall TFile::Destroy(TFile* file)
{
    if (file) {
        file->m_pFileSystem->DestroyFile(file);
    }
}

int __cdecl TFile::CPrintf(const char* fmt, ...)
{
    char* args = (char*)(&fmt + 1);
    return VCPrintf(fmt, args);
}

int __cdecl TFile::WPrintf(const TWChar* fmt, ...)
{
    char* args = (char*)(&fmt + 1);
    return VWPrintf(fmt, args);
}

// ---- TNullFile
bool TNullFile::Open(const TCString& fileName, unsigned int mode)
{
    return true;
}

void TNullFile::Close()
{
}

int TNullFile::GetSize()
{
    return 0;
}

int TNullFile::Tell()
{
    return 0;
}

bool TNullFile::Seek(int offset, TSEEK origin)
{
    return true;
}

int TNullFile::Read(void* buffer, int size)
{
    return -1;
}

int TNullFile::Write(const void* buffer, int size)
{
    m_iBytesWritten += size;
    return size;
}

int TNullFile::GetBytesWritten()
{
    return m_iBytesWritten;
}

int TNullFile::PutCChar(char c)
{
    if (Write(&c, 1) != 1) {
        return -1;
    }
    return c;
}

int TNullFile::PutWChar(TWChar c)
{
    if (Write(&c, 2) != 2) {
        return -1;
    }
    return c;
}

int TNullFile::GetCChar()
{
    unsigned char c;
    if (Read(&c, 1) != 1) {
        return -1;
    }
    return c;
}

int TNullFile::GetWChar()
{
    TWChar c;
    if (Read(&c, 2) != 2) {
        return -1;
    }
    return c;
}

int TNullFile::VCPrintf(const char* format, char* args)
{
    char buffer[512];
    int length = _vsnprintf(buffer, 512, format, args);
    if (length < 0) {
        length = 512;
    }
    return Write(buffer, length);
}

int TNullFile::VWPrintf(const TWChar* format, char* args)
{
    TWChar buffer[512];
    int length = _vsnwprintf(buffer, 512, format, args);
    if (length < 0) {
        length = 512;
    }
    int written = Write(buffer, length * 2);
    if (written >= 0) {
        written >>= 1;
    }
    return written;
}

// ---- TMemFile
int TMemFile::GetCChar()
{
    return -1;
}

int TMemFile::GetWChar()
{
    return 65535;
}

int TMemFile::GetSize()
{
    return m_iSize;
}

void TMemFile::ClearStats()
{
}

void TMemFile::DebugStats()
{
}

int TMemFile::Read(void* buffer, int size)
{
    if (size > 0 && size + (int)m_pCursor <= (int)m_pBuffer + m_iSize) {
        TSystem::MemCopy(buffer, m_pCursor, size);
        m_pCursor += size;
        if (size == 0) {
            size = -1;
        }
    } else {
        size = -1;
    }
    return size;
}

bool TMemFile::Seek(int offset, TSEEK origin)
{
    switch (origin) {
    case TSEEK_SET:
        if (offset > m_iSize) {
            m_pCursor = m_pBuffer;
        } else {
            m_pCursor = m_pBuffer + offset;
        }
        break;
    case TSEEK_CUR: {
        char* target = m_pCursor + offset;
        if (target > m_pBuffer + m_iSize) {
            m_pCursor = m_pBuffer;
        } else {
            m_pCursor = target;
        }
        break;
    }
    case TSEEK_END:
        m_pCursor = m_pBuffer + m_iSize;
        break;
    }
    return true;
}

void TMemFile::Close()
{
    if (m_pBuffer) {
        tfree(m_pBuffer);
        m_pBuffer = 0;
    }
    m_iSize = 0;
    m_pCursor = 0;
}

int TMemFile::PutCChar(char c)
{
    if (Write(&c, 1) != 1) {
        return -1;
    }
    return c;
}

int TMemFile::PutWChar(TWChar c)
{
    if (Write(&c, 2) != 2) {
        return -1;
    }
    return c;
}

int TMemFile::VCPrintf(const char* format, char* args)
{
    char buffer[512];
    int length = _vsnprintf(buffer, 512, format, args);
    if (length < 0) {
        length = 512;
    }
    return Write(buffer, length);
}

int TMemFile::VWPrintf(const TWChar* format, char* args)
{
    TWChar buffer[512];
    int length = _vsnwprintf(buffer, 512, format, args);
    if (length < 0) {
        length = 512;
    }
    int written = Write(buffer, length * 2);
    if (written >= 0) {
        written >>= 1;
    }
    return written;
}

bool TMemFile::Open(TFile* file)
{
    bool ok = true;
    if (file) {
        m_iSize = file->GetSize();
        if (m_iSize > 0) {
            m_pBuffer = (char*)tmalloc(m_iSize, 0, -1);
            m_pCursor = m_pBuffer;
            file->Seek(0, TSEEK_SET);
            if (file->Read(m_pBuffer, m_iSize) != m_iSize) {
                ok = false;
            }
        }
    }
    return ok;
}

// ---- TISOFile
bool TISOFile::Seek(int offset, TSEEK origin)
{
    switch (origin) {
    case TSEEK_SET:
        m_iPos = offset;
        break;
    case TSEEK_CUR:
        m_iPos += offset;
        break;
    case TSEEK_END:
        m_iPos = m_iSize - offset;
        break;
    }
    return true;
}

int TISOFile::GetCChar()
{
    unsigned char value;
    if (Read(&value, 1) != 1) {
        return -1;
    }
    return value;
}

int TISOFile::GetWChar()
{
    if (m_pBuffer) {
        int position = m_iPos;
        int block = position & ~0x1FFF;
        if (block == m_iBufferStart) {
            int index = position - block;
            if (index <= m_iBufferLength - 2) {
                unsigned char low = m_pBuffer[index];
                unsigned char high = m_pBuffer[index + 1];
                TWChar value = low | (high << 8);
                m_iPos = position + 2;
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

void TISOFile::Close()
{
    m_uStart = 0;
    m_iSize = 0;
    m_iPos = 0;
    m_iFilePointer = -1;
    m_iBufferStart = -1;
    m_iBufferLength = 0;
    if (m_pBuffer) {
        tfree(m_pBuffer);
        m_pBuffer = 0;
    }
}

int TISOFile::VWPrintf(const TWChar* format, char* args)
{
    return 0;
}

int TISOFile::VCPrintf(const char* format, char* args)
{
    return 0;
}

int TISOFile::PutWChar(TWChar c)
{
    return 0;
}

int TISOFile::PutCChar(char c)
{
    return 0;
}

int TISOFile::GetSize()
{
    return m_iSize;
}

int TISOFile::Tell()
{
    return m_iPos;
}

int TISOFile::Write(const void* buffer, int size)
{
    return 0;
}

void TISOFile::SetSubISOFile(unsigned int a, unsigned int b)
{
    m_uStart = a;
    m_iSize = b;
}

} // namespace Toshi
