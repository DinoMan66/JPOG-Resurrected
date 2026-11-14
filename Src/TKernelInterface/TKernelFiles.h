// TFile, TNullFile, TMemFile and TISOFile - kernel-internal declarations (the importing modules use include/TFile.h).
// Only the members implemented in TFile.cpp are declared; layouts follow the vtable of TNativeFile and the code.
#ifndef TKERNELFILES_H
#define TKERNELFILES_H
#include "TCString.h"
#include "TGenericLists.h"

namespace Toshi {

class TISOFileSystem;
class TNullFileSystem;
class TMemFileSystem;
class TFile;

// Base class of the mounted file systems. Layout: vtable, list node (+4), name (+0xC), prefix (+0x14).
class __declspec(dllexport) TFileSystem : public TGenericDList::TNode
{
public:
    TFileSystem(const char* name);
    virtual ~TFileSystem();                                                             // +0x00
    virtual TFile* CreateFile(const TCString& path, unsigned int flags) = 0;            // +0x04
    virtual void DestroyFile(TFile* file) = 0;                                          // +0x08
    virtual bool RemoveFile(const TCString& path);                                      // +0x0C
    virtual TCString MakeInternalPath(const TCString& path) const = 0;                  // +0x10
    virtual bool GetFirstFile(const TCString& pattern, TCString& result, unsigned int flags); // +0x14
    virtual bool GetNextFile(TCString& result, unsigned int flags);                     // +0x18
    virtual void SetPrefix(const TCString& prefix);                                     // +0x1C

    const TCString& GetName() const;
    const TCString& GetPrefix() const;

protected:
    TCString m_oName;               // +0x0C
    TCString m_oPrefix;             // +0x14
};

class __declspec(dllexport) TFile
{
public:
    enum TSEEK { TSEEK_SET = 0, TSEEK_CUR = 1, TSEEK_END = 2 };

    virtual int Read(void* buffer, int size) = 0;                   // +0x00
    virtual int Write(const void* buffer, int size) = 0;            // +0x04
    virtual bool Seek(int offset, TSEEK origin) = 0;                // +0x08
    virtual int Tell() = 0;                                         // +0x0C
    virtual int GetSize() = 0;                                      // +0x10
    virtual unsigned __int64 GetDate();                             // +0x14
    virtual int GetCChar() = 0;                                     // +0x18
    virtual int GetWChar() = 0;                                     // +0x1C
    virtual int PutCChar(char c) = 0;                               // +0x20
    virtual int PutWChar(TWChar c) = 0;                             // +0x24
    virtual int VCPrintf(const char* format, char* args) = 0;       // +0x28
    virtual int VWPrintf(const TWChar* format, char* args) = 0;     // +0x2C

    void Destroy();
    static TFile* __stdcall Create(const TCString& path, unsigned int flags);
    static void __stdcall Destroy(TFile* file);
    int __cdecl CPrintf(const char* fmt, ...);
    int __cdecl WPrintf(const TWChar* fmt, ...);
    TFileSystem* GetFileSystem() const { return m_pFileSystem; }
    static void __stdcall PrintFileAccess(bool enable);
    static TCString __stdcall ConcatPath(const TCString& directory, const TCString& file);

protected:
    TFile(TFileSystem* fileSystem);
    virtual ~TFile();                                               // +0x30

    TFileSystem* m_pFileSystem;     // +0x04
};

class __declspec(dllexport) TNullFile : public TFile
{
public:
    virtual int Read(void* buffer, int size);
    virtual int Write(const void* buffer, int size);
    virtual bool Seek(int offset, TSEEK origin);
    virtual int Tell();
    virtual int GetSize();
    virtual int GetCChar();
    virtual int GetWChar();
    virtual int PutCChar(char c);
    virtual int PutWChar(TWChar c);
    virtual int VCPrintf(const char* format, char* args);
    virtual int VWPrintf(const TWChar* format, char* args);
    int GetBytesWritten();

protected:
    TNullFile(TNullFileSystem* fileSystem);
    virtual ~TNullFile();

    bool Open(const TCString& fileName, unsigned int mode);
    void Close();

private:
    friend class TNullFileSystem;

    int m_iUnk08;
    int m_iBytesWritten;            // +0x0C
};

class __declspec(dllexport) TMemFile : public TFile
{
public:
    virtual int Read(void* buffer, int size);
    virtual bool Seek(int offset, TSEEK origin);
    virtual int GetCChar();
    virtual int GetWChar();
    virtual int GetSize();
    virtual int Tell();
    virtual int PutCChar(char c);
    virtual int PutWChar(TWChar c);
    virtual int VCPrintf(const char* format, char* args);
    virtual int VWPrintf(const TWChar* format, char* args);
    virtual int Write(const void* buffer, int size);
    virtual void ClearStats();
    virtual void DebugStats();
    void DumpFile();

protected:
    TMemFile(TMemFileSystem* fileSystem);
    virtual ~TMemFile();

    bool Open(const TCString& path, unsigned int flags);
    bool Open(TFile* file);
    void Close();

private:
    friend class TMemFileSystem;

    char* m_pBuffer;                // +0x08
    char* m_pCursor;                // +0x0C
    int m_iSize;                    // +0x10
};

class __declspec(dllexport) TISOFile : public TFile
{
public:
    virtual int Read(void* buffer, int size);
    virtual int Write(const void* buffer, int size);
    virtual bool Seek(int offset, TSEEK origin);
    virtual int GetCChar();
    virtual int GetWChar();
    virtual int Tell();
    virtual int GetSize();
    virtual int PutCChar(char c);
    virtual int PutWChar(TWChar c);
    virtual int VCPrintf(const char* format, char* args);
    virtual int VWPrintf(const TWChar* format, char* args);
    void SetSubISOFile(unsigned int a, unsigned int b);
    TISOFileSystem* GetFileSystem() const;

protected:
    TISOFile(TISOFileSystem* fileSystem);
    virtual ~TISOFile();

    bool Open(const TCString& path, unsigned int flags);
    void Close();

private:
    friend class TISOFileSystem;

    int ReadUnbuffered(void* buffer, int size);
    bool LoadBuffer(int offset);

    unsigned int m_uStart;          // +0x08
    int m_iSize;                    // +0x0C
    int m_iPos;                     // +0x10
    unsigned int m_uFlags;          // +0x14
    int m_iFilePointer;             // +0x18 (-1 when closed)
    int m_iBufferStart;             // +0x1C (-1 when closed)
    int m_iBufferLength;            // +0x20
    unsigned char* m_pBuffer;       // +0x24 (0x2000 byte read buffer)
};

} // namespace Toshi
#endif
